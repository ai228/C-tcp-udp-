#include <QTcpSocket>

#include "LinkJoin_TcpThreadServer.h"
#include "LinkJoin.h"
#include "LinkJoin_TcpThreadHandle.h"

LJ_TcpThreadServer::LJ_TcpThreadServer(QObject *parent, const int &max_connections)
	: QTcpServer(parent) {
	_tcp_client_map = new QHash<int, LJ_TcpThreadClient *>;
	setMaxPendingConnections(max_connections);
}

LJ_TcpThreadServer::~LJ_TcpThreadServer() {
	emit this->Signal_DisconnectWithClient(-1);
	delete _tcp_client_map;
}

void LJ_TcpThreadServer::setMaxPendingConnections(const int & max_connections) {
	this->QTcpServer::setMaxPendingConnections(max_connections);	// 调用Qtcpsocket函数 设置最大连接数 主要是使maxPendingConnections()依然有效
	this->_max_connections = max_connections;
}

void LJ_TcpThreadServer::close() {
	emit this->Signal_DisconnectWithClient(-1);
	_tcp_client_map->clear();
	QTcpServer::close();
}

void LJ_TcpThreadServer::incomingConnection(qintptr socket_id) {
	if (_tcp_client_map->size() > maxPendingConnections()) {	// 继承重写此函数后 QTcpServer默认的判断最大连接数失效 自己实现
		QTcpSocket tcp;
		tcp.setSocketDescriptor(socket_id);
		tcp.disconnectFromHost();
		return;
	}
	auto th = LJ_TcpThreadHandle::GetInstance().GetThread();
	auto client = new LJ_TcpThreadClient(socket_id);

	connect(client, &LJ_TcpThreadClient::Signal_DisconnectedWithServer, this, &LJ_TcpThreadServer::Slot_ClientDisconnected);	// 断开连接的处理 从列表移除 并释放断开的Tcpsocket 此槽必须实现 线程管理计数也是靠的他
	connect(client, &LJ_TcpThreadClient::Signal_SendToServer, this, &LJ_TcpThreadServer::Slot_ClientReceive);	// 断开连接的处理 从列表移除 并释放断开的Tcpsocket 此槽必须实现 线程管理计数也是靠的他
	connect(this, &LJ_TcpThreadServer::Signal_DisconnectWithClient, client, &LJ_TcpThreadClient::Slot_DisconnectedWithClient);	// 主动 断开 的 信号
	connect(this, &LJ_TcpThreadServer::Signal_SendToClient, client, &LJ_TcpThreadClient::Slot_SendToClient);	// 发送给client

	client->moveToThread(th);	// 把tcp类移动到新的线程 从线程管理类中获取
	_tcp_client_map->insert(socket_id, client);	// 插入到连接信息中
	QString ip = client->peerAddress().toString().remove("::ffff:");
	int port = client->peerPort();
	emit Signal_ClientConnected(socket_id, ip, port);
	//LJ_DEBUG(tr("线程0x%1客户端[%2]%3:%4 已连接").arg(quintptr(th), 8, 16, QLatin1Char('0')).arg(socket_id).arg(ip).arg(port));
}

void LJ_TcpThreadServer::Slot_SendToClient(const int &socket_id, const QByteArray &data) {	// 发给客户端数据
	emit Signal_SendToClient(socket_id, data);
}

void LJ_TcpThreadServer::Slot_ClientReceive(const int &socket_id, const QString &ip, const int &port, const QByteArray &data) {
	emit Signal_ClientReceive(socket_id, ip, port, data);
}

void LJ_TcpThreadServer::Slot_DisconnectWithClient(const int & socket_id) {
	emit Signal_DisconnectWithClient(socket_id);
}

void LJ_TcpThreadServer::Slot_ClientDisconnected(const int &socket_id, const QString &ip, const quint16 &port, QThread *th) {
	_tcp_client_map->remove(socket_id);	// 连接管理中移除断开连接的socket
	//LJ_DEBUG(tr("线程0x%1客户端[%2]%3:%4 已断开").arg(quintptr(th), 8, QLatin1Char('0')).arg(socket_id).arg(ip).arg(port));
	LJ_TcpThreadHandle::GetInstance().ReduceThread(th);	// 告诉线程管理类那个线程里的连接断开了
	emit Signal_ClientDisconnected(socket_id, ip, port);	// 发动断开连接的client信息
}