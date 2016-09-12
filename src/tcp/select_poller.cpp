/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-12 20:47:17
**/

#include "select_poller.hpp"
#include "../util/log.hpp"

namespace Onion {

namespace tcp {

using namespace util;

bool SelectPoller::AddEvent(const Event &event)
{
	if (select_fds_.size() > 1024) {
		WARNING("超过select最大连接数 :(");
		return false;
	}
	select_fds_[event.fd()] = event;
	return true;
}

bool SelectPoller::RemoveEvent(const Event &event)
{
	auto res = select_fds_.find(event.fd());
	if (res == select_fds_.end()) {
		WARNING("没有此事件，移除事件失败 :(");
		return false;
	}
	select_fds_.erase(res);
	return true;
}

bool SelectPoller::ModifyEvent(const Event &event)
{
	auto res = select_fds_.find(event.fd());
	if (res == select_fds_.end()) {
		WARNING("没有此事件，修改事件失败 :(");
		return false;
	}
	res->second = event;
	return true;
}

} // namespace tcp

} // namespace Onion
