/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Onion
 *    > Description:
 *
 *    > Created Time: 2016-09-10 14:46:34
**/

#include "tcp_client.hpp"
#include "../util/log.hpp"

namespace Onion {

namespace tcp {

ConnectionId TcpClient::AddConnection(const EndPoint &endpoint, const TcpOption &tcpoption)
{
	std::shared_ptr<TcpConnection> con = std::shared_ptr<TcpConnection>( \
		new TcpConnection(endpoint, tcpoption));
	ConnectionId id = ConnectionIdGenreator::Generate();
	if (con.get() && con->Connected()) {
		contexts_[id] = con;
		return id;
	} else {
		WARNING("tcp连接\n%s\n失败 :(", endpoint.ToString().c_str());
		return kInvalidConnectionId;
	}
}

TcpConnection* TcpClient::GetConnection(ConnectionId id)
{
	auto res = contexts_.find(id);
	if (res == contexts_.end()) {
		WARNING("不存在id为 %d 的tcp连接 :(", id);
		return nullptr;
	}
	return res->second.get();
}

bool TcpClient::CloseConnection(ConnectionId id)
{
	auto con = GetConnection(id);
	if (con) {
		con->Close();
		contexts_.erase(id);
	}
	return false;
}

} // namespace tcp

} // namespace Onion
