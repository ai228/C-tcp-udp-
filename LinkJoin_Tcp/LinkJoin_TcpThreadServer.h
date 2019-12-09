#pragma once

#include <QObject>
#include <QTcpServer>
#include <QThread>

#include "LinkJoin_TcpThreadClient.h"

/*
	TCP多线程服务类 1.0.0
	vanxkr.com vanxkr@qq.com 向宇翔
	2019-12-9 17:20:59
*/
class LJ_TcpThreadServer : public QTcpServer {
	Q_OBJECT
public:
	explicit LJ_TcpThreadServer(QObject *parent = Q_NULLPTR, const int &max_connections = 100);
	~LJ_TcpThreadServer();

	void setMaxPendingConnections(const int &max_connections);	// 重写设置最大连接
	void close();	// 关闭服务器 同时也会断开所有连接

protected:
	void incomingConnection(qintptr socket_id) override;	// 只要出现一个新的连接，就会自动调用这个函数

private:
	int _max_connections;	// 最大连接数
	QHash<int, LJ_TcpThreadClient *> *_tcp_client_map;	// 客户端连接管理

signals:
	void Signal_ClientConnected(const int &socket_id, const QString &ip, const quint16 &port);	// 客户端连接
	void Signal_ClientReceive(const int &socket_id, const QString &ip, const int &port, const QByteArray &data);	// 客户端发来的数据
	void Signal_ClientDisconnected(const int &socket_id, const QString &ip, const int &port);	// 客户端断开

	void Signal_SendToClient(const int &socket_id, const QByteArray &data);	// 发送数据给客户端
	void Signal_DisconnectWithClient(const int &socked_id);	// 主动 断开 客户端 -1为 全部断开

public slots:
	void Slot_SendToClient(const int &socket_id, const QByteArray &data);	// 发给客户端数据
	void Slot_DisconnectWithClient(const int &socket_id);	// 断开与客户端的连接

protected slots:
	void Slot_ClientReceive(const int &socket_id, const QString &ip, const int &port, const QByteArray &data);	// 客户端发来数据
	void Slot_ClientDisconnected(const int &socket_id, const QString &ip, const quint16 &port, QThread *th);	// 客户端断开连接

};
