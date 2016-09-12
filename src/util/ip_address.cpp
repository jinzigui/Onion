/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-08 14:30:10
**/

#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
#include <string.h>

#include "ip_address.hpp"
#include "string_op.hpp"

namespace Onion {

namespace util {

IPAddress::IPAddress(const char *address)
{
	if (!StrToNum(address))
		Clear();
}

IPAddress::IPAddress(uint32_t address)
{
	Resize(IPv4);
	address = htonl(address);
	memcpy(&address_[0], &address, IPv4);
}

bool IPAddress::StrToNum(const char *address)
{
	auto res = StringOperation::SplitByChar(std::string(address), '.');
	if (res.size() != IPv4) return false;
	address_.reserve(IPv4);
	for (auto &each : res) {
		uint32_t n = atoi(each.c_str());
		if (n > 255) return false;
		address_.push_back(static_cast<uint8_t>(n));
	}
	return true;
}

void IPAddress::NumToStr(std::string &address) const
{
	for (size_t i = 0; i != address_.size(); ++i) {
		address.append(std::to_string(static_cast<unsigned>(address_[i])));
		if (i != (address_.size() - 1))
			address.append(1, '.');
	}
}

int IPAddress::Family() const
{
	switch(address_.size()) {
		case IPAddress::IPv4:
			return AF_INET;
		default:
			return AF_UNSPEC;
	}
}

std::string IPAddress::ToString() const
{
	std::string address;
	NumToStr(address);
	std::string res("IP: ");
	res += address;
	return std::move(res);
}

void IPAddress::Print() const
{
	std::cout << ToString() << std::endl;
}

} // namespace util

} // namespace Onion
