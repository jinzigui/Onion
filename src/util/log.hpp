/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-09 11:49:42
**/

#ifndef _LOG_HPP_
#define _LOG_HPP_

#include <fstream>

namespace Onion {

namespace util {

#define log(level, ...) Logger::GetLogger().Log(level, __FILE__, __LINE__, __func__, __VA_ARGS__)

#define INFO(...)     log(Logger::Info, __VA_ARGS__)
#define WARNING(...)  log(Logger::Warning, __VA_ARGS__)
#define FATAL(...)    log(Logger::Fatal, __VA_ARGS__)

class Logger
{
	public:
		enum LogLevel {Info, Warning, Fatal, None};

		Logger(const char *file);

		void Log(LogLevel level, const char *file, int line, const char *fun, const char *fmt ...);
		static Logger& GetLogger();

	private:
		static const char *LogString[3];

		std::ofstream      out_;
};

} // namespace util

} // namespace Onion

#endif /* _LOG_HPP_ */