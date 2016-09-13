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

#include "tcp_server.hpp"
#include "select_poller.hpp"
#include "poll_poller.hpp"

namespace Onion {

namespace tcp {

TcpServer::TcpServer(const EndPoint &endpoint):end_point_(endpoint)
{
	Buffer tmp1(4096);
	std::swap(send_buffer_, tmp1);
	Buffer tmp2(4096);
	std::swap(recv_buffer_, tmp1);
}

bool TcpServer::Start()
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
#ifdef POLL
	poller_.reset(new PollPoller());
#else
	poller_.reset(new SelectPoller());
#endif

	if (!poller_.get()) {
		WARNING("tcp服务器poller初始化失败 :(");
		return false;
	}
	return true;
}

bool TcpServer::Serve()
{
	Event listen(listen_socket_.fd(), Event::Type::kRead);
	std::vector<int> client(SelectPoller::MaxFd, -1);
	int max_client = 0;
	for (;;) {
		#ifdef POLL
			poller_.reset(new PollPoller());
		#else
			poller_.reset(new SelectPoller());
		#endif
			poller_->AddEvent(Event(listen_socket_.fd(), Event::Type::kRead));

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
			TcpSocket socket;
			if (client[i] < 0) continue;
			socket.SetFd(client[i]);
			if (poller_->HasEvent(Event(socket.fd(), Event::Type::kRead))) {
				ssize_t len = socket.Receive(recv_buffer_.Char(), recv_buffer_.Capacity());
				if (len > 0) {
					recv_buffer_.SetLength(static_cast<size_t>(len));
					send_buffer_.Read(recv_buffer_.Char(), recv_buffer_.Length());
					socket.Send(send_buffer_.Char(), send_buffer_.Length());
				} else if (!len) {
					socket.Close();
					client[i] = -1;
					poller_->RemoveEvent(Event(socket.fd(), Event::Type::kRead));
				} else {
					WARNING("not implemented :(");
				}
			}
			if (!(--ready)) break;
		}
	}
	return true;
}

bool TcpServer::Shut()
{
	listen_socket_.Close();
	std::cout << "tcp服务器关闭 :)\n";
	return true;
}

} // namespace tcp

} // namespace Onion
