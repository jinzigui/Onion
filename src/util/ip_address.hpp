/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-08 14:30:01
**/

#ifndef _IPADDRESS_HPP_
#define _IPADDRESS_HPP_

#include <sys/types.h>
#include <stdint.h>
#include <vector>
#include <string>

namespace Onion {

namespace util {

class IPAddress
{
	public:
		static const int IPv4 = 4;

		IPAddress() = default;

		IPAddress(const char *address);
		IPAddress(uint32_t address);

		IPAddress(const IPAddress &address) = default;
		IPAddress& operator=(const IPAddress &address) = default;

		void Clear() { address_.clear(); }
		void Resize(size_t size) { address_.resize(size); }
		void Print() const;
		bool StrToNum(const char *address);
		void NumToStr(std::string &address) const;

		std::vector<uint8_t>& Address() { return address_; }
		const std::vector<uint8_t>& Address() const { return address_; }
		int Family() const;

	private:
		std::vector<uint8_t> address_;
};

} // namespace util

} // namespace Onion

#endif /* _IPADDRESS_HPP_ */