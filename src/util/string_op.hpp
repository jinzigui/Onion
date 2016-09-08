/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP
 *    > Description:
 *
 *    > Created Time: 2016-09-08 21:00:33
**/

#ifndef _STRINGOP_HPP_
#define _STRINGOP_HPP_

#include <vector>
#include <string>

namespace Onion {

namespace util {

class StringOperation
{
	public:
		static std::vector<std::string> SplitByChar(const std::string &str, const char c);
};

} // namespace util

} // namespace Onion

#endif /* _STRINGOP_HPP_ */