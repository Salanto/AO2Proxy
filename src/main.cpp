#include <QCoreApplication>
#include "tcpsocketserver.h"

TcpSocketServer* m_tcp_server;

int main(int argc, char *argv[])
{
    QCoreApplication AProxy(argc, argv);
    AProxy.setApplicationName("AProxy");
    AProxy.setApplicationVersion("1.0");
    m_tcp_server = new TcpSocketServer(8080,true);
    return AProxy.exec();
}
