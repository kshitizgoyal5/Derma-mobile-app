#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <client.h>
#include <opencvimageprovider.h>
#include <QQmlContext>
#include <clientudp.h>
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

        QQmlApplicationEngine engine;

        //Client videoStreamer;
        ClientUDP videoStreamer;
        OpencvImageProvider *liveImageProvider(new OpencvImageProvider);

        engine.rootContext()->setContextProperty("VideoStreamer",&videoStreamer);
        engine.rootContext()->setContextProperty("liveImageProvider",liveImageProvider);

        engine.addImageProvider("live",liveImageProvider);

        const QUrl url(QStringLiteral("qrc:/homepage.qml"));

        engine.load(url);

        //QObject::connect(&videoStreamer,&Client::newFrame,liveImageProvider,&OpencvImageProvider::updateImage);
        QObject::connect(&videoStreamer,&ClientUDP::newFrame,liveImageProvider,&OpencvImageProvider::updateImage);
        return app.exec();
}
