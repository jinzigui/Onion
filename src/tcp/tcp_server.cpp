/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-11 21:49:42
**/

#include "tcp_server.hpp"

namespace Onion {

namespace tcp {

bool TcpServer::Init()
{
	if (!listen_socket_.Create()) {
		WARNING("tcp服务器监听套接字创建失败 :(");
		return false;
	}
	if (!listen_socket_.Bind(end_point_)) {
		WARNING("tcp服务器监听套接字绑定失败 :(");
		return false;
	}
	if (!listen_socket_.Listen()) {
		WARNING("tcp服务器监听套接字监听失败 :(");
		return false;
	}
	return true;
}

} // namespace tcp

} // namespace Onion
