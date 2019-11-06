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
#include <qapplication.h>
#include <stdio.h>
#include <stdlib.h>
#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <QSharedMemory>
#include <QProcess>
static QFile *file = NULL;
void MessageOutput(QtMsgType type,const QMessageLogContext& context,const QString& msg)
{
    QString txtMessage;
    QMutex mutex;
    //加锁
    mutex.lock();
    //设置log输出格式
    txtMessage += QString("[%1][%2][%3]")
            .arg(QTime::currentTime().toString("hh:mm:ss.zzz"))
            .arg(context.file)
            .arg(context.function);
    switch (type) {
    case QtDebugMsg:
        txtMessage += QString("[Debug] %1").arg(msg);
        break;
    case QtWarningMsg:
        txtMessage += QString("[Warning] %1").arg(msg);
        break;
    case QtCriticalMsg:
        txtMessage += QString("[Critical] %1").arg(msg);
        break;
    case QtFatalMsg:
        txtMessage += QString("[Fatal] %1").arg(msg);
        abort();
        break;
    default:
        txtMessage += QString("[UnKnown] %1").arg(msg);
        break;
    }
    txtMessage += QString(",{%1}").arg(context.line);
    txtMessage += QString("\r\n");
    //输出到文件(写，追加模式)
    QFile file("D:\111\qDebug.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream out(&file);
        out<<txtMessage;
    }
    file.flush();
    file.close();
    // 解锁
     mutex.unlock();
}

void SFUpdateServer()
{
    int res = 1;

    if(res)
    {
        QProcess process;
        QString path = QCoreApplication::applicationDirPath() + "/SFUpdateServer.exe";

      //  process.startDetached(path,"192.168.1.119");
        system("taskkill /im ChemiClient.exe /f || pause");
    }

}


int main(int argc, char *argv[])
{
 //   QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    //确保应用程序唯一运行
    QSharedMemory shared("fushang"); //随便填个名字就可以
    if (shared.attach())
    {
        return 0;
    }
    shared.create(1);
    // 注册日志系统
  //  qInstallMsgHandler(customMessageHandler); //注册MsgHandler回调函数
 //   qInstallMessageHandler(MessageOutput);

    // 检查升级状态
   // SFUpdateServer();

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
   // w.show();

    return a.exec();
}
