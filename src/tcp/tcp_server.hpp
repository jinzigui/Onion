/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-11 21:48:12
**/

#ifndef _TCP_SERVER_HPP_
#define _TCP_SERVER_HPP_

#include <memory>

#include "../util/log.hpp"
#include "../util/socket.hpp"
#include "../util/buffer.hpp"
#include "poller.hpp"
#include "func.hpp"

namespace Onion {

namespace tcp {

using namespace util;

class TcpServer
{
	public:
		TcpServer(const EndPoint &endpoint);

		bool Start();

		bool Serve();

		bool Shut();

		void OnRecv(const OnRecvCallBack &cb) { on_recv_ = cb; }
		void OnSend(const OnSendCallBack &cb) { on_send_ = cb; }

	private:
		ListenSocket listen_socket_;
		EndPoint     end_point_;

		Buffer send_buffer_;
		Buffer recv_buffer_;

		std::shared_ptr<Poller> poller_;

		OnSendCallBack on_send_ = nullptr;
		OnSendCallBack on_recv_ = nullptr;
};

} // namespace tcp

} // namespace Onion

#endif /* _TCP_SERVER_HPP_ */