/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-09 11:49:52
**/

#include <iostream>
#include <fcntl.h>
#include <stdarg.h>
#include <assert.h>

#include "log.hpp"

namespace Onion {

namespace util {

Logger::Logger(const char *file)
{
	out_.open(file, std::ios::out | std::ios::trunc);
	assert(out_.is_open());
}

Logger& Logger::GetLogger()
{
	static Logger logger("log");
	return logger;
}

const char *Logger::LogString[3] = {
	"INFO", "WARNING", "FATAL"
};

void Logger::Log(	LogLevel level, const char *file, int line, const char *fun,
									const char *fmt ...)
{
	char buf[1024];
	char *ptr = buf, *end = buf + sizeof(buf);
	ptr += snprintf(ptr, end - ptr, "%s: %s\n%s: %d\n", LogString[level], file, fun, line);
	va_list args;
	va_start(args, fmt);
	ptr += vsnprintf(ptr, end - ptr, fmt, args);
	va_end(args);
	*ptr++ = '\n';
	*ptr++ = '\0';
	out_ << buf;
	if (out_.bad()) {
		std::cerr << "日志I/O错误 :(\n";
		exit(-1);
	}
	std::cerr << buf << std::endl;
}

} // namespace util

} // namespace Onion
