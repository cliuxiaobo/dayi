#include "channeldialog.h"


WebDialog::WebDialog(QObject *parent)
    : QObject(parent)
{
    QFileInfo jsFileInfo(QDir::currentPath() + "/qwebchannel.js");
    if (!jsFileInfo.exists())
        QFile::copy(":/qtwebchannel/qwebchannel.js",jsFileInfo.absoluteFilePath());

}


WebDialog::~WebDialog()
{

}

void WebDialog::displayMessage(QByteArray &message)
{

    // 获取到用户端信息，下发到线下处理服务
    DispatchProcess::getInstance().ProcessMsg(message);

    //ui.output->appendPlainText(message);
}
// 接收通道信息
 void WebDialog::receiveText(const QString &text)
 {
     static int i;
     if(text == "1"){
        DispatchProcess::getInstance().DispatchSetWebview(2,1024,1024);
     }
     emit sendText(text);   // 先回复界面确认收到信息
     #if 0
     if(i == 0)
     {
        i = i+1;

        QFile loadFile("E:\\1.json");
        if(!loadFile.open(QIODevice::ReadOnly))
        {
            qDebug() << "could't open projects json";
            return;
        }
        QByteArray allData = loadFile.readAll();
        loadFile.close();
        displayMessage(allData);
     }
     #endif
 }
