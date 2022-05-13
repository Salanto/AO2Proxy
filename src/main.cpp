#include "configmanager.h"
#include "tcpsocketserver.h"
#include <QCoreApplication>

TcpSocketServer *m_tcp_server;

int main(int argc, char *argv[])
{
    QCoreApplication AOProxy(argc, argv);
    AOProxy.setApplicationName("AProxy");
    AOProxy.setApplicationVersion("1.1");
    m_tcp_server = new TcpSocketServer(ConfigManager::localPort());
    return AOProxy.exec();
}
