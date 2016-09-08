/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-08 12:11:39
**/

#ifndef _ENDPOINT_HPP_
#define _ENDPOINT_HPP_

#include <sys/socket.h>

#include "ip_address.hpp"

namespace Onion {

namespace util {

class EndPoint
{
	public:

		EndPoint(const IPAddress &address, uint16_t port):address_(address), port_(port) { }

		bool SetAddressFrom(const struct sockaddr &sockaddr, const socklen_t len);
		bool SetAddressTo(struct sockaddr &sockaddr, socklen_t &len) const;

	private:
		IPAddress  address_;
		uint16_t   port_;
};

} // namespace util

} // namespace Onion

#endif /* _ENDPOINT_HPP_ */