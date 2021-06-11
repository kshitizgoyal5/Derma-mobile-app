#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QWidget>
#include <QTcpSocket>
#include <iostream>
#include <QPainter>
#include <QQmlEngine>
#include <QBuffer>
class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    Q_INVOKABLE void writeSocket(QString message);

signals:
    void readImage(const QString& str);
    void newFrame(const QImage& img);
private:
    QTcpSocket* socket;
    qint64 m_size = 0;

public slots:
    void readSocket();
    void discardSocket();
};

#endif // CLIENT_H
