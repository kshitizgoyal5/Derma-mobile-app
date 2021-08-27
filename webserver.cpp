#include "webserver.h"
#include <QHttpMultiPart>
#include <QFile>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

WebServer::WebServer(QObject *parent) : QObject(parent)
{

}

void WebServer::predictImage(QString path, QString url)
{
    qDebug() << "started Request";
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpg"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString("form-data ; name=\"filePath\" ; filename=\"(%1)\"").arg(path)) );

    qDebug() << "Opening File";
    QFile *file = new QFile(path);
    if(!file->open(QIODevice::ReadOnly)){
        qDebug() << "Cannot open";
        delete multiPart;
        return;
    }
    qDebug() << "File Opened";
    imagePart.setBodyDevice(file);
    file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart

    multiPart->append(imagePart);
    QUrl URL(url);

    QNetworkRequest request(URL);
    QNetworkReply *reply;
    reply = manager.post(request, multiPart);
    multiPart->setParent(reply);

    connect(reply, &QNetworkReply::readyRead, this, &WebServer::finished);


}

void WebServer::finished()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    QString replyStr = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(replyStr.toUtf8());
    qInfo() << replyStr;
    QJsonObject jsonObject = jsonResponse.object();
    // response is parsed
    if(jsonObject.find("predictedLabel") == jsonObject.end()){
        emit prediction("error");
    }
    else{
        int label = jsonObject["predictedLabel"].toInt();
        emit prediction(QString::number(label));
    }
    reply->deleteLater();
}
