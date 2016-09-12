/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-12 20:46:58
**/

#ifndef _SELECT_POLLER_HPP_
#define _SELECT_POLLER_HPP_

#include <map>

#include "poller.hpp"

namespace Onion {

namespace tcp {

class SelectPoller : public Poller
{
	public:
		bool AddEvent(const Event &event) override;
		bool ModifyEvent(const Event &event) override;
		bool RemoveEvent(const Event &event) override;

	private:
		std::map<int, Event> select_fds_;
		bool FindEvent(const Event &event);
};

} // namespace tcp

} // namespace Onion

#endif /* _SELECT_POLLER_HPP_ */