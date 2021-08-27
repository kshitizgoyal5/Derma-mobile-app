#include "capturer.h"
#include <QGraphicsObject>
#include <QPainter>
#include<QStyleOptionGraphicsItem>
#include <QDebug>
Capturer::Capturer(QObject *parent) : QObject(parent)
{

}

void Capturer::save(QObject *imageObj, const QString &path)
{
//    QGraphicsObject item = qobject_cast<QGraphicsObject>(imageObj);

//    if (!item) {
//        qDebug() << "Item is NULL";
//        return;
//    }

//    QImage img(item->boundingRect().size().toSize(), QImage::Format_RGB32);
//    img.fill(QColor(255, 255, 255).rgb());
//    QPainter painter(&img);
//    QStyleOptionGraphicsItem styleOption;
//    item->paint(&painter, &styleOption);
//    img.save(path);

}
