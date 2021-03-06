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

#include <unistd.h>

#include "poller.hpp"

namespace Onion {

namespace tcp {

class SelectPoller : public Poller
{
	public:
		SelectPoller():max_fd_(-1) {
			FD_ZERO(&read_fds_);
			FD_ZERO(&write_fds_);
			FD_ZERO(&except_fds_);
		}

		int  Poll() override;

		bool HasEvent(const Event &event) override;

		bool AddEvent(const Event &event) override;

		bool ModifyEvent(const Event &event) override;

		bool RemoveEvent(const Event &event) override;

	private:
		int    max_fd_;
		fd_set read_fds_;
		fd_set write_fds_;
		fd_set except_fds_;
};

} // namespace tcp

} // namespace Onion

#endif /* _SELECT_POLLER_HPP_ */