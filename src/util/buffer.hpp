/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-10 15:05:16
**/

#ifndef _BUFFER_HPP_
#define _BUFFER_HPP_

#include <string>

namespace Onion {

namespace util {

class Buffer
{
	public:
		Buffer(size_t capacity):buffer_(new char[capacity]), length_(0), capacity_(capacity) { }

		const char* Buffer() const { return buffer_; }
		size_t Length() const { return length_; }
		size_t Capacity() const { return capacity_; }

		bool Read(const std::string &str);
		bool Write(std::string &str);

		~Buffer() { delete [] buffer_; }

	private:
		char  *buffer_;
		size_t length_;
		size_t capacity_;
};

} // namespace util

} // namespace Onion

#endif /* _BUFFER_HPP_ */