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

namespace Onion {

namespace util {

class Buffer
{
	public:
		Buffer():buffer_(nullptr) { }
		Buffer(size_t capacity):buffer_(new char[capacity]), length_(0), capacity_(capacity) { }

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

		bool Read(const char *buf, size_t len);
		bool Write(char *buf, size_t &len);

		void Swap(Buffer &buffer) {
			std::swap(buffer_, buffer.buffer_);
			std::swap(begin_, buffer.begin_);
			std::swap(end_, buffer.end_);
			std::swap(length_, buffer.length_);
			std::swap(capacity_, buffer.capacity_);
		}

		~Buffer() {
			if (buffer_) delete [] buffer_;
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
namespace std {

template<>
inline void swap(Onion::util::Buffer &lhs, Onion::util::Buffer &rhs)
{
	lhs.Swap(rhs);
}

}

#endif /* _BUFFER_HPP_ */