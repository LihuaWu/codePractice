#include "CurrentThread.h"
#include "Mutex.h"
#include "Thread.h"
#include "Timestamp.h"

#include <stdio.h>

#include <map>
#include <string>

#include <boost/bind.hpp>

Sync::MutexLock g_mutex;
std::map<int, int> g_delays;

using namespace Sync;

void threadFunc() {
	printf("tid=%d\n", CurrentThread::tid());
}

void threadFunc2(Timestamp start) {
	Sync::Timestamp now(Timestamp::now());
	int delay = static_cast<int>(timeDifference(now, start) * 1000000);
	MutexLockGuard lock(g_mutex);
	++g_delays[delay];
	
}

int main() {
	printf("pid=%d, tid=%d\n", ::getpid(), CurrentThread::tid());
	Timestamp start(Timestamp::now());

	int kThreads = 100 * 1000;

	for (int i = 0; i < kThreads; i++) {
		Thread t1(threadFunc);
		t1.start();
		t1.join();
	}

	double timeUsed = timeDifference(Timestamp::now(), start);
	printf("thread creation time %f us\n", timeUsed * 1000000 / kThreads);
	printf("number of created threads %d\n", Thread::numCreated());


	for (int i = 0; i < kThreads; ++i) {
		Timestamp now(Timestamp::now());
		Thread t2(boost::bind(threadFunc2, now));
		t2.start();
		t2.join();
	}

	{
		MutexLockGuard lock(g_mutex);
		for (std::map<int, int>::iterator it = g_delays.begin();
			it != g_delays.end(); ++it) {
			printf("delay=%d, count=%d\n", it->first, it->second);
		}
	}
	return 0;
}

