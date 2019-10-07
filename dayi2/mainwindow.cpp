#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
   // ui(new Ui::MainWindow)
{
    #if 1
   // QWebEngineView view;
    qDebug()<< "123456";
    view = new QWebEngineView();
    view->setWindowTitle(QString::fromLocal8Bit("大医云诊所"));
    view->setWindowIcon(QIcon("E:/dayi/adyi2.0/dayi2/res/img/ico/dayi.ico"));
    view->setStyleSheet("border-image:url(E:/dayi/adyi2.0/dayi2/res/img/jiazai.jpg)");
   // view->setUrl(QUrl(QStringLiteral("http://39.104.64.52/index.html")));  // 登录界面
    connect(view, SIGNAL(loadFinished(bool)), SLOT(adjustLocation()));
    view->setUrl(QUrl(QStringLiteral("http://192.168.1.9:8080")));  // 登录界面
   // view->resize(1024, 750);
    qDebug()<< "123456";
  //   view->show();

    // 设置启动界面
    m_start_Screen = new QWidget();
    m_start_Screen->resize(350, 350);
    m_start_Screen->setWindowTitle(QString::fromLocal8Bit("正在启动..."));
    m_start_Screen->setWindowIcon(QIcon("E:/dayi/adyi2.0/dayi2/res/img/ico/dayi.ico"));
    m_start_Screen->setStyleSheet("border-image:url(E:/dayi/adyi2.0/dayi2/res/img/jiazai.jpg)");
    m_start_Screen->show();
#endif

}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
#if 0
    view->resize(this->size());
    view->show();
#endif
}

// 界面加载完成
void MainWindow::adjustLocation()
{
    qDebug()<< "1234321";
    view->show();
    delete m_start_Screen;
}

//
int MainWindow::SetWebWiew(int mode,int wide,int high){
    if(mode == 1){ // 自定义尺寸
        view->resize(wide, high);
    }
    else if(mode == 2)
    {
        QDesktopWidget* pDw = QApplication::desktop();//获得桌面窗体
        QRect rect = pDw->screenGeometry();//获得分辨率
        view->resize(rect.width(), rect.width());
        view->move(0,0);
    }

    return 0;
}



