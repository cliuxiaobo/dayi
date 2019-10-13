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
    // 检查是否为json
    // 获取到用户端信息，下发到线下处理服务
    DispatchProcess::getInstance().ProcessMsg(message);
}
// 接收通道信息
 void WebDialog::receiveText(const QString &text)
 {
#if 0
     static int i;
     if(i == 0)
     {
     if(text == "1"){
        DispatchProcess::getInstance().DispatchSetWebview(2,1024,1024);
     }
     qDebug()<< "recv:" + text;
    i = i+1;
    QFile loadFile("D:\\1.json");
    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "could't open projects json";
        return;
    }
    QByteArray allData = loadFile.readAll();
   loadFile.close();
#endif
   QByteArray allData = text.toUtf8();
   displayMessage(allData);
}
