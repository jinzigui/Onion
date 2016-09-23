/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-23 16:09:04
**/

#include <iostream>

#include "../src/util/log.hpp"
#include "../src/udp/udp_server.hpp"

int main(int argc, char **argv)
{
	using namespace Onion;
	using namespace util;
	using namespace udp;

	UdpServer server(EndPoint(IPAddress(static_cast<uint32_t>(0)), 8000));
	if (!server.Start()) {
		WARNING("udp服务器启动失败 :(");
		return -1;
	}
	server.OnRecv([] (size_t len) {
		std::cout << "receive " << len << std::endl;
	});
	server.OnSend([] (size_t len) {
		std::cout << "send " << len << std::endl;
	});
	server.Serve();

	server.Shut();

	return 0;
}
