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
	public:

		Socket():fd_(-1) { }

		bool Create(int domain, int type, int protocol) {
			return socket(domain, type, protocol) > 0;
		}

		int fd() const { return fd_; }

		bool IsValid() const { return fd_ != -1; }

		void SetFd(int fd);

		bool Close();

		bool Bind(const EndPoint &endpoint);

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
		bool Create() { return Socket::Create(AF_INET, SOCK_STREAM, 0); }
		bool Listen(int backlog = 1024) { return listen(fd(), backlog) == 0; }
		bool Accept(Socket *socket, EndPoint &endpoint, bool restart = true);
};

class DataSocket : public Socket
{
	public:
		bool Connect(const EndPoint &endpoint);

};

class TcpSocket : public DataSocket
{
	public:

	private:

};

} // namespace util

} // namespace Onion

#endif /* _SOCKET_HPP_ */