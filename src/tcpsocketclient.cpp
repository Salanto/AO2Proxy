#include "tcpsocketclient.h"

TcpSocketClient::TcpSocketClient(QTcpSocket *socket, bool debug, QObject *parent) :
    QObject(parent),
    m_socket(socket),
    m_debug(debug)
{
    if (m_debug)
        qInfo() << "[TCPClient]::Connect: Connected AO2-Client on 127.0.0.1 on port" << m_socket->peerPort();

    connect(m_socket, &QAbstractSocket::readyRead,
            this, &TcpSocketClient::receiveDataFromClient);
    connect(m_socket, &QAbstractSocket::disconnected,
            this, &TcpSocketClient::clientDisconnected);
}

void TcpSocketClient::receiveDataFromWebSocket(QString f_message)
{
    m_socket->write(f_message.toUtf8());
    m_socket->flush();
}

void TcpSocketClient::receiveDataFromClient()
{
    QByteArray tcp_message = m_socket->readAll();

    if (m_debug)
        qDebug() << tcp_message;

    if (!tcp_message.endsWith("#%")) {
        partial_packet.append(tcp_message);
        is_segmented = true;
        return;
    }

    if (is_segmented) {
        partial_packet.append(tcp_message);
        tcp_message = partial_packet;
        partial_packet.clear();
        is_segmented = false;
    }

    // Workaround for WebAO bug needing every packet in its own message
    QStringList all_packets = QString::fromUtf8(tcp_message).split("%");
    all_packets.removeLast(); // Remove empty space after final delimiter
    for (const QString &packet : qAsConst(all_packets)) {
        emit writeDataToWebsocket(packet + "%");
    }
}
