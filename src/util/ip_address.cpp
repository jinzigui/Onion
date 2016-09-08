/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-08 14:30:10
**/

#include <sys/socket.h>

#include "ip_address.hpp"
#include "string_op.hpp"

namespace Onion {

namespace util {

IPAddress::IPAddress(const char *address)
{
	auto res = StringOperation::SplitByChar(std::string(address), '.');
	if (res.size() != IPv4) {
		address_.clear();
		return ;
	}
	address_.reserve(IPv4);
	for (auto &each : res) {
		uint32_t n = atoi(each.c_str());
		if (n > 255) return ;
		address_.push_back(static_cast<uint8_t>(n));
	}
}

int IPAddress::Family() const
{
	switch(address_.size()) {
		case IPAddress::IPv4:
			return AF_INET;
		default:
			return AF_UNSPEC;
	}
}

} // namespace util

} // namespace Onion
