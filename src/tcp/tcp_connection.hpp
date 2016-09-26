/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-10 14:54:31
**/

#ifndef _TCP_CONNECTION_HPP_
#define _TCP_CONNECTION_HPP_

#include "../util/socket.hpp"
#include "../util/connection.hpp"
#include "tcp_option.hpp"

namespace Onion {

namespace tcp {

using namespace util;

class TcpConnection : public Connection
{
	public:
		TcpConnection(const EndPoint &endpoint, const TcpOption &tcpoption);

		bool Send(const char *buf, size_t len);
		bool Send(const char *buf);
		bool Send(const std::string &buf);

		bool Receive();

		bool Close() override;

	private:
		TcpOption tcp_option_;

		TcpSocket socket_;
};

} // namespace tcp

} // namespace Onion

#endif /* _TCP_CONNECTION_HPP_ */