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

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/sctp.h>

#include "end_point.hpp"

namespace Onion {

namespace util {

class Socket
{
	protected:
	bool Create(int level = AF_INET, int protocol = SOCK_STREAM, int flag = 0);

	public:
		Socket(int fd = -1):fd_(fd) { }

		int fd() const { return fd_; }

		bool IsValid() const { return fd_ != -1; }

		void SetFd(int fd);

		bool Close();

		bool Bind(const EndPoint &endpoint);

		template<typename T>
		bool GetOption(int level, int optname, T *optval, socklen_t *optlen) const {
			return getsockopt(fd(), level, optname, optval, optlen) == 0;
		}

		template<typename T>
		bool SetOption(int level, int optname, const T &optval) {
			socklen_t optlen = sizeof(optval);
			return setsockopt(fd(), level, optname, &optval, optlen) == 0;
		}

		bool GetReuseAddress(int *val) {
			socklen_t len;
			return GetOption(SOL_SOCKET, SO_REUSEADDR, val, &len);
		}

		bool SetReuseAddress(int val = 1) {
			return SetOption(SOL_SOCKET, SO_REUSEADDR, val);
		}

		bool GetKeepAlive(int *val) {
			socklen_t len;
			return GetOption(SOL_SOCKET, SO_KEEPALIVE, val, &len);
		}
		bool SetKeepAlive(int val = 1) {
			return SetOption(SOL_SOCKET, SO_KEEPALIVE, val);
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
		bool Create() { return Socket::Create(AF_INET, SOCK_DGRAM); }

		ssize_t SendTo(const void *buf, size_t size, const EndPoint &endpoint);

		ssize_t ReceiveFrom(void * buf, size_t size, EndPoint &endpoint);
};

class SctpSocket : public Socket
{
	public:
		bool Listen(int backlog = 1024) { return listen(fd(), backlog); }

		bool Create() { return Socket::Create(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP); }

		ssize_t SendMsg(const void *buf, size_t size, const EndPoint &endpoint, uint32_t ppid,
			uint32_t flags, uint16_t stream, uint32_t timetolive = 0, uint32_t context = 0);

		ssize_t ReceiveMsg(void *buf, size_t size, EndPoint &endpoint,
			struct sctp_sndrcvinfo *sinfo, int *msg_flags);

};

} // namespace util

} // namespace Onion

#endif /* _SOCKET_HPP_ */