/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-12 20:47:17
**/

#include <vector>
#include <iostream>

#include "select_poller.hpp"
#include "../util/log.hpp"

namespace Onion {

namespace tcp {

using namespace util;

bool SelectPoller::HasEvent(const Event &event)
{
	switch(event.type()) {
		case Event::Type::kRead:
			if (FD_ISSET(event.fd(), &read_fds_))
				return true;
			break;
		case Event::Type::kWrite:
			if (FD_ISSET(event.fd(), &write_fds_))
				return true;
			break;
		case Event::Type::kExcept:
			if (FD_ISSET(event.fd(), &except_fds_))
				return true;
			break;
	}
	return false;
}

bool SelectPoller::AddEvent(const Event &event)
{
	if (event.fd() >= Poller::MaxFd) {
		WARNING("超过select最大连接数 :(");
		return false;
	}
	switch(event.type()) {
		case Event::Type::kRead:
			FD_SET(event.fd(), &read_fds_);
			break;
		case Event::Type::kWrite:
			FD_SET(event.fd(), &write_fds_);
			break;
		case Event::Type::kExcept:
			FD_SET(event.fd(), &except_fds_);
			break;
	}
	if (event.fd() > max_fd_)
		max_fd_ = event.fd();
	return true;
}

bool SelectPoller::RemoveEvent(const Event &event)
{
	// if (event.fd() >= Poller::MaxFd) {
	// 	WARNING("超过select最大连接数，移除事件失败 :(");
	// 	return false;
	// }
	auto error = [event] {
		WARNING("没有事件 %s， 移除事件失败 :(", event.ToString().c_str());
		return false;
	};
	switch(event.type()) {
		case Event::Type::kRead:
			if (FD_ISSET(event.fd(), &read_fds_))
				FD_CLR(event.fd(), &read_fds_);
			else
				return error();
			break;
		case Event::Type::kWrite:
			if (FD_ISSET(event.fd(), &write_fds_))
				FD_CLR(event.fd(), &write_fds_);
			else
				return error();
			break;
		case Event::Type::kExcept:
			if (FD_ISSET(event.fd(), &except_fds_))
				FD_CLR(event.fd(), &except_fds_);
			else
				return error();
			break;
	}
	return true;
}

bool SelectPoller::ModifyEvent(const Event &event)
{
	// if (event.fd() >= Poller::MaxFd) {
	// 	WARNING("超过select最大连接数，修改事件失败 :(");
	// 	return false;
	// }
	auto error = [event] {
		WARNING("没有事件 %s， 修改事件失败:(", event.ToString().c_str());
		return false;
	};
	if (FD_ISSET(event.fd(), &read_fds_)) {
		FD_CLR(event.fd(), &read_fds_);
	} else if (FD_ISSET(event.fd(), &write_fds_)) {
		FD_CLR(event.fd(), &write_fds_);
	} else if (FD_ISSET(event.fd(), &except_fds_)) {
		FD_CLR(event.fd(), &except_fds_);
	} else {
		return error();
	}
	switch(event.type()) {
		case Event::Type::kRead:
			FD_SET(event.fd(), &read_fds_);
			break;
		case Event::Type::kWrite:
			FD_SET(event.fd(), &write_fds_);
			break;
		case Event::Type::kExcept:
			FD_SET(event.fd(), &except_fds_);
			break;
	}
	return true;
}

int SelectPoller::Poll()
{
	return select(max_fd_ + 1, &read_fds_, &write_fds_, &except_fds_, NULL);
}

} // namespace tcp

} // namespace Onion
