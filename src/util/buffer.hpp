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
#include <assert.h>
#include <iostream>

namespace Onion {

namespace util {

class Buffer
{
	public:
		Buffer(size_t capacity = 4096)
		:buffer_(new char[capacity]), length_(0), capacity_(capacity) { }

		Buffer& operator=(const Buffer &) = delete;

		Buffer(const Buffer &) = delete;

		char* Char() { return buffer_; }
		const char* Char() const { return buffer_; }

		size_t Length() const { return length_; }

		void SetLength(size_t length) {
			assert(length < capacity_);
			length_ = length;
		}

		size_t Capacity() const { return capacity_; }

		bool SetCapacity(size_t capacity) {
			if (capacity != Capacity()) {
				capacity_ = capacity;
				if (buffer_)
					delete [] buffer_;
				buffer_ = new char[capacity_];
				if (!buffer_) return false;
			}
			return true;
		}

		bool Read(const char *buf, size_t len);
		bool Write(char *buf, size_t &len);

		~Buffer() {
			if (buffer_) delete [] buffer_;
		}

		friend std::ostream& operator<<(std::ostream &os, const Buffer &buffer) {
			os << "长度: " << buffer.length_ << std::endl;
			os << "内容: " << buffer.buffer_ << std::endl;
			return os;
		}

	private:
		char  *buffer_;
		size_t begin_;
		size_t end_;
		size_t length_;
		size_t capacity_;
};

} // namespace util

} // namespace Onion

#endif /* _BUFFER_HPP_ */