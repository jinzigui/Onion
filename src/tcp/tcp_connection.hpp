/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-10 14:54:31
**/

#ifndef _TCP_CONNECTION_HPP_
#define _TCP_CONNECTION_HPP_

#include "../util/socket.hpp"
#include "../util/buffer.hpp"
#include "../util/end_point.hpp"
#include "../util/func.hpp"
#include "tcp_option.hpp"

namespace Onion {

namespace tcp {

using namespace util;

class TcpConnection
{
	public:
		TcpConnection(const util::EndPoint &endpoint, const TcpOption &tcpoption);

		bool Connected() const { return connected_; }

		bool Send(const char *buf, size_t len);
		bool Send(const char *buf);
		bool Send(const std::string &buf);

		bool Receive();

		void OnSend(const OnSendCallBack &cb) { on_send_ = cb; }
		void OnRecv(const OnRecvCallBack &cb) { on_recv_ = cb; }

		const Buffer& SendBuffer() const { return send_buffer_; }
		const Buffer& RecvBuffer() const { return recv_buffer_; }

		bool Close();

	private:
		bool      connected_;
		TcpOption tcp_option_;
		EndPoint  end_point_;
		TcpSocket socket_;
		Buffer    send_buffer_;
		Buffer    recv_buffer_;

		OnSendCallBack on_send_ = nullptr;
		OnSendCallBack on_recv_ = nullptr;
};

} // namespace tcp

} // namespace Onion

#endif /* _TCP_CONNECTION_HPP_ */