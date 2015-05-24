
#include "Mutex.h"

//#include "Thread.h"
#include "Timestamp.h"

#include <stdio.h>
#include <algorithm>

#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <vector>

using namespace Sync;

MutexLock g_mutex;
std::vector<int> g_vec;
const int kCount = 10 * 1000 * 1000;

void threadFunc() {
	for (int i = 0; i < kCount; i++) {
		MutexLockGuard lock(g_mutex);
		g_vec.push_back(i);
	}
}

int foo() __attribute__ ((noinline));

int g_count = 0;
int foo() {
	MutexLockGuard lock(g_mutex);
	if (!g_mutex.isLockedByThisThread()) {
		printf("FAIL\n");
		return -1;
	}
	++g_count;
	return 0;
}

int main() {
	foo();

	if (g_count != 1) {
		printf("calls twice.\n");
		abort();
	}

	const int kMaxThread = 8;

	g_vec.reserve(kMaxThread * kCount);

	Timestamp start(Timestamp::now());
	for (int i = 0; i < kCount; i++) {
		g_vec.push_back(i);
	}

	printf("single thread without lock %f\n", timeDifference(Timestamp::now(), start));

	start = Timestamp::now();
	threadFunc();
	printf("single thread with lock %f\n", timeDifference(Timestamp::now(), start));

	for (int nthreads = 1; nthreads < kMaxThread; ++nthreads) {
		boost::ptr_vector<boost::thread> threads;

		g_vec.clear();
		start = Timestamp::now();

		for (int i = 0; i < nthreads; i++) {
			threads.push_back(new boost::thread(&threadFunc));
		}

		std::for_each(threads.begin(), threads.end(), boost::bind(&boost::thread::join, _1));	

		printf("%d thread(s) vec size=%ld with lock %f\n", nthreads, g_vec.size(),timeDifference(Timestamp::now(), start));
	}
	
}
