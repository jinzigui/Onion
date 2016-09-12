/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-12 15:56:41
**/

#ifndef _CONNECTION_ID_HPP_
#define _CONNECTION_ID_HPP_

#include <atomic>

namespace Onion {

namespace tcp {

typedef int32_t ConnectionId;

const ConnectionId kInvalidConnectionId = -1;

class ConnectionIdGenreator
{
	public:
		static ConnectionId Generate();

	private:
		static std::atomic<ConnectionId> curr_id_;
};

} // namespace tcp

} // namespace Onion

#endif /* _CONNECTION_ID_HPP_ */