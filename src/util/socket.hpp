/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-08 11:02:57
**/

#ifndef _SOCKET_HPP_
#define _SOCKET_HPP_

#include <sys/socket.h>

#include "end_point.hpp"

namespace Onion {

namespace util {

class Socket
{
	protected:
		bool Create();

	public:
		Socket():fd_(-1) { }

		int fd() const { return fd_; }

		bool IsValid() const { return fd_ != -1; }

		void SetFd(int fd);

		bool Close();

		void Print() const;

		Socket(const Socket &) = delete;
		Socket& operator=(const Socket &) = delete;

		virtual ~Socket() { };

	private:
		int fd_;
};

class ListenSocket : public Socket
{
	public:
		ListenSocket() = default;

		bool Create() { return Socket::Create(); }

		bool Bind(const EndPoint &endpoint);

		bool Listen(int backlog = 1024) { return listen(fd(), backlog) == 0; }

		bool Accept(Socket *socket, EndPoint &endpoint, bool restart = true);
};

class DataSocket : public Socket
{
	public:
		bool Connect(const EndPoint &endpoint);

		bool Send(const void *buf, size_t size, int flags = 0);

		bool Receive(void *buf, size_t size, int flags = 0);
};

class TcpSocket : public DataSocket
{
	public:
		bool Create() { return Socket::Create(); }

		bool ShutDown() { return shutdown(fd(), SHUT_RDWR) == 0; }

		bool ShutDownReceive() { return shutdown(fd(), SHUT_WR) == 0; }

		bool ShutDownRead() { return shutdown(fd(), SHUT_RD) == 0; }

	private:

};

class UdpSocket : public DataSocket
{
	public:
		bool Create() { return Socket::Create(); }

		bool SendTo(const void *buf, size_t size, const EndPoint &endpoint);
		bool ReceiveFrom(void * buf, size_t size, EndPoint &endpoint);
};

} // namespace util

} // namespace Onion

#endif /* _SOCKET_HPP_ */