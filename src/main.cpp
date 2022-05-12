#include "tcpsocketserver.h"
#include <QCoreApplication>

TcpSocketServer *m_tcp_server;

int main(int argc, char *argv[])
{
    QCoreApplication AOProxy(argc, argv);
    AOProxy.setApplicationName("AProxy");
    AOProxy.setApplicationVersion("1.0");
    m_tcp_server = new TcpSocketServer(8080, true);
    return AOProxy.exec();
}
