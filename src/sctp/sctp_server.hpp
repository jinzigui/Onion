/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-24 15:46:34
**/

#ifndef _SCTP_SERVER_HPP_
#define _SCTP_SERVER_HPP_

#include "../util/socket.hpp"
#include "../util/func.hpp"
#include "../util/buffer.hpp"

namespace Onion {

namespace sctp {

using namespace util;

class SctpServer
{
	public:
		SctpServer(const EndPoint &endpoint):end_point_(endpoint) { }

		bool Start();

		bool Serve();

		void OnSend(const OnSendCallBack &cb) { on_send_ = cb; }
		void OnRecv(const OnRecvCallBack &cb) { on_recv_ = cb; }

	private:
		EndPoint end_point_;

		SctpSocket sctp_socket_;

		Buffer send_buffer_;
		Buffer recv_buffer_;

		OnSendCallBack on_send_ = nullptr;
		OnRecvCallBack on_recv_ = nullptr;
};

} // namespace sctp

} // namespace Onion

#endif /* _SCTP_SERVER_HPP_ */