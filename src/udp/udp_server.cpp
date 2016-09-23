/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-16 17:28:42
**/

#include "udp_server.hpp"
#include "../util/log.hpp"

#include <iostream>

namespace Onion {

namespace udp {

bool UdpServer::Start()
{
	if (!udp_socket_.Create()) {
		WARNING("udp服务器套接字创建失败 :(");
		return false;
	}
	if (!udp_socket_.Bind(end_point_)) {
		WARNING("udp服务器套接字绑定失败 :(");
		return false;
	}
	return true;
}

bool UdpServer::Serve()
{
	EndPoint client;
	while (1) {
		ssize_t len = udp_socket_.ReceiveFrom(recv_buffer_.Char(), recv_buffer_.Capacity(), client);
		if (on_recv_) on_recv_(len);
		if (!len) break;
		recv_buffer_.SetLength(static_cast<size_t>(len));
		send_buffer_.Read(recv_buffer_.Char(), recv_buffer_.Length());
		udp_socket_.SendTo(send_buffer_.Char(), send_buffer_.Length(), client);
		if (on_send_) on_send_(len);
	}
	return true;
}

bool UdpServer::Shut()
{
	std::cout << "udp服务器关闭 :)\n";
	return udp_socket_.Close();
}

} // namespace udp

} // namespace Onion
