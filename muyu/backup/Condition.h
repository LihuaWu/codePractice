#ifndef _H_CONDITION
#define _H_CONDITION

#include "Mutex.h"

#include <pthread.h>

#include <boost/noncopyable.hpp>

namespace Sync {

class Condition : boost::noncopyable {
public:
	explicit Condition(MutexLock& mutex)
		:mutex_(mutex) {
		pthread_cond_init(&pcond_, NULL);
	}

	~Condition() {
		pthread_cond_destroy(&pcond_);
	}

	void wait() {
		MutexLock::UnassignGuard ug(mutex_);
		pthread_cond_wait(&pcond_, mutex_.getPthreadMutex());
	}

	//TODO: wait for some time.
	//bool waitForSeconds(int seconds);

	void notify() {
		pthread_cond_signal(&pcond_);
	}

	void notifyAll() {
		pthread_cond_broadcast(&pcond_);
	}

private:
	MutexLock& mutex_;
	pthread_cond_t pcond_;


};

} //namespace Sync 

#endif
