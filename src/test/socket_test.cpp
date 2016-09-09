/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-09 15:34:11
**/

#include <time.h>
#include <iostream>

#include "tests.hpp"

namespace Onion {

namespace test {

void SocketTest()
{
	using namespace util;

	ListenSocket listensocket;
	if (!listensocket.Create()) {
		WARNING("套接字创建失败 :(");
		return ;
	}
	EndPoint server(IPAddress("127.0.0.1"), 8000);
	if (!listensocket.Bind(server)) {
		WARNING("套接字绑定失败 :(");
		return ;
	}
	if (!listensocket.Listen()) {
		WARNING("套接字监听失败 :(");
		return ;
	}
	listensocket.Print();
	server.Print();
}

} // namespace test

} // namespace Onion
