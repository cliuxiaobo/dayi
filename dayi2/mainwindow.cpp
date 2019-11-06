#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QWebEngineView(parent)
{
    this->setWindowTitle(QString::fromLocal8Bit("扶桑云医"));
    this->setWindowIcon(QIcon("fusang.ico"));


    //设置热键模式
    m_escAct = new QAction(this);
    m_escAct->setShortcut(Qt::Key_Escape);
    connect(m_escAct, &QAction::triggered, this,&MainWindow::slot_KeyLocation);
    this->addAction(m_escAct);
    this->setContextMenuPolicy(Qt::NoContextMenu);  // 屏蔽右键
    connect(this, SIGNAL(loadFinished(bool)), SLOT(adjustLocation())); // 注册登录完成事件
    this->setUrl(QUrl(QStringLiteral("http://192.168.1.9:8080")));  // 登录界面
    // 设置启动界面
    m_start_Screen = new QWidget();
    m_start_Screen->resize(1024, 750);
    m_start_Screen->setWindowTitle(QString::fromLocal8Bit("正在启动..."));
    m_start_Screen->setStyleSheet("border-image:url(E:\qidong.jpg)");
    m_start_Screen->activateWindow();
    m_start_Screen->show();

#if 0
    // 新建一个按钮，作为刷新使用
   m_backBtn = new QPushButton(this);
   m_backBtn->resize(100,30);
   m_backBtn->move(0,0);
   m_backBtn->setText(tr("reload"));
   connect(m_backBtn, SIGNAL(clicked(bool)), this, SLOT(onBackBtnClicked()));
#endif
}

MainWindow::~MainWindow()
{
    delete m_start_Screen;
    delete m_escAct;
}

void MainWindow::slot_KeyLocation()
{
    this->reload();
}

// 界面加载完成
void MainWindow::adjustLocation()
{
    static int i;
    if(i == 0)
    {
        i = i+1;
        qDebug()<< "界面加载完成界面";
        this->showMaximized();
        this->setZoomFactor(this->zoomFactor() + 0.5);
        this->activateWindow();
        this->show();
        m_start_Screen->close();
    }
}
int MainWindow::SetWebTitle(const QByteArray &message)
{
    WebTitleData info;
    int ret = BaseHelper::getWebInfo(message,&info);
    if(ret > 0){
        // 设置标题
        this->setWindowTitle(info.name);
        qDebug() << info.id;
        BaseHelper::SetHospitalInfo(info.name,info.id);
        return 0;
    }else{
        return -1;
    }
    return 0;

}

int MainWindow::recvWindowInfo(const QByteArray &message)
{
    return SetWebTitle(message);
}

int MainWindow::SetWebWiew(int mode,int wide,int high){
    if(mode == 1){ // 自定义尺寸
        this->resize(wide, high);
    }
    else if(mode == 2)
    {
        QDesktopWidget* pDw = QApplication::desktop();//获得桌面窗体
        QRect rect = pDw->screenGeometry();//获得分辨率
        this->resize(rect.width(), rect.width());
        this->move(0,0);
    }

    return 0;
}

// 点击界面按钮刷新
void MainWindow::onBackBtnClicked()
{
    this->reload();
    return;
}


