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
		Socket(int fd = -1):fd_(fd) { }

		int fd() const { return fd_; }

		bool IsValid() const { return fd_ != -1; }

		void SetFd(int fd);

		bool Close();

		template<typename T>
		bool GetSockOpt(int level, int optname, T *optval, socklen_t *optlen) const {
			return getsockopt(fd(), level, optname, optval, optlen) == 0;
		}

		template<typename T>
		bool SetSockOpt(int level, int optname, const T &optval) {
			socklen_t optlen = sizeof(optval);
			return setsockopt(fd(), level, optname, &optval, optlen) == 0;
		}

		bool GetReuseAddress(int *val) {
			socklen_t len;
			return GetSockOpt(SOL_SOCKET, SO_REUSEADDR, val, &len);
		}

		bool SetReuseAddress(int val = 1) {
			return SetSockOpt(SOL_SOCKET, SO_REUSEADDR, val);
		}

		bool GetKeepAlive(int *val) {
			socklen_t len;
			return GetSockOpt(SOL_SOCKET, SO_KEEPALIVE, val, &len);
		}
		bool SetKeepAlive(int val = 1) {
			return SetSockOpt(SOL_SOCKET, SO_KEEPALIVE, val);
		}

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

		bool Accept(Socket &socket, EndPoint &endpoint, bool restart = true);
};

class DataSocket : public Socket
{
	public:
		bool Connect(const EndPoint &endpoint);

		ssize_t Send(const void *buf, size_t size, int flags = 0);

		ssize_t Receive(void *buf, size_t size, int flags = 0);
};

class TcpSocket : public DataSocket
{
	public:
		bool Create() { return Socket::Create(); }

		bool ShutDown() { return shutdown(fd(), SHUT_RDWR) == 0; }

		bool ShutDownReceive() { return shutdown(fd(), SHUT_WR) == 0; }

		bool ShutDownRead() { return shutdown(fd(), SHUT_RD) == 0; }
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