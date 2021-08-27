#include "clientudp.h"
#include <iostream>
#include <QNetworkInterface>
#include <QStandardPaths>
/*
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
*/


packet deserialize(const QByteArray& byteArray)
{
    QDataStream stream(byteArray);
    stream.setVersion(QDataStream::Qt_4_5);
    packet pkt;

    stream >> pkt.header.magic_4byte
               >> pkt.header.sequence_no

               >> pkt.header.total_cmp_size
               >> pkt.header.packet_index

               >> pkt.header.packet_size

               >> pkt.header.total_packets
               >> pkt.header.packet_no

               >> pkt.header.image_size
               >> pkt.header.byte_count;
    pkt.data.resize(pkt.header.packet_size);
    stream >> pkt.data;
    return pkt;
}

ClientUDP::ClientUDP(QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket();
    socketConnectToServer = new QUdpSocket();
    connect(socket, &QUdpSocket::readyRead, this, &ClientUDP::readSocket);
    connect(socket, &QUdpSocket::disconnected,
            this, &ClientUDP::discardSocket);

    //socket->connectToHost(QHostAddress("192.168.18.255"), 9999);
    //if(socket->bind(9999, QUdpSocket::ShareAddress)){


}

void ClientUDP::writeSocket(QString message)
{
    socket->write("hello");
}

void ClientUDP::connectToServer()
{
    if(!socket){
        socket = new QUdpSocket();
        connect(socket, &QUdpSocket::readyRead, this, &ClientUDP::readSocket);
        connect(socket, &QUdpSocket::disconnected,
                this, &ClientUDP::discardSocket);
    }

    if(socket->bind(QHostAddress::AnyIPv4, 9999)){
        qDebug() << "Connected to server";
    }
    else qDebug() << "Server not found";

    QByteArray datagram = "HI";
    QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();

    // Interfaces iteration
    for (int i = 0; i < ifaces.size(); i++)
    {
        // Now get all IP addresses for the current interface
        QList<QNetworkAddressEntry> addrs = ifaces[i].addressEntries();

        // And for any IP address, if it is IPv4 and the interface is active, send the packet
        for (int j = 0; j < addrs.size(); j++)
            if ((addrs[j].ip().protocol() == QAbstractSocket::IPv4Protocol) && (addrs[j].broadcast().toString() != ""))
                for(int i=0; i<10; i++)
                while(socketConnectToServer->writeDatagram(datagram.data(), datagram.length(), addrs[j].broadcast(), 45454) == -1) qDebug() << "Failed";
    }
}

void ClientUDP::disconnectFromserver()
{
    if(socket != nullptr){
        socket->close();
    }

}

QString ClientUDP::getPathForSave()
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    //path = path.mid(8, -1);
    return path;
}

void ClientUDP::readSocket()
{
        //qDebug() << "Ready Read";
        QByteArray PKT;
        PKT.resize(socket->pendingDatagramSize());
        socket->readDatagram(PKT.data(), PKT.size());
        packet pkt = deserialize(PKT);
        if(pkt.header.magic_4byte != 69696) return;
        if(pkt.data.size() != pkt.header.packet_size) return;

        if(pkt.header.sequence_no != seq_no){
            //qDebug() << "NEW Image";
            seq_no = pkt.header.sequence_no;
            ImageCache.clear();
            ImageCache.resize(pkt.header.total_cmp_size);
            cacheMask = std::vector<bool>(pkt.header.total_packets, 0);
            for(int i=0; i<pkt.header.packet_size; i++){
                ImageCache[i + pkt.header.packet_index] = pkt.data[i];
            }
            cacheMask[pkt.header.packet_no] = 1;
            packets_rec = 1;
            packets_need = pkt.header.total_packets;
        }
        else{
            if(cacheMask[pkt.header.packet_no]) return;
            for(int i=0; i<pkt.header.packet_size; i++){
                ImageCache[i + pkt.header.packet_index] = pkt.data[i];
            }
            cacheMask[pkt.header.packet_no] = 1;
            packets_rec++;
        }
        qDebug() << pkt.header.packet_no << pkt.header.total_packets;
        if(packets_rec == packets_need){
            qDebug() << "NEW Image";
            packets_need = -1;
            packets_rec = 0;
            QByteArray IMAGE_DATA;
            IMAGE_DATA = qUncompress(ImageCache);
            QImage img = QImage(pkt.header.image_size.width(), pkt.header.image_size.height(), QImage::Format_RGB32);
            for(int i=0; i<pkt.header.byte_count; i++){
                img.bits()[i] = IMAGE_DATA.data()[i];
            }
            emit newFrame(img);
        }
}

void ClientUDP::discardSocket()
{
    socket->deleteLater();
    socket=nullptr;
    qDebug() << "Server Disconnected";
}

