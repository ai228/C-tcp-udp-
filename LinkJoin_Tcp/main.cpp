#include "tcp_test.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    TcpTest w;
    w.show();
    return a.exec();
}
