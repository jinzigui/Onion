/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-24 15:46:57
**/

#include <memory.h>

#include "sctp_server.hpp"
#include "../util/log.hpp"

namespace Onion {

namespace sctp {

bool SctpServer::Start()
{
	if (!sctp_socket_.Create()) {
		WARNING("sctp服务器套接字创建失败 :(");
		return false;
	}
	if (!sctp_socket_.Bind(end_point_)) {
		WARNING("sctp服务器套接字绑定失败 :(");
		return false;
	}

	struct sctp_event_subscribe event;
	memset(&event, 0, sizeof(event));
	event.sctp_data_io_event = 1;
	if (!sctp_socket_.SetOption(IPPROTO_SCTP, SCTP_EVENTS, &event))
		return false;

	if (!sctp_socket_.Listen()) {
		WARNING("sctp服务器套接字监听失败 :(");
		return false;
	}
	return true;
}

bool SctpServer::Serve()
{
	int flag;
	struct sctp_sndrcvinfo info;
	for (;;) {
		EndPoint endpoint;
		ssize_t len = sctp_socket_.ReceiveMsg(recv_buffer_.Char(), recv_buffer_.Capacity(),
			endpoint, &info, &flag);
		if (len < 0) {
			WARNING("sctp服务器接收信息失败 :(");
			return false;
		}
		if (on_recv_) on_recv_(len);
		recv_buffer_.SetLength(len);
		send_buffer_.Read(recv_buffer_.Char(), recv_buffer_.Length());
		sctp_socket_.SendMsg(send_buffer_.Char(), send_buffer_.Length(), endpoint,
			info.sinfo_ppid, info.sinfo_flags, info.sinfo_stream);
		if (on_send_) on_send_(len);
	}
	return true;
}

bool SctpServer::Shut()
{
	std::cout << "sctp服务器关闭 :)\n";
	return sctp_socket_.Close();
}

} // namespace sctp

} // namespace Onion
