/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-10 14:54:31
**/

#ifndef _TCPCONNECTION_HPP_
#define _TCPCONNECTION_HPP_

namespace Onion {

namespace tcp {

class TcpConnection
{
	public:
		TcpConnection(const util::EndPoint &endpoint, const TcpOption &tcpoption= TcpOption())
		:tcp_option_(tcpoption),
		 send_buffer_(tcpoption_.send_buffer_size()), recv_buffer_(tcpoption_.recv_buffer_size()) { }

		bool SendPacket(const std::string &packet);

		bool ReceivePacket();

	private:
		TcpOption tcp_option_;
		util::EndPoint end_point_;
		util::TcpSocket socket_;
		util::Buffer send_buffer_;
		util::Buffer recv_buffer_;
};

} // namespace tcp

} // namespace Onion

#endif /* _TCPCONNECTION_HPP_ */