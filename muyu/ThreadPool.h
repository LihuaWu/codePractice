#ifndef _H_THREADPOOL
#define _H_THREADPOOL 

#include "Mutex.h"
#include "Condition.h"

#include "Thread.h"

#include <string>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <deque>

namespace Sync 
{
class ThreadPool : boost::noncopyable {
public:	
	typedef boost::function<void()> Task;
	
	explicit ThreadPool(const std::string& nameArg = std::string("ThreadPool"));
	~ThreadPool();

	void setMaxQueueSize(int maxSize) {maxQueueSize_ = maxSize; }
	void setThreadInitCallback(const Task& cb) {
		threadInitCallback_ = cb;
	}

	void start(int numThreads);
	void stop();

	const std::string& name() const {return name_; }

	size_t queueSize() const;

	void run(const Task& f);

private:
	bool isFull() const;
	void runInThread();
	Task take();

	mutable MutexLock mutex_;
	Condition notEmpty_;
	Condition notFull_;
	std::string name_;
	Task threadInitCallback_;
	boost::ptr_vector<Sync::Thread> threads_;
	std::deque<Task> queue_;
	size_t maxQueueSize_;
	bool running_;
}; //ThreadPool
	

} // namespace Sync 


#endif
