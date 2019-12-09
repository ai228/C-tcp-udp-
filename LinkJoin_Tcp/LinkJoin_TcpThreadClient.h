#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QFutureWatcher>
#include <QQueue>
#include <QThread>

#include "LinkJoin.h"

class LJ_TcpThreadClient : public QTcpSocket {
	Q_OBJECT
public:
	explicit LJ_TcpThreadClient(const qintptr &socket_descriptor, QObject *parent = Q_NULLPTR);
	~LJ_TcpThreadClient();

	QByteArray HandleData(const int &socket_id, const QString &QString, const quint16 &port, QByteArray data);	// 用来处理数据的函数

protected:
	QFutureWatcher<QByteArray> __watcher;
	QQueue<QByteArray> __datas;

private:
	qintptr _socket_id; //  套接字

signals:
	void Signal_SendToServer(const int &socket_id, const QString &QString, const quint16 &port, const QByteArray &data);	// client发来的数据
	void Signal_DisconnectedWithServer(const int &socket_id, const QString &QString, const quint16 &port, QThread *thread_id);	// 发送断开连接的用户信息 此信号必须发出! 线程管理类根据信号计数的

public slots:
	void Slot_SendToClient(const int &socket_id, const QByteArray &data);	// 发送数据
	void Slot_DisconnectedWithClient(const int &socket_id);	// 断开连接 -1全部断开

protected slots:
	void Slot_Receive();	// 读取数据
	void Slot_StartNext();	// 处理下一个
};
