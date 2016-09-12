/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-12 20:31:39
**/

#ifndef _EVENT_HPP_
#define _EVENT_HPP_

namespace Onion {

namespace tcp {

class Event
{
	public:
		enum Type { kNone, kRead, kWrite, kClose };

		Event():fd_(-1) { }

		Event(int fd):fd_(fd) { }

		Event& operator=(const Event &event) = default;

		int fd() const { return fd_; }

	private:
		int fd_;

};

} // namespace tcp

} // namespace Onion

#endif /* _EVENT_HPP_ */