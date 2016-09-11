/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-10 12:49:03
**/

#ifndef _TCPCLIENT_HPP_
#define _TCPCLIENT_HPP_

namespace Onion {

namespace tcp {

class TcpClient
{
	public:

	private:
		std::vector<std::shared_ptr<TcpConnection>> contexts_;
};

} // namespace tcp

} // namespace Onion

#endif /* _TCPCLIENT_HPP_ */