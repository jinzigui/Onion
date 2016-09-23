/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-23 16:08:49
**/

#include <iostream>

#include "../src/udp/udp_client.hpp"
#include "../src/util/log.hpp"

int main(int argc, char **argv)
{
	using namespace Onion;
	using namespace util;
	using namespace udp;

	EndPoint endpoint(IPAddress("127.0.0.1"), 8000);
	UdpClient client(endpoint);
	client.OnSend([] (size_t len) {
		std::cout << "send " << len << std::endl;
	});
	client.OnRecv([] (size_t len) {
		std::cout << "receive " << len << std::endl;
	});
	if (!client.SendTo("hello world :)"))
		WARNING("udp数据报发送失败 :(");
	if (!client.ReceiveFrom())
		WARNING("udp数据报接收失败 :(");

	client.Close();

	return 0;
}
