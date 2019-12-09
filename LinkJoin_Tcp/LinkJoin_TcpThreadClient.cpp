#include <QtConcurrent/QtConcurrent>
#include <QHostAddress>
#include <QElapsedTimer>

#include "LinkJoin_TcpThreadClient.h"

LJ_TcpThreadClient::LJ_TcpThreadClient(const qintptr &socket_descriptor, QObject *parent)
	: QTcpSocket(parent) {
	this->setSocketDescriptor(socket_descriptor);
	this->_socket_id = socket_descriptor;
	connect(this, &LJ_TcpThreadClient::readyRead, this, &LJ_TcpThreadClient::Slot_Receive);
	connect(this, &LJ_TcpThreadClient::disconnected, [&]() {
		//LJ_DEBUG(QStringLiteral("%1:%2:%3 disconnected %4").arg(this->_socket_id).arg(this->peerAddress().toString().remove("::ffff:")).arg(this->peerPort())) << QThread::currentThread();
		emit Signal_DisconnectedWithServer(this->_socket_id, this->peerAddress().toString().remove("::ffff:"), this->peerPort(), QThread::currentThread());	// 发送断开连接的用户信息
		this->deleteLater();
	});
	connect(&__watcher, &QFutureWatcher<QByteArray>::finished, this, &LJ_TcpThreadClient::Slot_StartNext);
	connect(&__watcher, &QFutureWatcher<QByteArray>::canceled, this, &LJ_TcpThreadClient::Slot_StartNext);
	//LJ_DEBUG(QStringLiteral("%1:%2:%3 connected %4").arg(this->_socket_id).arg(this->peerAddress().toString().remove("::ffff:")).arg(this->peerPort())) << QThread::currentThread();
}

LJ_TcpThreadClient::~LJ_TcpThreadClient() {
}

QByteArray LJ_TcpThreadClient::HandleData(const int &socket_id, const QString &ip, const quint16 &port, QByteArray data) {
	return data;
}

void LJ_TcpThreadClient::Slot_SendToClient(const int &socket_id, const QByteArray &data) {	// 发送数据		
	//LJ_DEBUG(QStringLiteral("%1:%2:%3").arg(this->_socket_id).arg(this->peerAddress().toString().remove("::ffff:")).arg(this->peerPort())) << QThread::currentThread();
	if (socket_id == _socket_id) {
		write(data);
	}
}

void LJ_TcpThreadClient::Slot_DisconnectedWithClient(const int & socket_id) {
	if (socket_id == _socket_id || -1 == socket_id) {
		this->disconnectFromHost();
	}
}

void LJ_TcpThreadClient::Slot_Receive() {
	//LJ_DEBUG(QStringLiteral("%1:%2:%3").arg(this->_socket_id).arg(this->peerAddress().toString().remove("::ffff:")).arg(this->peerPort())) << QThread::currentThread();
	auto data = HandleData(this->_socket_id, this->peerAddress().toString().remove("::ffff:"), this->peerPort(), this->readAll());
	emit Signal_SendToServer(this->_socket_id, this->peerAddress().toString().remove("::ffff:"), this->peerPort(), data);
}

void LJ_TcpThreadClient::Slot_StartNext() {
	this->write(__watcher.future().result());
	if (!__datas.isEmpty()) {
		__watcher.setFuture(QtConcurrent::run(this, &LJ_TcpThreadClient::HandleData, this->_socket_id, this->peerAddress().toString().remove("::ffff:"), this->peerPort(), __datas.dequeue()));
	}
}