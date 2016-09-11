/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-09 17:23:10
**/

#include <iostream>
#include <string.h>

#include "util/socket.hpp"
#include "util/log.hpp"

using namespace Onion;
using namespace util;

int main()
{
	ListenSocket listensocket;
	if (!listensocket.Create()) {
		WARNING("套接字创建失败 :(");
		return -1;
	}
	listensocket.Print();
	EndPoint server(IPAddress(static_cast<uint32_t>(0)), 8000);
	server.Print();
	if (!listensocket.Bind(server)) {
		WARNING("套接字绑定失败 :(");
		return -1;
	}
	if (!listensocket.Listen()) {
		WARNING("套接字监听失败 :(");
		return -1;
	}
	TcpSocket socket;
	EndPoint client;
	for (;;) {
		if (!listensocket.Accept(&socket, client)) {
			WARNING("套接字接收失败 :(");
			return -1;
		}
		listensocket.Close();
		std::cout << "连接来自 ";
		client.Print();
		char recv[1024];
		ssize_t len;
		while (1) {
			if ((len = socket.Receive(recv, 1024)) < 0) {
				WARNING("接收失败 :(");
				break;
			} else if (!len) {
				WARNING("客户端断开连接 :(");
				break;
			}
			recv[len-1] = '\0';
			printf("长度: %d\n", (int)len);
			printf("内容: %s\n", recv);
			if (socket.Send(recv, len) < 0)
				WARNING("%s 发送失败 :(", send);
		}
		socket.Close();
	}
	return 0;
}
