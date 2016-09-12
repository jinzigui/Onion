/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-10 12:49:03
**/

#ifndef _TCP_CLIENT_HPP_
#define _TCP_CLIENT_HPP_

#include <map>
#include <memory>

#include "connection_id.hpp"
#include "tcp_connection.hpp"

namespace Onion {

namespace tcp {

class TcpClient
{
	public:
		TcpClient() = default;

		ConnectionId AddConnection(	const EndPoint &endpoint,
																const TcpOption &tcpoption = TcpOption());

		TcpConnection* GetConnection(ConnectionId id);

		bool CloseConnection(ConnectionId id);

		TcpClient(const TcpClient &) = delete;
		TcpClient& operator=(const TcpClient &) = delete;

	private:
		std::map<ConnectionId, std::shared_ptr<TcpConnection>> contexts_;
};

} // namespace tcp

} // namespace Onion

#endif /* _TCP_CLIENT_HPP_ */