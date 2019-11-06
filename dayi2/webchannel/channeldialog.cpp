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
    emit DispatchProcess::getInstance().emit_ProcessMsg(message);
}
 void WebDialog::SendToWeb(const QString &text)
 {
     emit sendText(text);   // 先回复界面确认收到信息
 }
// 接收通道信息
 void WebDialog::receiveText(const QString &text)
 {
       QByteArray allData = text.toUtf8();
       displayMessage(allData);
}
