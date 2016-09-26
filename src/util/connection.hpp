/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-25 16:22:21
**/

#ifndef _CONNECTION_HPP_
#define _CONNECTION_HPP_

#include "end_point.hpp"
#include "buffer.hpp"
#include "func.hpp"

namespace Onion {

namespace util {

class Connection
{
	public:
		Connection(const EndPoint &endpoint):connected_(false), end_point_(endpoint) { }

		bool Connected() const { return connected_; }

		void OnSend(const OnSendCallBack &cb) { on_send_ = cb; }
		void OnRecv(const OnRecvCallBack &cb) { on_recv_ = cb; }

		const Buffer& SendBuffer() const { return send_buffer_; }
		const Buffer& RecvBuffer() const { return recv_buffer_; }

		virtual bool Close() = 0;

		virtual ~Connection() { }

	protected:
		bool      connected_;

		EndPoint  end_point_;

		Buffer    send_buffer_;
		Buffer    recv_buffer_;

		OnSendCallBack on_send_ = nullptr;
		OnSendCallBack on_recv_ = nullptr;
};

} // namespace util

} // namespace Onion

#endif /* _CONNECTION_HPP_ */