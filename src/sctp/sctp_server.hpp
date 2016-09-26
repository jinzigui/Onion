/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-24 15:46:34
**/

#ifndef _SCTP_SERVER_HPP_
#define _SCTP_SERVER_HPP_

#include "../util/socket.hpp"
#include "../util/server.hpp"

namespace Onion {

namespace sctp {

using namespace util;

class SctpServer : public Server
{
	public:
		SctpServer(const EndPoint &endpoint):Server(endpoint) { }

		bool Start() override;

		bool Serve() override;

		bool Shut() override;

	private:
		SctpSocket sctp_socket_;
};

} // namespace sctp

} // namespace Onion

#endif /* _SCTP_SERVER_HPP_ */