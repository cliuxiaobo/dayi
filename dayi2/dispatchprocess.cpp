#include "mainwindow.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include "dispatchprocess.h"
#include "basehelper.h"

DispatchProcess::DispatchProcess()
{
    m_audioRecord = new AudioRecorder();
    m_Print =  new FontPrint();
    m_windos = new MainWindow();
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
int DispatchProcess::Webview()
{
    return 0;
}

int DispatchProcess::DispatchSetWebview(int mode,int wige,int high)
{
    m_windos->SetWebWiew(mode,wige,high);
    return 0;
}


int DispatchProcess::ProcessMsg(const QByteArray &message)
{
    int command = BaseHelper::getWebCommandType(message);
    if(0 == command){
        qDebug() << "no obj first head";
        return -1;
    }else if(-1 == command){
        qDebug() << "ProcessMsg:json error!";
        return -1;
    }
    //执行开始录音相关操作
    if(1 == command){
       // m_audioRecord->startRecorder(message);
        m_audioRecord->recvAudioInfo(message);
    }else if(2 == command) {   // 执行打印相关操作
        m_Print->recvPrintInfo(message);
    }
}
