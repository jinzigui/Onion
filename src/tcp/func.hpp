/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-13 18:33:09
**/

#ifndef _FUNC_HPP_
#define _FUNC_HPP_

#include <functional>

namespace Onion {

namespace tcp {

using OnSendCallBack = std::function<void(size_t)>;
using OnRecvCallBack = std::function<void(size_t)>;

} // namespace tcp

} // namespace Onion

#endif /* _FUNC_HPP_ */