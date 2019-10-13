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
    m_windos =  new MainWindow();


}

DispatchProcess::~DispatchProcess()
{
    delete m_audioRecord;
    delete m_Print;
    delete m_windos;
}

// 界面加载完成
void DispatchProcess::adjustLocation()
{
#if 0
  //  qDebug()<< "界面加载完成界面";
  //  this->showMaximized();
   // this->showFullScreen();
    m_view->setZoomFactor(m_view->zoomFactor() + 0.5);
    m_view->showMaximized();
    m_view->show();
    m_start_Screen->close();
#endif
}

void DispatchProcess::run()
{

}
int DispatchProcess::Webview()
{
#if 0
    m_view->setWindowTitle(QString::fromLocal8Bit("扶桑云医"));
    m_view->setWindowIcon(QIcon("fusang.ico"));
    m_view->setContextMenuPolicy(Qt::NoContextMenu);
    connect(m_view, SIGNAL(loadFinished(bool)), SLOT(adjustLocation())); // 注册登录完成事件
    m_view->setUrl(QUrl(QStringLiteral("http://192.168.1.9:8080")));  // 登录界面

    m_start_Screen->resize(1024, 750);
    m_start_Screen->setWindowTitle(QString::fromLocal8Bit("正在启动..."));

   // m_start_Screen->setWindowIcon(QIcon("E:/dayi/adyi2.0/dayi2/res/img/ico/dayi.ico"));
    m_start_Screen->setStyleSheet("border-image:url(./beijin.jpg)");
    m_start_Screen->show();
#endif
    return 0;
}


int DispatchProcess::SetWebTitle(const QByteArray &message)
{
#if 0
    WebTitleData info;
    int ret = BaseHelper::getWebInfo(message,&info);
    if(ret > 0){
        // 设置标题
        m_view->setWindowTitle(info.name);
        return 0;
    }else{
        return -1;
    }
    return -1;
#endif
    return 0;
}

int DispatchProcess::DispatchSetWebview(int mode,int wige,int high)
{
   // m_windos->SetWebWiew(mode,wige,high);
    return 0;
}
#if 0
int DispatchProcess::DispatchRspWeb()
{
    JSONObject obj = new JSONObject();
    obj.put("name", "John");
    obj.put("sex", "male");
    obj.put("age", 22);
    obj.put("is_student", true);
    obj.put("hobbies", new String[] {"hiking", "swimming"});
}
#endif
int DispatchProcess::ProcessMsg(const QByteArray &message)
{
    int command = BaseHelper::getWebCommandType(message);
    qDebug() << command;
    if(0 == command){
        qDebug() << "no code obj";
        return -1;
    }else if(-1 == command){
        qDebug() << "ProcessMsg:json error!";
        return -1;
    }
    //执行开始录音相关操作
    if(101 == command){
       // m_audioRecord->startRecorder(message);
        m_audioRecord->recvAudioInfo(message);
    }else if(102== command) {   // 执行打印相关操作
        m_Print->recvPrintInfo(message);
    }else if(100 == command){ // 修改标题
        SetWebTitle(message);
    }
}
