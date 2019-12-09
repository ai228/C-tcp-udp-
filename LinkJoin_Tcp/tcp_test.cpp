#include "tcp_test.h"

TcpTest::TcpTest(QWidget *parent)
    : QMainWindow(parent)
	, _ui(new Ui::TcpTestClass)
	, _server(new LJ_TcpThreadServer)
	, _server_state(0) {
    _ui->setupUi(this);

	connect(_server, &LJ_TcpThreadServer::Signal_ClientConnected, this, &TcpTest::Slot_ClientConnected);
	connect(_server, &LJ_TcpThreadServer::Signal_ClientReceive, this, &TcpTest::Slot_ClientReceive);
	connect(_server, &LJ_TcpThreadServer::Signal_ClientDisconnected, this, &TcpTest::Slot_ClientDisconnected);
	connect(_server, &LJ_TcpThreadServer::Signal_ClientReceive, this, &TcpTest::Slot_ClientReceive);
	connect(this, &TcpTest::Signal_SendToClient, _server, &LJ_TcpThreadServer::Slot_SendToClient);
	connect(this, &TcpTest::Signal_DisconnectWithClient, _server, &LJ_TcpThreadServer::Slot_DisconnectWithClient);

	QList<QHostAddress> ip_list = QNetworkInterface::allAddresses();
	QStringList ipv4_list;
	for (const auto &ip : ip_list) {
		if (QAbstractSocket::IPv4Protocol == ip.protocol()) {
			ipv4_list.append(ip.toString());
		}
	}
	_ui->label_ip->setText(ipv4_list.join('\n'));
}

TcpTest::~TcpTest() {

}

void TcpTest::_RefreshClients(const QList<sClient>& clients) {
	QString current_client = _ui->comboBox_client->currentText();
	_ui->comboBox_client->clear();
	if (!clients.isEmpty()) {
		QStringList datas;
		for (const auto &client : clients) {
			datas.append(QStringLiteral("[%1]%2:%3").arg(client.socket_id).arg(client.ip).arg(client.port));
		}
		_ui->comboBox_client->addItems(datas);
		if (!current_client.isEmpty()) {
			_ui->comboBox_client->setCurrentText(current_client);
		}
		_ui->pushButton_send_to_client->setEnabled(true);
		_ui->pushButton_send_to_all->setEnabled(true);
		_ui->pushButton_disconnected_client->setEnabled(true);
	} else {
		_ui->pushButton_send_to_client->setEnabled(false);
		_ui->pushButton_send_to_all->setEnabled(false);
		_ui->pushButton_disconnected_client->setEnabled(false);
	}
}

void TcpTest::Slot_ClientConnected(const int &socket_id, const QString &ip, const quint16 &port) {
	QString t_ip = ip;
	_clients.append(sClient(socket_id, t_ip, port));
	_RefreshClients(_clients);
	_ui->textBrowser_server->append(QStringLiteral("[%1]%2:%3 connected").arg(socket_id).arg(t_ip).arg(port));
}

void TcpTest::Slot_ClientReceive(const int &socket_id, const QString &ip, const int &port, const QByteArray &data) {
	QString t_ip = ip;
	_ui->textBrowser_server->append(QStringLiteral("[%1]%2:%3 receive\n%4").arg(socket_id).arg(t_ip).arg(port).arg(QString(data)));
}

void TcpTest::Slot_ClientDisconnected(const int &socket_id, const QString &ip, const int &port) {
	QString t_ip = ip;
	for (const auto &client : _clients) {
		if (socket_id == client.socket_id) {
			_clients.removeOne(client);
		}
	}
	_RefreshClients(_clients);
	_ui->textBrowser_server->append(QStringLiteral("[%1]%2:%3 disconnected").arg(socket_id).arg(t_ip).arg(port));

}

void TcpTest::on_pushButton_send_to_client_clicked() {
	//QString current_client = _ui->comboBox_client->currentText();
	//if (!current_client.isEmpty()) {
	//	int socket_id = current_client.split(QRegExp("[\[\]]"), QString::SkipEmptyParts).first().toInt();
	//	emit Signal_SendToClient(socket_id, _ui->textEdit_to_client->toPlainText().toLatin1());
	//}
	if (!_clients.isEmpty()) {
		emit Signal_SendToClient(_clients[_ui->comboBox_client->currentIndex()].socket_id, _ui->textEdit_to_client->toPlainText().toLatin1());
	}
}

void TcpTest::on_pushButton_send_to_all_clicked() {
	if (!_clients.isEmpty()) {
		for (const auto &client : _clients) {
			emit Signal_SendToClient(client.socket_id, _ui->textEdit_to_client->toPlainText().toLatin1());
		}
	}
}

void TcpTest::on_pushButton_disconnected_client_clicked() {
	if (!_clients.isEmpty()) {
		emit Signal_DisconnectWithClient(_clients[_ui->comboBox_client->currentIndex()].socket_id);
	}
}

void TcpTest::on_pushButton_start_server_clicked() {
	// LJ_DEBUG(QThread::currentThread());
	int port = _ui->spinBox_port->value();
	if (0 == _server_state) {
		_server_state = 1;
		bool ret = _server->listen(QHostAddress::Any, port);
		if (ret) {
			_ui->spinBox_port->setEnabled(false);
			_ui->pushButton_start_server->setText(tr("停止服务"));
			_ui->textBrowser_server->append(tr("服务已启动: %1").arg(port));
		} else {
			_ui->textBrowser_server->append(_server->errorString());
		}
	} else {
		_server_state = 0;
		_server->close();
		_ui->spinBox_port->setEnabled(true);
		_ui->pushButton_start_server->setText(tr("启动服务"));
		_ui->textBrowser_server->append(tr("服务已停止: %1").arg(port));
	}
}