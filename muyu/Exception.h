#ifndef _H_EXCEPTION
#define _H_EXCEPTION

#include <exception>
#include <string>

namespace Sync 
{
class Exception : public std::exception {
public:
	explicit Exception(const char* what);

	explicit Exception(const std::string& what);

	virtual ~Exception() throw();

	virtual const char* what() const throw();
	
	const char* stackTrace() const throw();

private:
	void fillStackTrace();
	std::string message_;
	std::string stack_;
};

} // namespace Sync 
#endif
