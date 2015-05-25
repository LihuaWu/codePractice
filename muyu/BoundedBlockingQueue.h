#ifndef _H_BOUNDEDBLOCKINGQUEUE
#define _H_BOUNDEDBLOCKINGQUEUE

#include <assert.h>

#include "Mutex.h"

namespace Sync 
{

template <typename T>
class BoundedBlockingQueue : boost::noncopyable {
private:	
	mutable MutexLock	 		mutex_;
	Condition			 		notEmpty_;
	Condition			 		notFull_;
	boost::circular_buffer<T> 	queue_;

public:
	explicit BoundedBlockingQueue(int maxSize) 
		: mutex_(),
		notEmpty_(mutex_),
		notFull_(mutex_),
		queue_(maxSize) { }

	void put(const T& x) {
		MutexLockGuard lock(mutex_);
		while(queue_.full()) {
			notFull_.wait();
		}
		assert(!queue_.full());
		queue_.push_back(x);	
		notEmpty_.notify();
	}

	T take() {
		MutexLockGuard lock(mutex_);
		while (queue_.empty()) {
			notEmpty_.wait();
		}

		assert(!queue_.empty());
		T front(queue_.front());
		queue_.pop_front();
		notFull_.notify();
		return front;
	}

	bool empty() const {
		MutexLockGuard lock(mutex_);
		return queue_.empty();
	}

	bool full() const {
		MutexLockGuard lock(mutex_);
		queue_.full();
	}

	size_t size()  {
		MutexLockGuard lock(mutex_);
		return queue_.size();
	}
	size_t capacity() const {
		MutexLockGuard lock(mutex_);
		return queue_.capacity();
	}
};
} //namespace Sync

#endif
