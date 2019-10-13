#include "mainwindow.h"
#include "./webchannel/channeldialog.h"
#include "./audioctl/audiorecorder.h"
#include <QApplication>
#include <QWebEngineView>
#include <QDialog>
#include <QVariantMap>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>
#include <QFileInfo>
#include <QtWebSockets/QWebSocketServer>
int main(int argc, char *argv[])
{
 //   QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    // 创建本地接听
    QWebSocketServer server(QStringLiteral("QWebChannel Standalone Example Server"), QWebSocketServer::NonSecureMode);
    if (!server.listen(QHostAddress::LocalHost, 12345)) {
        qFatal("Failed to open web socket server.");
        return 1;
    }

    // 注册通道
    WebSocketClientWrapper clientWrapper(&server);

    // setup the channel
    QWebChannel channel;
    QObject::connect(&clientWrapper, &WebSocketClientWrapper::clientConnected,
                     &channel, &QWebChannel::connectTo);

    WebDialog dialog;
    channel.registerObject(QStringLiteral("dialog"), &dialog);
    DispatchProcess::getInstance().Webview();
#if 0
    QUrl url = QUrl::fromLocalFile(   "http://localhost/index.html ");
    QWebEngineView view;
    QDesktopServices::openUrl(QStringLiteral("http://39.104.64.52/index.html"));
#endif
   // w.show();

    return a.exec();
}
