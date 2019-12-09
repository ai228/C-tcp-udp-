/********************************************************************************
** Form generated from reading UI file 'tcp_test.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCP_TEST_H
#define UI_TCP_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TcpTestClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QSpinBox *spinBox_port;
    QTextEdit *textEdit_to_client;
    QLabel *label;
    QPushButton *pushButton_start_server;
    QSpacerItem *verticalSpacer;
    QTextBrowser *textBrowser_server;
    QLabel *label_ip;
    QPushButton *pushButton_send_to_client;
    QPushButton *pushButton_disconnected_client;
    QComboBox *comboBox_client;
    QLabel *label_2;
    QPushButton *pushButton_send_to_all;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TcpTestClass)
    {
        if (TcpTestClass->objectName().isEmpty())
            TcpTestClass->setObjectName(QString::fromUtf8("TcpTestClass"));
        TcpTestClass->resize(631, 504);
        centralWidget = new QWidget(TcpTestClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        spinBox_port = new QSpinBox(groupBox_2);
        spinBox_port->setObjectName(QString::fromUtf8("spinBox_port"));
        spinBox_port->setMinimum(5001);
        spinBox_port->setMaximum(65535);
        spinBox_port->setValue(6000);

        gridLayout_2->addWidget(spinBox_port, 5, 1, 1, 2);

        textEdit_to_client = new QTextEdit(groupBox_2);
        textEdit_to_client->setObjectName(QString::fromUtf8("textEdit_to_client"));

        gridLayout_2->addWidget(textEdit_to_client, 1, 1, 1, 3);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 4, 1, 1, 1);

        pushButton_start_server = new QPushButton(groupBox_2);
        pushButton_start_server->setObjectName(QString::fromUtf8("pushButton_start_server"));

        gridLayout_2->addWidget(pushButton_start_server, 5, 3, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 3, 1, 1, 3);

        textBrowser_server = new QTextBrowser(groupBox_2);
        textBrowser_server->setObjectName(QString::fromUtf8("textBrowser_server"));

        gridLayout_2->addWidget(textBrowser_server, 0, 0, 7, 1);

        label_ip = new QLabel(groupBox_2);
        label_ip->setObjectName(QString::fromUtf8("label_ip"));

        gridLayout_2->addWidget(label_ip, 4, 2, 1, 2);

        pushButton_send_to_client = new QPushButton(groupBox_2);
        pushButton_send_to_client->setObjectName(QString::fromUtf8("pushButton_send_to_client"));
        pushButton_send_to_client->setEnabled(false);

        gridLayout_2->addWidget(pushButton_send_to_client, 2, 1, 1, 1);

        pushButton_disconnected_client = new QPushButton(groupBox_2);
        pushButton_disconnected_client->setObjectName(QString::fromUtf8("pushButton_disconnected_client"));
        pushButton_disconnected_client->setEnabled(false);

        gridLayout_2->addWidget(pushButton_disconnected_client, 2, 3, 1, 1);

        comboBox_client = new QComboBox(groupBox_2);
        comboBox_client->setObjectName(QString::fromUtf8("comboBox_client"));

        gridLayout_2->addWidget(comboBox_client, 0, 2, 1, 2);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 1, 1, 1);

        pushButton_send_to_all = new QPushButton(groupBox_2);
        pushButton_send_to_all->setObjectName(QString::fromUtf8("pushButton_send_to_all"));
        pushButton_send_to_all->setEnabled(false);

        gridLayout_2->addWidget(pushButton_send_to_all, 2, 2, 1, 1);


        gridLayout->addWidget(groupBox_2, 0, 0, 1, 1);

        TcpTestClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TcpTestClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 631, 23));
        TcpTestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TcpTestClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        TcpTestClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TcpTestClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        TcpTestClass->setStatusBar(statusBar);

        retranslateUi(TcpTestClass);

        QMetaObject::connectSlotsByName(TcpTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *TcpTestClass)
    {
        TcpTestClass->setWindowTitle(QApplication::translate("TcpTestClass", "TcpTest", nullptr));
        groupBox_2->setTitle(QApplication::translate("TcpTestClass", "\346\234\215\345\212\241\345\231\250", nullptr));
        label->setText(QApplication::translate("TcpTestClass", "IP:", nullptr));
        pushButton_start_server->setText(QApplication::translate("TcpTestClass", "\345\220\257\345\212\250\346\234\215\345\212\241", nullptr));
        label_ip->setText(QApplication::translate("TcpTestClass", "127.0.0.1", nullptr));
        pushButton_send_to_client->setText(QApplication::translate("TcpTestClass", "\345\217\221\351\200\201", nullptr));
        pushButton_disconnected_client->setText(QApplication::translate("TcpTestClass", "\346\226\255\345\274\200\350\277\236\346\216\245", nullptr));
        label_2->setText(QApplication::translate("TcpTestClass", "\345\256\242\346\210\267\347\253\257", nullptr));
        pushButton_send_to_all->setText(QApplication::translate("TcpTestClass", "\347\276\244\345\217\221", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TcpTestClass: public Ui_TcpTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCP_TEST_H
