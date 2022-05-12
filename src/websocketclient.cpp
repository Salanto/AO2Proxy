#include "websocketclient.h"

WebSocketClient::WebSocketClient(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),
    m_url(url),
    m_debug(debug)
{
    if (m_debug)
        qDebug() << "[Websocket]::Info: WebSocket server:" << url;
    m_webSocket = new QWebSocket();
    connect(m_webSocket, &QWebSocket::disconnected, this, &WebSocketClient::closed);
    connect(m_webSocket, &QWebSocket::textMessageReceived, this, &WebSocketClient::onTextMessageReceived);
    connect(m_webSocket, &QWebSocket::connected, this, &WebSocketClient::onConnected);
    connect(m_webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
            this, &WebSocketClient::onError);
    connect(m_webSocket, &QWebSocket::stateChanged,
            this, &WebSocketClient::onStateChanged);
}

void WebSocketClient::startWebsocket()
{
    QNetworkRequest l_request(QUrl(QStringLiteral("ws://ao.fantacrypt.com:80")));
    l_request.setHeader(QNetworkRequest::UserAgentHeader, "AO2ClientWebsocketProxy");
    if (m_debug)
        qDebug() << "[Websocket]::Info: Connecting to" << m_url.toString();
    m_webSocket->open(l_request);
}

void WebSocketClient::onTextMessageReceived(QString message)
{
    if (m_debug)
        qDebug() << "[Websocket]::Network: Message received:" << message;
    emit onTextMessageProcessed(message);
}

void WebSocketClient::onError()
{
    m_webSocket->errorString();
}

void WebSocketClient::onStateChanged(QAbstractSocket::SocketState f_state)
{
    qDebug() << "[Websocket]::StateChange:" << f_state;
    if (f_state == QAbstractSocket::SocketState::UnconnectedState)
        emit closed();
}

void WebSocketClient::writeToSocket(QString message)
{
    m_webSocket->sendTextMessage(message);
}

void WebSocketClient::onConnected()
{
    if (m_debug)
        qDebug() << "[Websocket]::Info: Connected.";
}
