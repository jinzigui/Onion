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

#include <string>

namespace Onion {

namespace tcp {

class Event
{
	public:
		enum Type { kRead    = 0x1,
								kWrite   = 0x2,
								kExcept  = 0x4
							};

		Event(int fd, int type):fd_(fd), type_(type) { }

		Event& operator=(const Event &event) = default;

		std::string ToString() const {
			char res[32];
			snprintf(res, 32, "fd %d, type %s", fd_, type_ == kRead ? "读" :
																							(type_ == kWrite ? "写" : "Other"));
			return std::string(res);
		}

		int fd() const { return fd_; }

		int type() const { return type_; }

	private:
		int fd_;
		int type_;

};

} // namespace tcp

} // namespace Onion

#endif /* _EVENT_HPP_ */