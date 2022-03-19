#include "websocketclient.h"

WebSocketClient::WebSocketClient(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),
    m_url(url),
    m_debug(debug)
{
    if (m_debug)
        qDebug() << "WebSocket server:" << url;
    m_webSocket = new QWebSocket();
    connect(m_webSocket, &QWebSocket::disconnected, this, &WebSocketClient::closed);
    connect(m_webSocket, &QWebSocket::textMessageReceived, this, &WebSocketClient::onTextMessageReceived);
    connect(m_webSocket, &QWebSocket::connected, this, &WebSocketClient::onConnected);
    connect(m_webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
            this, &WebSocketClient::onError);
}

void WebSocketClient::startWebsocket()
{
    if (m_debug)
        qDebug() << "Starting websocket to host: " << m_url;
    m_webSocket->open(m_url);
}

void WebSocketClient::onTextMessageReceived(QString message)
{
    if (m_debug)
            qDebug() << "Message received:" << message;
    emit onTextMessageProcessed(message);
}

void WebSocketClient::onError()
{
    m_webSocket->errorString();
}

void WebSocketClient::writeToSocket(QString message)
{
    m_webSocket->sendTextMessage(message);
}

void WebSocketClient::onConnected()
{
    if (m_debug)
        qDebug() << "Connected.";

}

