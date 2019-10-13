#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QWebEngineView(parent)
{
    this->setWindowTitle(QString::fromLocal8Bit("扶桑云医"));
    this->setWindowIcon(QIcon("fusang.ico"));
    this->setContextMenuPolicy(Qt::NoContextMenu);
    connect(this, SIGNAL(loadFinished(bool)), SLOT(adjustLocation())); // 注册登录完成事件
    this->setUrl(QUrl(QStringLiteral("http://192.168.1.9:8080")));  // 登录界面
//    this->setUrl(QUrl(QStringLiteral(BUILD_DIR"/index.html")));   // 调试选项
   // this->resize(1024, 750);

    // 设置启动界面
    m_start_Screen = new QWidget();
    m_start_Screen->resize(1024, 750);
    m_start_Screen->setWindowTitle(QString::fromLocal8Bit("正在启动..."));
    m_start_Screen->setStyleSheet("border-image:url(./beijin.jpg)");
    m_start_Screen->show();
}

MainWindow::~MainWindow()
{
    delete m_start_Screen;
}

// 界面加载完成
void MainWindow::adjustLocation()
{
    qDebug()<< "界面加载完成界面";
    this->showMaximized();
    this->setZoomFactor(this->zoomFactor() + 0.5);
    this->show();
    m_start_Screen->close();
}

//
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

