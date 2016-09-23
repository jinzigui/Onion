/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-13 17:46:34
**/

#include <iostream>

#include "../src/util/log.hpp"
#include "../src/tcp/tcp_client.hpp"

int main(int argc, char **argv)
{
	using namespace Onion;
	using namespace util;
	using namespace tcp;

	TcpClient client;
	EndPoint endpoint(IPAddress("127.0.0.1"), 8000);
	ConnectionId id = client.AddConnection(endpoint);
	if (id == kInvalidConnectionId) {
		WARNING("Invalid Connection :(");
		return 0;
	}
	auto con = client.GetConnection(id);
	assert(con);
	con->OnSend([] (size_t len) {
		std::cout << "sending " << len << std::endl;
	});
	con->OnRecv([] (size_t len) {
		std::cout << "receiving " << len << std::endl;
	});
	con->Send("hello world");
	if (!con->Receive())
		return -1;
	client.CloseConnection(id);
	return 0;
}
