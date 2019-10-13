#ifndef FONTPRINT_H
#define FONTPRINT_H

#include <QWebEngineView>
#include<QMutex.h>
#include <Qqueue>
#include <QThread>
#include <QQueue>
#include "../ui_mainwindow.h"
#include "../common.h"
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#include <QPrinterInfo>
#include <QPixmap>
#if QT_CONFIG(printpreviewdialog)
#include <QPrintPreviewDialog>
#endif
#endif
#endif
#include <qmainwindow.h>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#endif
QT_BEGIN_NAMESPACE
class QPrinter;
class QTextEdit;
class QTreeWidget;
class QTreeWidgetItem;
QT_END_NAMESPACE

#if 0
struct _PrintType{
    QString printName;
    int     printPageWigth;
    int     printPageHeight;
    _PrintType(){
        printName = "";
        printPageWigth = 0;
        printPageHeight = 0;
    }
}PrintType;
#endif
class FontPrint : public QWidget// public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT
public:
    FontPrint();
    ~FontPrint();
    int StartPrint();
    int createprinter();
    int recvPrintInfo(const QByteArray &message);

    int printPreview();
    int GetVoucherTemplate(QPixmap *pix);
    int getPrintDeviceList();
    void printDocumentA4(const QString &strHtml, int iFormat = 1);
public slots:
    void drawPic(QPrinter *printerPixmap);
    int printDocument(QPrinter *printer);
    void slotHandlePagePrinted(bool result);
    void printLocation(bool flag);
private:
    // 取药号打印
    int PrintDocumentVoucher(const QByteArray &message,bool flag);
    // 病例单打印
    int PrintDocumentDrug(const QByteArray &message,bool flag);


    QPixmap *m_pix;
    int agreeWith;    // 57mm 纸
    int agreeHigh;

    QPrinter *m_currentPrinter;
    QWebEnginePage    *doc;
};

#endif
