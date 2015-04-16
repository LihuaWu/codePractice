package pbservice

import "net"
import "fmt"
import "net/rpc"
import "log"
import "time"
import "viewservice"
import "sync"
import "sync/atomic"
import "os"
import "syscall"
import "math/rand"



type PBServer struct {
	mu         sync.Mutex
	l          net.Listener
	dead       int32 // for testing
	unreliable int32 // for testing
	me         string
	vs         *viewservice.Clerk
	// Your declarations here.
	data	   map[string]string
	replies		map[int64]string
	curr	   viewservice.View
}

func (pb *PBServer) get(args *GetArgs, reply *GetReply) {
	if _, ok := pb.data[args.Key]; !ok {
		reply.Err = ErrNoKey
		return
	}
	reply.Err = OK
	reply.Value = pb.data[args.Key]
}

func (pb *PBServer) BGet(args *GetArgs, reply *GetReply) error {
//	pb.mu.Lock()
//	defer pb.mu.Unlock()
	if pb.me != pb.curr.Backup {
		reply.Err = ErrWrongServer
		return nil
	}
	pb.get(args, reply)
	pb.replies[args.Xid] = reply.Value
	return nil
}


func (pb *PBServer) Get(args *GetArgs, reply *GetReply) error {
//	pb.mu.Lock()
//	defer pb.mu.Unlock()
	
	if r, ok := pb.replies[args.Xid]; ok {
		reply.Err = OK
		reply.Value = r
		return nil
	}

	if pb.me != pb.curr.Primary {
		reply.Err = ErrWrongServer
		return nil
	}

	if pb.curr.Backup != "" {
		if ok := call(pb.curr.Backup, "PBServer.BGet", args, reply); !ok {
		}
		if reply.Err != OK {
			return nil
		}
	}

	pb.get(args, reply)

	pb.replies[args.Xid] = reply.Value
	// Your code here.

	return nil
}

func (pb *PBServer) BPut(args *PutAppendArgs, reply *PutAppendReply) error {
	pb.mu.Lock()
	defer pb.mu.Unlock()

	if pb.me != pb.curr.Backup {
		reply.Err = ErrWrongServer
		return nil
	}
	pb.replies[args.Xid] = args.Value
}

func (pb *PBServer) PutAppend(args *PutAppendArgs, reply *PutAppendReply) error {
	// Your code here.
	pb.mu.Lock()
	defer pb.mu.Unlock()

	if pb.me != pb.curr.Primary {
		reply.Err = ErrWrongServer
		return nil
	}

	if pb.curr.Backup != "" {
		if ok := call(pb.curr.Backup, "PBServer.BPut", args, reply); !ok {
			return log.Printf("Put [%s]: Error talking to backup [%s]", pb.curr.Primary, pb.curr.Backup)
		}
		if reply.Err != OK {
			return nil
		}
	}

	pb.put(args, reply)

	return nil
}


//
// ping the viewserver periodically.
// if view changed:
//   transition to new view.
//   manage transfer of state from primary to new backup.
//
func (pb *PBServer) tick() {
	pb.mu.Lock()
	defer pb.mu.Unlock()

	view, err := pb.vs.Ping(pb.curr.Viewnum)
	if err != nil {
		return
	}

	if view.Primary == pb.me && view.Backup != "" && view.Backup != pb.curr.Backup {
		var reply SyncReply
		if ok := call(view.Backup, "PBServer.BSync", SyncArgs{pb.data, pb.replies}, &reply); !ok {
			log.Printf("Sync[%s]: Error talking to backup [%s]", view.Primary,view.Backup)
			return
		}
	}
	pb.curr = view
	// Your code here.
}

// tell the server to shut itself down.
// please do not change these two functions.
func (pb *PBServer) kill() {
	atomic.StoreInt32(&pb.dead, 1)
	pb.l.Close()
}

func (pb *PBServer) isdead() bool {
	return atomic.LoadInt32(&pb.dead) != 0
}

// please do not change these two functions.
func (pb *PBServer) setunreliable(what bool) {
	if what {
		atomic.StoreInt32(&pb.unreliable, 1)
	} else {
		atomic.StoreInt32(&pb.unreliable, 0)
	}
}

func (pb *PBServer) isunreliable() bool {
	return atomic.LoadInt32(&pb.unreliable) != 0
}

func (pb *PBServer) BSync(args *SyncArgs, reply *SyncReply) error {
	pb.mu.Lock()
	defer pb.mu.Unlock()

	pb.data = args.Data
	pb.replies = args.Replies
	return nil
}


func StartServer(vshost string, me string) *PBServer {
	pb := new(PBServer)
	pb.me = me
	pb.vs = viewservice.MakeClerk(me, vshost)
	// Your pb.* initializations here.

	rpcs := rpc.NewServer()
	rpcs.Register(pb)

	os.Remove(pb.me)
	l, e := net.Listen("unix", pb.me)
	if e != nil {
		log.Fatal("listen error: ", e)
	}
	pb.l = l

	// please do not change any of the following code,
	// or do anything to subvert it.

	go func() {
		for pb.isdead() == false {
			conn, err := pb.l.Accept()
			if err == nil && pb.isdead() == false {
				if pb.isunreliable() && (rand.Int63()%1000) < 100 {
					// discard the request.
					conn.Close()
				} else if pb.isunreliable() && (rand.Int63()%1000) < 200 {
					// process the request but force discard of reply.
					c1 := conn.(*net.UnixConn)
					f, _ := c1.File()
					err := syscall.Shutdown(int(f.Fd()), syscall.SHUT_WR)
					if err != nil {
						fmt.Printf("shutdown: %v\n", err)
					}
					go rpcs.ServeConn(conn)
				} else {
					go rpcs.ServeConn(conn)
				}
			} else if err == nil {
				conn.Close()
			}
			if err != nil && pb.isdead() == false {
				fmt.Printf("PBServer(%v) accept: %v\n", me, err.Error())
				pb.kill()
			}
		}
	}()

	go func() {
		for pb.isdead() == false {
			pb.tick()
			time.Sleep(viewservice.PingInterval)
		}
	}()

	return pb
}
