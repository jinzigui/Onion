/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-11 21:48:12
**/

#ifndef _TCP_SERVER_HPP_
#define _TCP_SERVER_HPP_

#include <memory>

#include "../util/socket.hpp"
#include "../util/server.hpp"
#include "poller.hpp"

namespace Onion {

namespace tcp {

using namespace util;

class TcpServer : public Server
{
	public:
		TcpServer(const EndPoint &endpoint):Server(endpoint) { }

		bool Start();

		bool Serve();

		bool Shut();

	private:
		ListenSocket listen_socket_;

		std::shared_ptr<Poller> poller_;
};

} // namespace tcp

} // namespace Onion

#endif /* _TCP_SERVER_HPP_ */