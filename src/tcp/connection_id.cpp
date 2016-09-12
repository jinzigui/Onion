/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-12 15:59:54
**/

#include "connection_id.hpp"

namespace Onion {

namespace tcp {

std::atomic<ConnectionId> ConnectionIdGenreator::curr_id_(-1);

ConnectionId ConnectionIdGenreator::Generate()
{
	return ++curr_id_;
}

} // namespace tcp

} // namespace Onion
