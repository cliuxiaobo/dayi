#include "mainwindow.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<QFile>
#include "dispatchprocess.h"
#include "basehelper.h"
static WebDialog *m_WebObj;


DispatchProcess::DispatchProcess()
{
    m_audioRecord = new AudioRecorder();
    m_Print =  new FontPrint();
    m_windos =  new MainWindow();
     qDebug() << "init emit_ProcessMsg";
    connect(this,SIGNAL(emit_ProcessMsg(const QByteArray)),this,SLOT(slot_ProcessMsg(const QByteArray)));
}

DispatchProcess::~DispatchProcess()
{
    delete m_audioRecord;
    delete m_Print;
    delete m_windos;
}

void DispatchProcess::run()
{

}

#if 0
// 注册回复UI函数
int DispatchProcess::DispatchRegisterWeb(WebDialog *pthis)
{
   // m_windos->SetWebWiew(mode,wige,high);
    return 0;
}
#endif

#if 0
int DispatchProcess::DispatchSetWebview(int mode,int wige,int high)
{
   // m_windos->SetWebWiew(mode,wige,high);
    return 0;
}
#endif
int DispatchProcess::Webview()
{

    return 0;
}

//发送给客户端数据
int DispatchProcess::DispatchRspWeb(int ErrorType, QString ErrorInfo)
{
//创建json对象
    QJsonObject obj;
    QJsonObject sub;
    sub.insert("error_type",QJsonValue(ErrorType));
    sub.insert("error_info",QJsonValue(ErrorInfo));
    obj.insert("data",QJsonValue(sub));
    obj.insert("code",QJsonValue("201"));
    return 0;
}

// 接收线上数据
void DispatchProcess::slot_ProcessMsg(const QByteArray &message)
{
    // 获取code命令
    int command = BaseHelper::getWebCommandType(message);

    if(0 == command){
        qDebug() << "no code obj";
        return;
    }else if(-1 == command){
        qDebug() << "ProcessMsg:json error!";
        return ;
    }
    qDebug() << command;
    if(100 == command){
         m_windos->recvWindowInfo(message);// 界面修改操作
    }else if(101 == command){    // 开始录音
        m_audioRecord->startRecorder(message);
    }else if(102 == command) {   // 执行结束录音
        m_audioRecord->stopRecorder(message);
        //m_Print->recvPrintInfo(message);
    }else if(201 == command){
        QString strHtml;
      //  m_audioRecord->stopRecorder();
        BaseHelper::getWebData(message,strHtml);
        m_Print->printDocumentA4(strHtml);

    }
    return;
}
