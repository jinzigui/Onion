/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-10 15:06:25
**/

#include <stdlib.h>
#include <string.h>

#include "buffer.hpp"
#include "log.hpp"

namespace Onion {

namespace util {

bool Buffer::Read(const char *buf, size_t len)
{
	if (len > capacity_) {
		WARNING("写入缓冲区的字符串长度 %d 超过缓冲区限制 %d :(", len, capacity_);
		return false;
	}
	begin_ = 0;
	memcpy(buffer_, buf, len);
	end_ = len;
	length_ = len;
	return true;
}

bool Buffer::Write(char *buf, size_t &len)
{
	memcpy(buffer_, buf, len);
	len = length_;
	return true;
}

} // namespace util

} // namespace Onion
