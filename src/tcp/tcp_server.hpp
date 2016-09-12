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

#include "../util/log.hpp"
#include "../util/socket.hpp"

namespace Onion {

namespace tcp {

using namespace util;

class TcpServer
{
	public:
		TcpServer(const EndPoint &endpoint):end_point_(endpoint) { }


	private:
		ListenSocket listen_socket_;
		TcpSocket    serve_scoket_;
		EndPoint     end_point_;

		bool Init();
};

} // namespace tcp

} // namespace Onion

#endif /* _TCP_SERVER_HPP_ */