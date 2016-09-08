/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP
 *    > Description:
 *
 *    > Created Time: 2016-09-08 21:05:11
**/

#include "string_op.hpp"

namespace Onion {

namespace util {

std::vector<std::string> StringOperation::SplitByChar(const std::string &str, const char c)
{
	std::vector<std::string> res;
	size_t start = 0;
	for (size_t i = 0; i != str.size(); ++i) {
		if (str[i] == c) {
			res.push_back(std::string(str.begin() + start, str.begin() + i));
			start = i + 1;
		}
	}
	return std::move(res);
}

} // namespace util

} // namespace Onion
