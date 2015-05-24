#ifndef _H_MUTEX
#define _H_MUTEX

#include "CurrentThread.h"

#include <assert.h>
#include <pthread.h>

#include <boost/noncopyable.hpp>


namespace Sync {

class MutexLock : boost::noncopyable {
public:
	MutexLock() {
		pthread_mutex_init(&mutex_, NULL);
	}

	~MutexLock() {
		pthread_mutex_destroy(&mutex_);
	}

	bool isLockedByThisThread() const {
		return holder_ == CurrentThread::tid();
	}

	void assertLocked() const {
		assert(isLockedByThisThread());
	}

	void lock() {
		pthread_mutex_lock(&mutex_);
		assignHolder();
	}

	void unlock() {
		unassignHolder();
		pthread_mutex_unlock(&mutex_);
		
	}

	pthread_mutex_t* getPthreadMutex() {
		return &mutex_;
	}

private:
	friend class Condition;

	class UnassignGuard : boost::noncopyable {
	public:
		UnassignGuard(MutexLock& owner) : owner_(owner) {owner_.unassignHolder();}
		~UnassignGuard() {owner_.assignHolder(); }

	private:
		MutexLock& owner_;
	};

	void unassignHolder() {holder_ = 0;}
	void assignHolder() {holder_ = CurrentThread::tid(); }

	pid_t holder_;
	pthread_mutex_t mutex_;
};

class MutexLockGuard : boost::noncopyable {
public:
	explicit MutexLockGuard(MutexLock& mutex)
		:mutex_(mutex) {
		mutex.lock();
	}

	~MutexLockGuard() {
		mutex_.unlock();
	}

private:
	MutexLock& mutex_;
};

} //namespace Sync

//avoid misuse of MutexLockGuard
//#define MutexLockGuard(x) error "Missing guard object name"

#endif


