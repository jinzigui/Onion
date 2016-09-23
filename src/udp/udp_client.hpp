/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-16 17:44:15
**/

#ifndef _UDP_CLIENT_HPP_
#define _UDP_CLIENT_HPP_

#include <string>

#include "../util/socket.hpp"
#include "../util/end_point.hpp"
#include "../util/buffer.hpp"
#include "../util/func.hpp"
#include "udp_option.hpp"

namespace Onion {

namespace udp {

using namespace util;

class UdpClient
{
	public:
		UdpClient(const EndPoint &endpoint, const UdpOption & = UdpOption());

		bool SendTo(const char *buf, size_t len);
		bool SendTo(const char *buf);
		bool SendTo(const std::string &buf);

		bool ReceiveFrom();

		void OnSend(const OnSendCallBack &cb) { on_send_ = cb; }
		void OnRecv(const OnRecvCallBack &cb) { on_recv_ = cb; }

		bool Close() { return udp_socket_.Close(); }

	private:
		UdpSocket udp_socket_;
		EndPoint  end_point_;

		UdpOption udp_option_;

		Buffer send_buffer_;
		Buffer recv_buffer_;

		OnSendCallBack on_send_ = nullptr;
		OnRecvCallBack on_recv_ = nullptr;
};

} // namespace udp

} // namespace Onion

#endif /* _UDP_CLIENT_HPP_ */