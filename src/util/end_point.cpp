/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-08 12:10:59
**/

#include <netinet/in.h>
#include <string.h>

#include "end_point.hpp"

namespace Onion {

namespace util {

bool EndPoint::SetAddressTo(struct sockaddr &sockaddr, socklen_t &len) const
{
	if (!port_) return false;

	switch(address_.Family()) {
		case AF_INET: {
			len = sizeof(struct sockaddr_in);
			auto in_address = reinterpret_cast<struct sockaddr_in *>(&sockaddr);
			in_address->sin_family = AF_INET;
			in_address->sin_port = port_;
			memcpy(&in_address->sin_addr, &address_.Address()[0], IPAddress::IPv4);
			break;
		}
		default:
			return false;
	}
	return true;
}

bool EndPoint::SetAddressFrom(const struct sockaddr &sockaddr, const socklen_t len)
{
	auto error = [this] {
		address_.Clear();
		port_ = 0;
		return false;
	};

	switch (len) {
		case sizeof (struct sockaddr_in): {
			auto in_address = reinterpret_cast<const struct sockaddr_in *>(&sockaddr);
			if (in_address->sin_family != AF_INET) return error();
			port_ = ntohs(in_address->sin_port);
			address_.Resize(IPAddress::IPv4);
			memcpy(&address_.Address()[0], &in_address->sin_addr, IPAddress::IPv4);
			break;
		}
		default:
			return error();
	}
	return true;
}

} // namespace util

} // namespace Onion
