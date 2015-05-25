#ifndef _H_CURRENT_THREAD
#define _H_CURRENT_THREAD

#include <stdint.h>

namespace Sync {

namespace CurrentThread {

	extern __thread int t_cachedTid;
	extern __thread char t_tidString[32];
	extern __thread const char* t_threadName;
	void cacheTid();
	
	inline int tid() {
		if (__builtin_expect(t_cachedTid == 0, 0)) {
			cacheTid();
		}
		return t_cachedTid;
	}

	inline const char* tidString() {
		return t_tidString;
	}

	inline const char* name() {
		return t_threadName;
	}

	bool isMainThread();

	void sleepUsec(int64_t usec);

} //namespace CurrentThread
} //namespace Sync
#endif
