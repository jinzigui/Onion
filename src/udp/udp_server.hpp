/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-16 17:27:30
**/

#ifndef _UDP_HPP_
#define _UDP_HPP_

#include "../util/socket.hpp"
#include "../util/end_point.hpp"
#include "../util/buffer.hpp"

namespace Onion {

namespace udp {

using namespace util;

class UdpServer
{
	public:
		UdpServer(const EndPoint &endpoint):end_point_(endpoint) { }

		bool Start();

		bool Serve();

		bool Shut();

	private:
		UdpSocket udp_socket_;
		EndPoint end_point_;

		Buffer send_buffer_;
		Buffer recv_buffer_;
};

} // namespace udp

} // namespace Onion

#endif /* _UDP_HPP_ */