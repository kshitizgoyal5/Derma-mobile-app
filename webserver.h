#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <QObject>
#include  <QNetworkAccessManager>

class WebServer : public QObject
{
    Q_OBJECT
public:
    explicit WebServer(QObject *parent = nullptr);
    Q_INVOKABLE void predictImage(QString path, QString url);

signals:
    void prediction(QString predic);

public slots:
    void finished();

private:
    QNetworkAccessManager manager;
};

#endif // WEBSERVER_H
