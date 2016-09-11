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
#include <iostream>
#include <errno.h>

#include "socket.hpp"

namespace Onion {

namespace util {

bool Socket::Create()
{
	Close();
	fd_ = socket(AF_INET, SOL_SOCKET, 0);
	return IsValid();
}

void Socket::Print() const
{
	std::cout << "fd: " << fd_ << std::endl;
}

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

bool ListenSocket::Bind(const EndPoint &endpoint)
{
	struct sockaddr sockaddr;
	socklen_t len;
	if (!endpoint.SetAddressTo(sockaddr, len))
		return false;
	return bind(fd(), &sockaddr, len) == 0;
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

ssize_t DataSocket::Send(const void *buf, size_t size, int flags)
{
	for (;;) {
		ssize_t len = send(fd(), buf, size, flags);
		if (len == -1 && errno == EINTR)
			continue;
		return len;
	}
}

ssize_t DataSocket::Receive(void *buf, size_t size, int flags)
{
	for (;;) {
		ssize_t len = recv(fd(), buf, size, flags);
		if (len == -1 && errno == EINTR)
			continue;
		return len;
	}
}

bool UdpSocket::SendTo(const void *buf, size_t size, const EndPoint &endpoint)
{
	struct sockaddr sockaddr;
	socklen_t socklen;
	endpoint.SetAddressTo(sockaddr, socklen);
	ssize_t len = sendto(fd(), buf, size, 0, &sockaddr, socklen);
	if (len > 0)
		return true;
	return false;
}

bool UdpSocket::ReceiveFrom(void *buf, size_t size, EndPoint &endpoint)
{
	struct sockaddr sockaddr;
	socklen_t socklen;
	ssize_t len = recvfrom(fd(), buf, size, 0, &sockaddr, &socklen);
	if (len > 0)
		return true;
	return false;
}

} // namespace util

} // namespace Onion
