#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>

class WebSocketClient : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketClient(const QUrl &url, bool debug = true, QObject *parent = nullptr);

    void startWebsocket();

Q_SIGNALS:
    void closed();

public slots:
    void writeToSocket(QString message);

private slots:
    void onConnected();
    void onTextMessageReceived(QString message);
    void onError();

private:
    QWebSocket* m_webSocket;
    QUrl m_url;
    bool m_debug;

signals:
    void onTextMessageProcessed(QString message);
};

#endif // WEBSOCKETCLIENT_H
