#ifndef CLIENTUDP_H
#define CLIENTUDP_H

#include <QObject>
#include <QWidget>
#include <QUdpSocket>
#include <iostream>
#include <QPainter>
#include <QQmlEngine>
#include <QBuffer>

struct packet_header{
    int magic_4byte;
    int sequence_no;

    int total_cmp_size;

    int packet_index;
    int packet_size;

    int total_packets;
    int packet_no;

    QSize image_size;
    int byte_count;
};

struct packet{
    packet_header header;
    QByteArray data;
};

class ClientUDP : public QObject
{
    Q_OBJECT
public:
    explicit ClientUDP(QObject *parent = nullptr);
    Q_INVOKABLE void writeSocket(QString message);
    Q_INVOKABLE void connectToServer();
    Q_INVOKABLE void disconnectFromserver();
    Q_INVOKABLE QString getPathForSave();

public slots:
    void readSocket();
    void discardSocket();

signals:
    void readImage(const QString& str);
    void newFrame(const QImage& img);

private:
    QUdpSocket* socket;
    qint64 m_size = 0;
    int seq_no = -1;
    int packets_rec = 0;
    int packets_need = 0;
    QByteArray ImageCache;
    std::vector<bool> cacheMask;
    QUdpSocket *socketConnectToServer;
};

#endif // CLIENTUDP_H
