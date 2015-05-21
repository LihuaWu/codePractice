package viewservice

import "net"
import "net/rpc"
import "log"
import "time"
import "sync"
import "fmt"
import "os"
import "sync/atomic"

type ViewServer struct {
	mu       sync.Mutex
	l        net.Listener
	dead     int32 // for testing
	rpccount int32 // for testing
	me       string
	primaryAck	bool
	view	 View
	lastSeen	map[string]time.Time


	// Your declarations here.
}

func (vs *ViewServer) changeView(n uint, p, b string) {
	vs.view = View{n, p, b}
	vs.primaryAck = false
}

func (vs *ViewServer) promoteBackup() bool {
	if !vs.primaryAck {return false }
	if vs.view.Backup == "" { return false }
	vs.changeView(vs.view.Viewnum + 1, vs.view.Backup, "")
	return true;
}

func (vs *ViewServer) addServer(id string) bool {
	if !vs.primaryAck {return false }
	if vs.view.Primary == "" {
		vs.changeView(1, id, "")
		return true
	}
	if (vs.view.Backup == "") {
		vs.changeView(vs.view.Viewnum + 1, vs.view.Primary, id)
		return true
	}
	return false;
}

func (vs *ViewServer) removeBackup() bool {
	if !vs.primaryAck  {return false }
	vs.changeView(vs.view.Viewnum + 1, vs.view.Primary, "")
	return true;
}

//
// server Ping RPC handler.
//
func (vs *ViewServer) Ping(args *PingArgs, reply *PingReply) error {
	vs.mu.Lock()
	defer vs.mu.Unlock()

	id, viewnum := args.Me, args.Viewnum
	switch id {
	case vs.view.Primary:
		if viewnum == vs.view.Viewnum {
			vs.primaryAck = true
			vs.lastSeen[vs.view.Primary] = time.Now()
		} else {
			fmt.Printf("ack:%d\n",vs.primaryAck)
			vs.promoteBackup()
		}
	case vs.view.Backup:
		if viewnum == vs.view.Viewnum {
			vs.lastSeen[vs.view.Backup] = time.Now()
		} else {
			fmt.Printf("ack:%d\n",vs.primaryAck)
			vs.removeBackup()
		}
	default:
		vs.addServer(id)
	}

	reply.View = vs.view
	// Your code here.

	return nil
}

//
// server Get() RPC handler.
//
func (vs *ViewServer) Get(args *GetArgs, reply *GetReply) error {
	// Your code here.
	vs.mu.Lock()
	defer vs.mu.Unlock()
	reply.View = vs.view
	return nil
}


//
// tick() is called once per PingInterval; it should notice
// if servers have died or recovered, and change the view
// accordingly.
//
func (vs *ViewServer) tick() {
	vs.mu.Lock()
	defer vs.mu.Unlock()
	for id, t := range vs.lastSeen {
		if time.Since(t) >= DeadPings * PingInterval {
			switch id {
			case vs.view.Primary:
				vs.promoteBackup()
			case vs.view.Backup:
				vs.removeBackup()
			}
		}
	}
	// Your code here.
}

//
// tell the server to shut itself down.
// for testing.
// please don't change these two functions.
//
func (vs *ViewServer) Kill() {
	atomic.StoreInt32(&vs.dead, 1)
	vs.l.Close()
}

//
// has this server been asked to shut down?
//
func (vs *ViewServer) isdead() bool {
	return atomic.LoadInt32(&vs.dead) != 0
}

// please don't change this function.
func (vs *ViewServer) GetRPCCount() int32 {
	return atomic.LoadInt32(&vs.rpccount)
}

func StartServer(me string) *ViewServer {
	vs := new(ViewServer)
	vs.me = me
	vs.primaryAck = true
	vs.lastSeen = make(map[string]time.Time)
	// Your vs.* initializations here.

	// tell net/rpc about our RPC server and handlers.
	rpcs := rpc.NewServer()
	rpcs.Register(vs)

	// prepare to receive connections from clients.
	// change "unix" to "tcp" to use over a network.
	os.Remove(vs.me) // only needed for "unix"
	l, e := net.Listen("unix", vs.me)
	if e != nil {
		log.Fatal("listen error: ", e)
	}
	vs.l = l

	// please don't change any of the following code,
	// or do anything to subvert it.

	// create a thread to accept RPC connections from clients.
	go func() {
		for vs.isdead() == false {
			conn, err := vs.l.Accept()
			if err == nil && vs.isdead() == false {
				atomic.AddInt32(&vs.rpccount, 1)
				go rpcs.ServeConn(conn)
			} else if err == nil {
				conn.Close()
			}
			if err != nil && vs.isdead() == false {
				fmt.Printf("ViewServer(%v) accept: %v\n", me, err.Error())
				vs.Kill()
			}
		}
	}()

	// create a thread to call tick() periodically.
	go func() {
		for vs.isdead() == false {
			vs.tick()
			time.Sleep(PingInterval)
		}
	}()

	return vs
}
