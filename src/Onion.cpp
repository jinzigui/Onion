/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-08 11:18:49
**/

#include "util/socket.hpp"

using namespace Onion;
using namespace util;

int main(int argc, char **argv)
{
	ListenSocket listensocket;
	if (!listensocket.Create()) return -1;
	if (!listensocket.Listen()) return -1;
	TcpSocket socket;
	EndPoint endpoint(IPAddress("127.0.0.1"), 8000);
	if (!listensocket.Accept(&socket, endpoint)) return -1;
	return 0;
}
