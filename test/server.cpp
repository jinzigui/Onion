/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-13 17:50:56
**/

#include <iostream>

#include "../src/tcp/tcp_server.hpp"

int main(int argc, char **argv)
{
	using namespace Onion;
	using namespace util;
	using namespace tcp;
	TcpServer server(EndPoint(IPAddress(static_cast<uint32_t>(0)), 8000));
	server.OnRecv([] (size_t len) {
		std::cout << "receive " << len << std::endl;
	});
	server.Start();
	server.Serve();
	server.Shut();
	return 0;
}
