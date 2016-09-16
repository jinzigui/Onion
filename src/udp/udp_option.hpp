/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-16 18:00:28
**/

#ifndef _UDP_OPTION_HPP_
#define _UDP_OPTION_HPP_

#include <iostream>

namespace Onion {

namespace udp {

class UdpOption
{
	public:
		UdpOption(size_t send_buffer_size = 4096, size_t recv_buffer_size = 4096)
		:send_buffer_size_(send_buffer_size), recv_buffer_size_(recv_buffer_size) { }

		UdpOption& operator=(const UdpOption &) = default;
		UdpOption(const UdpOption &) = default;

		size_t send_buffer_size() { return send_buffer_size_; }
		size_t recv_buffer_size() { return recv_buffer_size_; }

	private:
		size_t send_buffer_size_;
		size_t recv_buffer_size_;
};

} // namespace udp

} // namespace Onion

#endif /* _UDP_OPTION_HPP_ */