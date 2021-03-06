#include "CurrentThread.h"
#include "Thread.h"
#include "Timestamp.h"

#include <sys/syscall.h>
#include <unistd.h>
#include <sys/types.h>

//#include <sys/prctl.h>
//#include <linux/unistd.h>

#include <stdio.h>
#include <assert.h>

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/weak_ptr.hpp>


namespace Sync {

namespace CurrentThread {
	__thread int t_cachedTid = 0;	
	__thread char t_tidString[32];
	__thread int t_tidStringLength = 6;
	__thread const char* t_threadName = "unknown";
	const bool sameType = boost::is_same<int, pid_t>::value;
	BOOST_STATIC_ASSERT(sameType);

} // namespace CurrentThread

namespace detail {

pid_t gettid() {
//	return static_cast<pid_t>(::syscall(SYS_gettid));
	return pthread_mach_thread_np(pthread_self());
}

struct ThreadData {
	typedef Sync::Thread::ThreadFunc ThreadFunc;
	ThreadFunc func_;
	std::string name_;
	boost::weak_ptr<pid_t> wkTid_;

	ThreadData(const ThreadFunc& func, 
			const std::string& name,
			const boost::shared_ptr<pid_t>& tid) 
		: func_(func),
		name_(name),
		wkTid_(tid) {}

	void runInThread() {
		pid_t tid = Sync::CurrentThread::tid();
		boost::shared_ptr<pid_t> ptid = wkTid_.lock();
		if (ptid) {
			*ptid = tid;
			//remember to release the ownership.
			ptid.reset();
		}

		Sync::CurrentThread::t_threadName = name_.empty() ? "WillThread" : name_.c_str();
	//  mac doesn't support this.
	//	::prctl(PR_SET_NAME, Sync::CurrentThread::t_threadName);
		try {
			func_();
			CurrentThread::t_threadName = "finished";
		} catch (const std::exception& ex) {
			Sync::CurrentThread::t_threadName = "crashed";
			fprintf(stderr, "exception caught in Thread %s\n", name_.c_str());
			fprintf(stderr, "reason: %s\n", ex.what());
			abort();
		} catch (...) {
			Sync::CurrentThread::t_threadName = "crashed";
			fprintf(stderr, "unknown exception caught in Thread %s\n", name_.c_str());
			throw; //rethrow;
		} 

	}

};

void * startThread(void* obj) {
	ThreadData* data = static_cast<ThreadData*>(obj);
	data->runInThread();
	delete data;
	return NULL;
}
} //namespace detail

} //namespace Sync



using namespace Sync;

void CurrentThread::cacheTid() {
	if (t_cachedTid == 0) {
		t_cachedTid = detail::gettid();
		t_tidStringLength = snprintf(t_tidString, sizeof t_tidString, "%5d ", t_cachedTid);
	}
}

bool CurrentThread::isMainThread() {
	return tid() == ::getpid();
}

void CurrentThread::sleepUsec(int64_t usec) {
	struct timespec ts = {0, 0};
	ts.tv_sec = static_cast<time_t>(usec / Timestamp::kMicroSecondsPerSecond);
	ts.tv_nsec = static_cast<time_t>(usec / Timestamp::kMicroSecondsPerSecond * 1000);
	::nanosleep(&ts, NULL);
}

//Thread class implementation.
AtomicInt32 Thread::numCreated_;

Thread::Thread(const ThreadFunc& func, const std::string& n)
	: started_(false),
	  joined_(false),
	  pthreadId_(0),
	  tid_(new pid_t(0)),
	  func_(func),
	  name_(n) {
	setDefaultName();
}

Thread::~Thread() {
	if (started_ && !joined_) {
		pthread_detach(pthreadId_);
	}
}

void Thread::setDefaultName() {
	int num = numCreated_.incrementAndGet();
	if (name_.empty()) {
		char buf[32];
		snprintf(buf, sizeof buf, "Thread%d", num);
		name_ = buf;
	}
}

void Thread::start() {
	assert(!started_);
	started_ = true;

	detail::ThreadData* data = new detail::ThreadData(func_, name_, tid_);
	if (pthread_create(&pthreadId_, NULL, &detail::startThread, data)) {
		started_ = false;
		delete data;
	}
}

int Thread::join() {
	assert(started_);
	assert(!joined_);
	joined_ = true;
	return pthread_join(pthreadId_, NULL);
}
