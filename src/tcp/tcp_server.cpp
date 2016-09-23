/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-11 21:49:42
**/

#include <vector>
#include <iostream>

#include "../util/log.hpp"
#include "tcp_server.hpp"
#include "select_poller.hpp"
#include "poll_poller.hpp"

namespace Onion {

namespace tcp {

bool TcpServer::Start()
{
	if (!listen_socket_.Create()) {
		WARNING("tcp服务器监听套接字创建失败 :(");
		return false;
	}
	if (!listen_socket_.SetReuseAddress()) {
		WARNING("tcp服务器重复使用地址失败 :(");
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
#ifdef POLL
	poller_ = std::shared_ptr<Poller>(new SelectPoller());
#else
	poller_ = std::shared_ptr<Poller>(new PollPoller());
#endif

	if (!poller_.get()) {
		WARNING("tcp服务器poller初始化失败 :(");
		return false;
	}
	return true;
}

bool TcpServer::Serve()
{
	std::vector<int> client(SelectPoller::MaxFd, -1);
	int max_client = 0;
	Event listen(listen_socket_.fd(), Event::Type::kRead);
	poller_->AddEvent(listen);
	for (;;) {
		int ready = poller_->Poll();
		if (poller_->HasEvent(listen)) {
			TcpSocket socket;
			EndPoint endpoint;
			if (listen_socket_.Accept(socket, endpoint)) {
				poller_->AddEvent(Event(socket.fd(), Event::Type::kRead));
				client[max_client++] = socket.fd();
			}
			if (!(--ready)) continue;
		}
		for (int i = 0; i < max_client; ++i) {
			if (client[i] < 0) continue;
			TcpSocket socket;
			socket.SetFd(client[i]);
			if (poller_->HasEvent(Event(socket.fd(), Event::Type::kRead))) {
				ssize_t len = socket.Receive(recv_buffer_.Char(), recv_buffer_.Capacity());
				if (len > 0) {
					recv_buffer_.SetLength(static_cast<size_t>(len));
					send_buffer_.Read(recv_buffer_.Char(), recv_buffer_.Length());
					socket.Send(send_buffer_.Char(), send_buffer_.Length());
				} else if (!len) {
					client[i] = -1;
					poller_->RemoveEvent(Event(socket.fd(), Event::Type::kRead));
					socket.Close();
				} else {
					return false;
				}
			}
			if (!(--ready)) break;
		}
	}
	return true;
}

bool TcpServer::Shut()
{
	std::cout << "tcp服务器关闭 :)\n";
	return listen_socket_.Close();
}

} // namespace tcp

} // namespace Onion
