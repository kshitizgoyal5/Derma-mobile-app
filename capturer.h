#ifndef CAPTURER_H
#define CAPTURER_H

#include <QObject>
class Capturer : public QObject
{
    Q_OBJECT
public:
    explicit Capturer(QObject *parent = nullptr);
public slots:
    void save(QObject *item, const QString &path);
signals:

};

#endif // CAPTURER_H
