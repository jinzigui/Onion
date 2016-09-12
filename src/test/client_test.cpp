/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-09 15:34:11
**/

#include "tests.hpp"

namespace Onion {

namespace test {

using namespace util;
using namespace tcp;

void ClientTest()
{
	TcpClient client;
	EndPoint endpoint(IPAddress("127.0.0.1"), 8000);
	ConnectionId id = client.AddConnection(endpoint);
	if (id == kInvalidConnectionId)
		WARNING("Invalid Connection :(");
	auto con = client.GetConnection(id);
	assert(con);
	con->Send("hello world :)");
	client.CloseConnection(id);
}

} // namespace test

} // namespace Onion
