/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-13 19:34:58
**/

#include "poll_poller.hpp"
#include "../util/log.hpp"

namespace Onion {

namespace tcp {

using namespace util;

int PollPoller::Poll()
{
	return poll(poll_fds_, index_ + 1, -1);
}

bool PollPoller::HasEvent(const Event &event)
{
	for (int i = 0; i != index_; ++i)
		if (poll_fds_[i].fd == event.fd())
			return true;
	return false;
}

bool PollPoller::AddEvent(const Event &event)
{
	if (event.fd() >= Poller::MaxFd) {
		WARNING("超过poll最大连接数 :(");
		return false;
	}
	poll_fds_[index_].fd = event.fd();
	switch(event.type()) {
		case Event::Type::kRead:
			poll_fds_[index_++].events = POLLIN;
			break;
		case Event::Type::kWrite:
			poll_fds_[index_++].events = POLLOUT;
			break;
		default:
			WARNING("不支持的poll事件 :(");
			return false;
	}
	return true;
}

bool PollPoller::RemoveEvent(const Event &event)
{
	for (int i = 0; i != index_; ++i)
		if (poll_fds_[i].fd == event.fd()) {
			poll_fds_[i].fd = -1;
			return true;
		}
	WARNING("poll中不存在事件 %s :(", event.ToString().c_str());
	return false;
}

bool PollPoller::ModifyEvent(const Event &event)
{
	for (int i = 0; i != index_; ++i)
		if (poll_fds_[i].fd == event.fd()) {
			switch(event.type()) {
				case Event::Type::kRead:
					poll_fds_[i].events = POLLIN;
					break;
				case Event::Type::kWrite:
					poll_fds_[i].events = POLLOUT;
					break;
				default:
					WARNING("不支持的poll事件 :(");
					return false;
			}
		}
	WARNING("poll中不存在事件 %s :(", event.ToString().c_str());
	return false;
}

} // namespace tcp

} // namespace Onion
