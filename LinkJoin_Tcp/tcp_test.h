#ifndef TCP_TEST_H
#define TCP_TEST_H

#include <QtWidgets/QMainWindow>
#include <QtNetwork>

#include "ui_tcp_test.h"
#include "LinkJoin_TcpThreadServer.h"
#include "LinkJoin.h"

class TcpTest : public QMainWindow {
    Q_OBJECT
public:
    TcpTest(QWidget *parent = Q_NULLPTR);
    ~TcpTest();

private:
    Ui::TcpTestClass	*_ui;
	LJ_TcpThreadServer	*_server;
	int					_server_state;

	struct sClient {
		int socket_id;
		QString ip;
		int port;
		sClient(const int &socket_id = LJ_INF, const QString &ip = Q_NULLPTR, const int &port = LJ_INF) {
			this->socket_id = socket_id;
			this->ip = ip;
			this->port = port;
		}
		bool  operator==(const sClient &t) {
			return this->socket_id == t.socket_id && this->ip == t.ip && this->port == t.port;
		}
	};
	QList<sClient>			_clients;

	void _RefreshClients(const QList<sClient> &clients);

signals:
	void Signal_SendToClient(const int &socket_id, const QByteArray &data);
	void Signal_DisconnectWithClient(const int &socket_id);

public slots:
	void Slot_ClientConnected(const int &socket_id, const QString &ip, const quint16 &port);	// 客户端连接
	void Slot_ClientReceive(const int &socket_id, const QString &ip, const int &port, const QByteArray &data);	// 客户端发来的数据
	void Slot_ClientDisconnected(const int &socket_id, const QString &ip, const int &port);	// 客户端断开

protected slots:
	void on_pushButton_send_to_client_clicked();
	void on_pushButton_send_to_all_clicked();
	void on_pushButton_disconnected_client_clicked();
	void on_pushButton_start_server_clicked();
};

#endif // TCP_TEST_H
