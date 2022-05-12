#ifndef TCPSOCKETCLIENT_H
#define TCPSOCKETCLIENT_H

#include <QObject>
#include <QtNetwork/QTcpSocket>

class TcpSocketClient : public QObject
{
    Q_OBJECT

  public:
    explicit TcpSocketClient(QTcpSocket *socket, bool debug, QObject *parent = nullptr);

  signals:
    // Writes data to the Websocket instance.
    void writeDataToWebsocket(QString f_message);

    // Signals a disconnect. This means we have to destroy the connection.
    void clientDisconnected();

  public slots:

    // Reads data from the websocket and sends it to the tcp socket.
    void receiveDataFromWebSocket(QString f_message);

    // Reads data from the AO2-Client
    void receiveDataFromClient();

  private:
    QTcpSocket *m_socket;
    bool m_debug;

    /**
     * @brief Stores partial packets in case they don't all come through the TCP socket at once
     */
    QByteArray partial_packet;

    /**
     * @brief Flag that is set when packets are segmented
     */
    bool is_segmented = false;
};

#endif // TCPSOCKETCLIENT_H
