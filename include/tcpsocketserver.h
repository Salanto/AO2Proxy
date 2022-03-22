#ifndef TCPSOCKETSERVER_H
#define TCPSOCKETSERVER_H

#include <QObject>
#include <QtNetwork>
#include <QtWebSockets/QWebSocket>
#include "websocketclient.h"
#include "tcpsocketclient.h"

class TcpSocketServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpSocketServer(const int port, bool debug, QObject *parent = nullptr);
    ~TcpSocketServer();

signals:

public slots:

    void newConnection();

    void onClientDisconnect();

private:
    QTcpServer* m_tcp_server;

    const int m_port;
    bool m_debug;

    /**
     * @brief m_tcp_client Represents a legacy client connection from AO2-Client
     */
    TcpSocketClient* m_tcp_client;

    /**
     * @brief m_web_client A dummy client that interacts as a WebAO client.
     */
    WebSocketClient* m_web_client;

    /**
     * @brief m_settings Stores the setting info on bootime.
     */
    QSettings* m_settings;
};

#endif // TCPSOCKETSERVER_H
