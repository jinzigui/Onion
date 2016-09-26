/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-25 15:56:18
**/

#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include "end_point.hpp"
#include "buffer.hpp"
#include "func.hpp"

namespace Onion {

namespace util {

class Server
{
	public:
		Server(const EndPoint &endpoint):end_point_(endpoint) { }

		virtual bool Start() = 0;

		virtual bool Serve() = 0;

		virtual bool Shut() = 0;

		virtual ~Server() { }

		void OnSend(const OnSendCallBack &cb) { on_send_ = cb; }
		void OnRecv(const OnRecvCallBack &cb) { on_recv_ = cb; }

	protected:
		EndPoint end_point_;

		Buffer send_buffer_;
		Buffer recv_buffer_;

		OnSendCallBack on_send_ = nullptr;
		OnRecvCallBack on_recv_ = nullptr;
};

} // namespace util

} // namespace Onion

#endif /* _SERVER_HPP_ */
