#include "tcpsocketserver.h"
#include "configmanager.h"

TcpSocketServer::TcpSocketServer(const int port, QObject *parent) :
    QObject(parent),
    m_port(port),
    m_debug(ConfigManager::showDebug())
{
    m_tcp_server = new QTcpServer(this);
    connect(m_tcp_server, &QTcpServer::newConnection,
            this, &TcpSocketServer::newConnection);
    if (!m_tcp_server->listen(QHostAddress::LocalHost, port)) {
        qDebug() << "[TCPServer]::Error: Proxy error:" << m_tcp_server->errorString();
    }
    else {
        qInfo() << "[TCPServer]::Start: Proxy listening on port" << port;
    }
}

TcpSocketServer::~TcpSocketServer()
{
}

void TcpSocketServer::newConnection()
{
    QTcpSocket *l_socket = m_tcp_server->nextPendingConnection();
    m_tcp_client = new TcpSocketClient(l_socket, m_debug, this);
    connect(m_tcp_client, &TcpSocketClient::clientDisconnected,
            this, &TcpSocketServer::onClientDisconnect);
    m_web_client = new WebSocketClient(QUrl(ConfigManager::hostname()), m_debug, this);

    // TCP -> WebSocket
    connect(m_tcp_client, &TcpSocketClient::writeDataToWebsocket,
            m_web_client, &WebSocketClient::writeToSocket);

    // Websocket -> TCP
    connect(m_web_client, &WebSocketClient::onTextMessageProcessed,
            m_tcp_client, &TcpSocketClient::receiveDataFromWebSocket);

    // All connected, start phase 2.
    m_web_client->startWebsocket();
}

void TcpSocketServer::onClientDisconnect()
{
    qInfo() << "[TCPServer]::Info: Disconnected. Destroying connection.";
    if (m_tcp_client != nullptr)
        m_tcp_client->deleteLater();

    if (m_web_client != nullptr)
        m_web_client->deleteLater();
}
