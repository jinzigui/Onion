/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-09 17:31:54
**/

#include <iostream>
#include <string.h>
#include <unistd.h>

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
	char send[1024], recv[1024];
	for (; fgets(send, 1024, stdin);) {
		size_t len = strlen(send);
		if (!len) break;
		if (socket.Send(send, len) < 0) {
			WARNING("%s 发送失败 :(", send);
			break;
		}
		sleep(2);
		if (socket.Send(send + 1, len - 1) < 0) {
			WARNING("%s 发送失败 :(", send);
			break;
		}
		if (socket.Receive(recv, 1024) < 0) {
			WARNING("接收失败 :(");
			break;
		}
		recv[len-1] = '\0';
		printf("%s\n", recv);
	}
	socket.Close();
	return 0;
}
