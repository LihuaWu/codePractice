#include "ThreadPool.h"
#include "CountDownLatch.h"
#include "CurrentThread.h"

#include <stdio.h>
#include <string>

#include <boost/bind.hpp>

using namespace Sync;

void print() {
	printf("tid=%d\n", CurrentThread::tid());
}

void printString(const std::string& str) {
	printf("%s\n", str.c_str());
	usleep(100 * 1000);
}

void test(int maxSize) {
	printf("Test ThreadPool with max queue size = %d\n", maxSize);
	ThreadPool pool("MainThreadPool");
	pool.setMaxQueueSize(maxSize);
	pool.start(5);

	printf("Adding");
	pool.run(print);
	pool.run(print);

	for (int i = 0; i < 100; i++) {
		char buf[32];	
		snprintf(buf, sizeof buf, "task %d", i);
		pool.run(boost::bind(printString, std::string(buf)));
	}

	printf("Done.\n");
	
	CountDownLatch latch(1);
	pool.run(boost::bind(&CountDownLatch::countDown, &latch));

	latch.wait();
	pool.stop();
}

int main() {
	test(100);
}

