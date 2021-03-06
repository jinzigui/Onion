/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-12 20:36:02
**/

#ifndef _POLLER_HPP_
#define _POLLER_HPP_

#include <memory>

#include "event.hpp"

namespace Onion {

namespace tcp {

class Poller
{
	public:
		static const int MaxFd = 1024;

		Poller() = default;

		virtual int  Poll() = 0;
		virtual bool HasEvent(const Event &event) = 0;
		virtual bool AddEvent(const Event &event) = 0;
		virtual bool ModifyEvent(const Event &event) = 0;
		virtual bool RemoveEvent(const Event &event) = 0;
		virtual ~Poller() { }
};

} // namespace tcp

} // namespace Onion

#endif /* _POLLER_HPP_ */