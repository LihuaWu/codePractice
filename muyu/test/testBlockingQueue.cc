
#include "CurrentThread.h"
#include "BlockingQueue.h"
#include "CountDownLatch.h"

#include <unistd.h>

#include <stdio.h>
#include <string>
#include <algorithm>

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

using namespace Sync;

class Test {
public:
	Test(int numThreads) 
		: threads_(numThreads),
		latch_(numThreads) {
		printf("test started. num of threads=%d\n", numThreads);

		for (int i = 0; i < numThreads; i++) {
			char name[32];
			snprintf(name, sizeof name, "work thread %d", i);
			threads_.push_back(new boost::thread(
				boost::bind(&Test::display, this, name)));
			
		}
	}

	void display(const std::string& threadName) {
		printf("tid=%d, %s started.\n", CurrentThread::tid(), threadName.c_str());
		latch_.countDown();

		bool running = true;
		while(running) {
			printf("tid=%d\n, waiting......\n", CurrentThread::tid());
			std::string d(queue_.take());
			printf("tid=%d, get data = %s, size = %zd\n", CurrentThread::tid(), d.c_str(), queue_.size());
			sleep(2);
			running = (d != "stop");
		}

		printf("tid=%d, %s stopped\n", CurrentThread::tid(), threadName.c_str());
	}

	void run(int times) {
		printf("tid=%d, waiting for count down latch\n", CurrentThread::tid());
		latch_.wait();
		printf("all threads started, msgcount = %d\n", times);

		for (int i = 0; i < times; i++) {
			char buf[32];

			snprintf(buf, sizeof(buf), "hello %d", i);

			printf("%s\n", buf);

			queue_.put(std::string(buf));
			printf("tid=%d, data = %s, size=%zd\n", CurrentThread::tid(), buf, queue_.size());
		}
	}

	void joinAll() {
		for (size_t i = 0; i < threads_.size(); i++) {
			queue_.put("stop");
		}

		std::for_each(threads_.begin(), threads_.end(), boost::bind(&boost::thread::join, _1));
	}

private:
	BlockingQueue<std::string> queue_;
	boost::ptr_vector<boost::thread> threads_;
	CountDownLatch latch_;

};

int main() {

	printf("pid=%d, tid=%d\n", ::getpid(), CurrentThread::tid());

	Test t(2);
	t.run(20);
	t.joinAll();

	return 0;
}

