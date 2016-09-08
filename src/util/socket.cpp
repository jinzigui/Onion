/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-08 11:18:30
**/

#include <unistd.h>
#include <cassert>

#include "socket.hpp"

namespace Onion {

namespace util {

void Socket::SetFd(int fd)
{
	if (fd != fd_) {
		assert(Close());
		fd_ = fd;
	}
}

bool Socket::Close()
{
	if (IsValid()) {
		int fd = fd_;
		fd_ = -1;
		return close(fd) == 0;
	}
	return true;
}

bool Socket::Bind(const EndPoint &endpoint)
{
	struct sockaddr sockaddr;
	socklen_t len;
	if (!endpoint.SetAddressTo(sockaddr, len))
		return false;
	return bind(fd_, &sockaddr, len) == 0;
}

bool ListenSocket::Accept(Socket *socket, EndPoint &endpoint, bool restart)
{
	assert(socket);
	struct sockaddr sockaddr;
	socklen_t len = sizeof(sockaddr);
	for (;;) {
		int ret = accept(fd(), &sockaddr, &len);
		if (ret != -1) {
			socket->SetFd(ret);
			endpoint.SetAddressFrom(sockaddr, len);
			return true;
		} else if (!restart) {
			break;
		}
	}
	return false;
}

bool DataSocket::Connect(const EndPoint &endpoint)
{
	struct sockaddr sockaddr;
	socklen_t len;
	if (!endpoint.SetAddressTo(sockaddr, len))
		return false;

	return connect(fd(), &sockaddr, len) == 0;
}

} // namespace util

} // namespace Onion
