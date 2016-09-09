/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-09 17:31:54
**/

#include "util/socket.hpp"
#include "util/log.hpp"

using namespace Onion;
using namespace util;

int main(int argc, char **argv)
{
	TcpSocket socket;
	if (!socket.Create()) {
		WARNING("套接字创建失败 :(");
		return -1;
	}
	socket.Print();
	EndPoint server(IPAddress("127.0.0.1"), 8000);
	server.Print();
	if (!socket.Connect(server)) {
		WARNING("套接字连接失败 :(");
		return -1;
	}
	char send[4096];
	for (;;) {

	}

	return 0;
}
