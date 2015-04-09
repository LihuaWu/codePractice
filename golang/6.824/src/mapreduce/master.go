package mapreduce

import "container/list"
import "fmt"
import "log"


type WorkerInfo struct {
	address string
	// You can add definitions here.
}


//akshaykumar90/mit-6.824-labs
// Clean up all workers by sending a Shutdown RPC to each one of them Collect
// the number of jobs each work has performed.
func (mr *MapReduce) KillWorkers() *list.List {
	l := list.New()
	for _, w := range mr.Workers {
		DPrintf("DoWork: shutdown %s\n", w.address)
		args := &ShutdownArgs{}
		var reply ShutdownReply
		ok := call(w.address, "Worker.Shutdown", args, &reply)
		if ok == false {
			fmt.Printf("DoWork: RPC %s shutdown error\n", w.address)
		} else {
			l.PushBack(reply.Njobs)
		}
	}
	return l
}

func (mr *MapReduce) RunMaster() *list.List {
	done := make(chan struct{})
	jobs := make(chan *DoJobArgs)
	waiting := make(chan string)


	DoJob := func(worker string, args *DoJobArgs)  {
		var reply DoJobReply
		ok := call(worker, "Worker.DoJob", args, &reply)
		if (ok) {
			done <-struct{}{}
			waiting <-worker
		} else {
			jobs <-args
		}
	}

	SelectedWorker := func() string {
		var worker string
		select {
		case worker = <-mr.registerChannel:
			mr.Workers[worker] = &WorkerInfo{worker}
		case worker = <-waiting:
		}
		return worker
	}


	go func() {
		for job := range jobs {
			worker := SelectedWorker()
			go DoJob(worker, job)

		}
	}()



	for i := 0; i < nMap; i++ {
		args := &DoJobArgs{File:mr.file, Operation: Map, JobNumber: i, NumOtherPhase: nReduce}
		jobs <-args

	}
	for i := 0; i < mr.nMap; i++ {
		<-done
	}
	log.Printf("map done!\n")

	for i := 0; i < nReduce; i++ {
		args := &DoJobArgs{File:mr.file, Operation: Reduce, JobNumber: i, NumOtherPhase: nMap}
		jobs <-args
	}
	for i := 0; i < mr.nReduce; i++ {
		<-done
	}
	log.Printf("reduce done!\n")
	// Your code here

	return mr.KillWorkers()
}
