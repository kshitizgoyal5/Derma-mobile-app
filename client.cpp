#include "client.h"
#include <QtBluetooth/QBluetoothSocket>
Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket();
    connect(socket, &QTcpSocket::readyRead, this, &Client::readSocket);
    connect(socket, &QTcpSocket::disconnected,
            this, &Client::discardSocket);
    socket->connectToHost("192.168.18.16", 9999);
    if(socket->waitForConnected()){
        qDebug() << "Connected to server";
        socket->write("ok");
    }
    else qDebug() << "Server not found";

}

void Client::writeSocket(QString message)
{
    socket->write("hello");
}

void Client::readSocket()
{
        //QImage image;
        //QString image;
        QByteArray image;
        QSize imgsize;
        int byteCount;
        QDataStream socketStream(socket);
        socketStream.setVersion(QDataStream::Qt_5_11);
        if(m_size == 0){
            if(socket->bytesAvailable() < (int)sizeof(qint64)) return;
            //qDebug() << "bytes recieved = " << socket->bytesAvailable();
            socketStream >> m_size;
            //qDebug() << "Got size = " << m_size;
        }
        if(socket->bytesAvailable() < m_size) return;
        socketStream >> imgsize >> byteCount >> image;
        //socketStream >> image;
        m_size = 0;
        image = qUncompress(image);
        //QString im("data:image/jpg;base64,");
        //im.append(QString::fromLatin1(image.toBase64().data()));
        //qDebug() <<imgsize.width()<<imgsize.height()<<byteCount;
//        if(image.isNull()) qDebug() << "Image is Null";
//        else{
//            //qDebug() << image.height() << image.width() << image.format();
//        }
        //QByteArray bArray;
        //QBuffer buffer(&image);
        //buffer.open(QIODevice::WriteOnly);

        QImage  img = QImage(imgsize.width(), imgsize.height(), QImage::Format_RGB32);

        memcpy(img.bits(), image.data(), byteCount); // We write the image data into the new QImage

        //QString img("data:image/jpg;base64,");
        //img.append(QString::fromLatin1(bArray.toBase64().data()));
        //emit readImage(image);
        emit newFrame(img);
        socket->write("ok");
}

void Client::discardSocket()
{
    socket->deleteLater();
    socket=nullptr;
    qDebug() << "Server Disconnected";
}

