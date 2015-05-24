#ifndef _H_COUNTDOWNLATCH
#define _H_COUNTDOWNLATCH

#include "Condition.h"
#include "Mutex.h"

namespace Sync {

class CountDownLatch : boost::noncopyable {
public:
	explicit CountDownLatch(int count);

	void wait();

	void countDown();

	int getCount() const;

private:
	mutable MutexLock mutex_;
	Condition condition_;
	int count_;
};


} //namespace Sync

#endif
