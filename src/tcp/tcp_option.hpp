/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-10 14:47:24
**/

#ifndef _TCPOPTION_HPP_
#define _TCPOPTION_HPP_

namespace Onion {

namespace tcp {

class TcpOption
{
	public:
		TcpOption(size_t send_buffer_size = 4096, size_t recv_buffer_size = 4096)
		:send_buffer_size_(send_buffer_size), recv_buffer_size_(recv_buffer_size) { }

		size_t send_buffer_size() { return send_buffer_size_; }
		size_t recv_buffer_size() { return recv_buffer_size_; }

	private:
		size_t send_buffer_size_;
		size_t recv_buffer_size_;
};

} // namespace tcp

} // namespace Onion

#endif /* _TCPOPTION_HPP_ */