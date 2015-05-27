#ifndef _H_PROCESSINFO
#define _H_PROCESSINFO

#include <string>

#include  "Timestamp.h"

namespace Sync 
{

namespace ProcessInfo 
{
	pid_t pid();
	std::string pidString();
	uid_t uid();
	std::string username();
	uid_t euid();
	Timestamp startTime();

	int clockTicksPerSecond();
	int pageSize();
//	bool isDebugBuild();

	std::string hostname();
	std::string procname();
	std::string procname(const std::string& stat);
	
	//read /proc/self/status
	std::string procStatus();
	//read /proc/self/stat
	std::string procStat();
	//read /proc/self/task/tid/stat
	std::string threadStat();
	//readlink /proc/self/exe
	std::string exePath();

	int openedFiles();
	int maxOpenFiles();

	struct CpuTime {
		double userSeconds;
		double systemSeconds;

		CpuTime() : userSeconds(0.0), systemSeconds(0.0) {}
	};

	CpuTime cpuTime();

	int numThreads();

	std::vector<pid_t> threads();
} //namespace ProcessInfo

}// namespace Sync 

#endif
