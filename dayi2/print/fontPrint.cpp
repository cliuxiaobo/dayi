#include "./fontPrint.h"
#include <QProgressDialog>
#include <QPainter>
#include <QTextDocument>
#include <QMainWindow>
#include <QDialog>
#include <QVariantMap>
#include <type_traits>

#include <QWebEngineView>
#include <QDialog>
#include <QVariantMap>
#include <QDesktopServices>


#include <QtCore/QSettings>

#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QPlainTextEdit>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QtPrintSupport/QPrinter>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QInputDialog>

#include <QWebEngineHistory>
#include <QWebEngineProfile>
#include <QWebEngineSettings>

#include <QtCore/QDebug>


#include "../basehelper.h"
#include "./orderpix.h"


#if 0
template<typename Arg, typename R, typename C>
struct InvokeWrapper {
    R *receiver;
    void (C::*memberFun)(Arg);
    void operator()(Arg result) {
        (receiver->*memberFun)(result);
    }
};

typedef QList<QTreeWidgetItem *> StyleItems;

template<typename Arg, typename R, typename C>
InvokeWrapper<Arg, R, C> invoke(R *receiver, void (C::*memberFun)(Arg))
{
    InvokeWrapper<Arg, R, C> wrapper = {receiver, memberFun};
    return wrapper;
}

FontPrint::FontPrint()
{
    agreeWith = 190;    // 57mm 纸
    agreeHigh = 800;
}

FontPrint::~FontPrint()
{

}

// 最多5个
int FontPrint::getPrintDeviceList()
{

    return 0;

}

// 打印门诊病历单
int FontPrint::PrintDocumentDrug(const QByteArray &message,bool flag)
{
#if 0
    WebPrintBodyInfo bodyInfo;
    WebHeadInfo headInfo;
    WebPrintADInfo ADinfo;
    WebPrintDrugInfo drugArray[100];
    BaseHelper::getWebInfo(message,&headInfo);
    BaseHelper::getWebInfo(message,&ADinfo);
    int drugNum = BaseHelper::getWebInfo(message,drugArray);
    int ret = BaseHelper::getWebInfo(message,&bodyInfo);
    if(ret < 0 ){
        return -1;
    }
    // 订单头部信息
    OrderHeadInfo order;
    order.doctorName = headInfo.userName;
    order.hospitalNmane = headInfo.hostName;
    order.hospitalTelephone = "18708518284";

    // 设置打印信息
    OrderPix pixVoucher;
    pixVoucher.setPixHeadInfo(order); // 设置头信息
    pixVoucher.setPixInfo(ADinfo); // 设置广告部分
    pixVoucher.setPixInfo(bodyInfo); // 设置body信息
    pixVoucher.setPixDrugInfo(drugArray,drugNum);

    pixVoucher.agreeTempPrintSize(&agreeWith,&agreeHigh); //协商打印尺寸
    QFile loadFile("D:\\2.html");
    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "could't open projects json";
        return 0;
    }
#endif
    QByteArray allData = loadFile.readAll();
   loadFile.close();
    QString strHtml;
    strHtml.append(allData);

    printDocumentA4(strHtml, 1);
#if 0
    // 获取打印模板
    m_pix =new QPixmap(agreeWith,agreeHigh);
    pixVoucher.GetDrugTemplate(m_pix);  // 获取打印信息

    if(flag == 1) //打印预览
    {
        printPreview();
    }else{ //直接打印
        createprinter();
    }
    delete[] m_pix;
#endif
}

// 打印取号ID
int FontPrint::PrintDocumentVoucher(const QByteArray &message,bool flag)
{
    WebPrintBodyInfo bodyInfo;
    WebHeadInfo headInfo;
    WebPrintADInfo ADinfo;
    BaseHelper::getWebInfo(message,&headInfo);
    BaseHelper::getWebInfo(message,&ADinfo);
    int ret = BaseHelper::getWebInfo(message,&bodyInfo);
    if(ret < 0 ){
        return -1;
    }
    //设置打印图像尺寸
    OrderPix pixVoucher;
    OrderHeadInfo order;
    order.doctorName = headInfo.userName;
    order.hospitalNmane = headInfo.hostName;
    order.hospitalTelephone = "1234";
    pixVoucher.setPixHeadInfo(order);
    pixVoucher.setPixInfo(ADinfo);
    pixVoucher.agreeTempPrintSize(&agreeWith,&agreeHigh);
    m_pix =new QPixmap(agreeWith,agreeHigh);
    pixVoucher.GetVoucherTemplate(m_pix);  // 获取打印信息

    if(flag == 1) //打印预览
    {
        printPreview();
    }else{ //直接打印
        createprinter();
    }
    delete[] m_pix;
}

int FontPrint::recvPrintInfo(const QByteArray &messagee)
{
    WebHeadInfo info;
    int ret = BaseHelper::getWebInfo(messagee,&info);
    if(ret < 0 ){
        return -1;
    }
    // 打印取药凭条
    if(1 == info.command_child)
    {
        PrintDocumentVoucher(messagee,0); // 直接打印凭条

    }else if(2 == info.command_child)
    {  // 打印凭条并且预览打印
        PrintDocumentVoucher(messagee,1);
    }else if(3 == info.command_child)
    {
        PrintDocumentDrug(messagee,0); //直接打印病例
    }else if(4 == info.command_child)
    {
        PrintDocumentDrug(messagee,1); //预览打印
    }
    return 0;
}

int FontPrint::StartPrint()
{
    return 0;
}

// 创建打印对象
int FontPrint::createprinter()
{
    QPrinter printer(QPrinter::HighResolution);

   // 获取默认打印机
   QPrinterInfo info;
   QString name = info.defaultPrinterName(); // 获取默认打印机名字
    printer.setPrinterName(name);
   // printer.setPaperSize(QSizeF(190,800), QPrinter::Point);

    printer.setPaperSize(QPrinter::A4);
    printDocument(&printer);
    return 0;
}

void FontPrint::drawPic(QPrinter *printerPixmap)
{
    //纵向：Portrait 横向：Landscape
    printerPixmap->setOrientation(QPrinter::Portrait);
    //获取界面的图片
    QPainter painterPixmap(this);
    painterPixmap.begin(printerPixmap);
    QRect rect = painterPixmap.viewport();
    int x = rect.width() / m_pix->width();
    int y = rect.height() / m_pix->height();
    //设置图像长宽是原图的多少倍
    painterPixmap.scale(x, y);
    painterPixmap.drawPixmap(0, 0, *m_pix);
    painterPixmap.end();
}

int FontPrint::printPreview()
{
    QPrinter printer(QPrinter::HighResolution);

   // 获取默认打印机
   QPrinterInfo info;
   QString name = info.defaultPrinterName(); // 获取默认打印机名字
    printer.setPrinterName(name);
    printer.setPageSize(QPrinter::Custom);
    printer.setPaperSize(QSizeF(190,800), QPrinter::Point);
    QPrintPreviewDialog preview(&printer, this);// 创建打印预览对话框
    // preview.setMinimumSize(1000,600);
     connect(&preview, SIGNAL(paintRequested(QPrinter*)), SLOT(drawPic(QPrinter*)));
     preview.exec();
    return 0;
}

void FontPrint::slotHandlePagePrinted(bool result)
{
    // 启动打印机进行打印
    qDebug() << "end";
}

void FontPrint::printDocumentA4(const QString &strHtml, int iFormat)
{

    m_currentPrinter = new QPrinter();
    m_currentPrinter->setPrinterName(m_currentPrinter->printerName());
    doc =new QWebEnginePage();
    connect(doc, SIGNAL(loadFinished(bool)), SLOT(printLocation(bool))); // 注册登录完成事件

    QFile loadFile("e:\\1.html");
    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "could't open projects json";
        return;
    }
    QByteArray allData = loadFile.readAll();
   loadFile.close();
  //  strHtml.prepend(allData);
    QString strHtml1 = allData;
    qDebug() << strHtml1;
    doc->setHtml(strHtml1);  // 获取网页内容
    return;
}

// 打印信息加载完成
void FontPrint::printLocation(bool flag)
{

    qDebug()<< "start print";
 //   qDebug()<< flag;
  //  QString info;
    doc->print(m_currentPrinter, invoke(this, &FontPrint::slotHandlePagePrinted));
    //   this->showMaximized();
 //   this->setZoomFactor(this->zoomFactor() + 0.5);
 //   this->show();
 //   m_start_Screen->close();
}


int FontPrint::printDocument(QPrinter *printer)
{   
        QPainter painter;
        painter.begin(printer);
        painter.drawPixmap(0, 0 ,*m_pix);
        painter.end();
        return 0;
}
#endif

// 打印门诊病历单
int FontPrint::PrintDocumentDrug(const QByteArray &message,bool flag)
{

    QByteArray allData = loadFile.readAll();
   loadFile.close();
    QString strHtml;
    strHtml.append(allData);
    printDocumentA4(strHtml, 1);
}

void FontPrint::drawPic(QPrinter *printerPixmap)
{
    //纵向：Portrait 横向：Landscape
    printerPixmap->setOrientation(QPrinter::Portrait);
    //获取界面的图片
    QPainter painterPixmap(this);
    painterPixmap.begin(printerPixmap);
    QRect rect = painterPixmap.viewport();
    int x = rect.width() / m_pix->width();
    int y = rect.height() / m_pix->height();
    //设置图像长宽是原图的多少倍
    painterPixmap.scale(x, y);
    painterPixmap.drawPixmap(0, 0, *m_pix);
    painterPixmap.end();
}




void FontPrint::printDocumentA4(const QString &strHtml, int iFormat)
{

    m_currentPrinter = new QPrinter();
    m_currentPrinter->setPrinterName(m_currentPrinter->printerName());
    doc =new QWebEnginePage();
    if(1 == iFormat){
        QPrintPreviewDialog preview(&printer, this);// 创建打印预览对话框
        connect(&preview, SIGNAL(paintRequested(QPrinter*)), SLOT(drawPic(QPrinter*)));
        preview.exec();
    }


    connect(doc, SIGNAL(loadFinished(bool)), SLOT(printLocation(bool))); // 注册登录完成事件

    QFile loadFile("e:\\1.html");
    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "could't open projects json";
        return;
    }
    QByteArray allData = loadFile.readAll();
   loadFile.close();
  //  strHtml.prepend(allData);
    QString strHtml1 = allData;
    qDebug() << strHtml1;
    doc->setHtml(strHtml1);  // 获取网页内容
    return;
}


int FontPrint::printPreview()
{
    QPrinter printer(QPrinter::HighResolution);

   // 获取默认打印机
   QPrinterInfo info;
   QString name = info.defaultPrinterName(); // 获取默认打印机名字
    printer.setPrinterName(name);
    printer.setPageSize(QPrinter::Custom);
    printer.setPaperSize(QSizeF(190,800), QPrinter::Point);
    QPrintPreviewDialog preview(&printer, this);// 创建打印预览对话框
     connect(&preview, SIGNAL(paintRequested(QPrinter*)), SLOT(drawPic(QPrinter*)));
     preview.exec();
    return 0;
}


// 打印信息加载完成
void FontPrint::printLocation(bool flag)
{

    qDebug()<< "start print";
    doc->print(m_currentPrinter, invoke(this, &FontPrint::slotHandlePagePrinted));
}
