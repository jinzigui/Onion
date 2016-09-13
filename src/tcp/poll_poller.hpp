/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-13 19:33:36
**/

#ifndef _POLL_POLLER_HPP_
#define _POLL_POLLER_HPP_

#include <poll.h>

#include "poller.hpp"

namespace Onion {

namespace tcp {

class PollPoller : public Poller
{
	public:
		PollPoller():index_(0) { }

		int  Poll() override;

		bool HasEvent(const Event &event) override;

		bool AddEvent(const Event &event) override;

		bool ModifyEvent(const Event &event) override;

		bool RemoveEvent(const Event &event) override;

	private:
		int index_;
		struct pollfd poll_fds_[Poller::MaxFd];
};

} // namespace tcp

} // namespace Onion

#endif /* _POLL_POLLER_HPP_ */