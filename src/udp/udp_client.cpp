/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-16 17:45:26
**/

#include "udp_client.hpp"
#include "../util/log.hpp"

#include <string.h>

namespace Onion {

namespace udp {

UdpClient::UdpClient(const EndPoint &endpoint, const UdpOption &udpoption)
:end_point_(endpoint), udp_option_(udpoption)
{
	if (!udp_socket_.Create())
		WARNING("udp客户套接字创建失败 :(");
	send_buffer_.SetCapacity(udp_option_.send_buffer_size());
	recv_buffer_.SetCapacity(udp_option_.recv_buffer_size());
}

bool UdpClient::SendTo(const char *buf, size_t len)
{
	return udp_socket_.SendTo(buf, len, end_point_);
}

bool UdpClient::SendTo(const std::string &str)
{
	return SendTo(str.c_str(), str.size());
}

bool UdpClient::SendTo(const char *buf)
{
	size_t len = strlen(buf);
	return SendTo(buf, len);
}

bool UdpClient::ReceiveFrom()
{
	EndPoint endpoint;
	bool flag = udp_socket_.ReceiveFrom(recv_buffer_.Char(), recv_buffer_.Capacity(), endpoint);
	if (endpoint != end_point_) return false;
	return flag;
}

} // namespace udp

} // namespace Onion
