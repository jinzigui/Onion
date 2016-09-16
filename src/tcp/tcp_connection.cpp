/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-11 20:48:35
**/

#include <string.h>

#include "../util/log.hpp"
#include "tcp_connection.hpp"

namespace Onion {

namespace tcp {

TcpConnection::TcpConnection(const util::EndPoint &endpoint, const TcpOption &tcpoption)
:connected_(false), tcp_option_(tcpoption), end_point_(endpoint)
{
	if (!socket_.Create()) {
		WARNING("套接字创建失败 :(");
		return ;
	}
	if (!socket_.Connect(endpoint)) {
		WARNING("套接字连接失败 :(");
		return ;
	}
	send_buffer_.SetCapacity(tcp_option_.send_buffer_size());
	recv_buffer_.SetCapacity(tcp_option_.recv_buffer_size());
	connected_ = true;
}

bool TcpConnection::Send(const char *buf, size_t len)
{
	send_buffer_.Read(buf, len);
	std::cout << socket_.fd() << std::endl;
	if (socket_.Send(buf, len) < 0)
		return false;
	if (on_send_)
		on_send_(len);
	return true;
}

bool TcpConnection::Send(const char *buf)
{
	return Send(buf, strlen(buf));
}

bool TcpConnection::Send(const std::string &buf)
{
	return Send(buf.c_str(), buf.size());
}

bool TcpConnection::Close()
{
	connected_ = false;
	return socket_.Close();
}

bool TcpConnection::Receive()
{
	ssize_t len = socket_.Receive(recv_buffer_.Char(), recv_buffer_.Capacity());
	if (len > 0 && on_recv_) {
		on_recv_(len);
		return true;
	}
	return false;
}

} // namespace tcp

} // namespace Onion
