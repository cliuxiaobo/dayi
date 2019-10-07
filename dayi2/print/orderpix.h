#ifndef CREATPIX_H
#define CREATPIX_H
#include<QMutex.h>
#include <Qqueue>
#include <QThread>
#include <QQueue>
#include "../ui_mainwindow.h"
#include "../basehelper.h"
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

typedef struct _OrderHeadInfo{
     QString hospitalNmane; // 诊所名称
     QString hospitalTelephone;
     QString doctorName;
}OrderHeadInfo;

struct OrderDrugInfo{

};


class OrderPix : public QWidget
{
public:
    OrderPix();
    ~OrderPix();
    int setTemplateSize(float scaleSize);
    int setPixHeadInfo(OrderHeadInfo HeadInfo); // 设置抬头打印信息
//    int setPixBodyInfo();
    int agreeTempPrintSize(int *w,int *h);

    int setPixInfo(WebPrintADInfo Info);
    int setPixDrugInfo(WebPrintDrugInfo *Info,int num);
    int setPixInfo(WebPrintBodyInfo Info);
    int GetVoucherTemplate(QPixmap *pix);
    int GetDrugTemplate(QPixmap *pix);
private:
    int m_printWith;
    int m_printHigh;
    float m_scaleSize;
    QPainter *painter;
    OrderHeadInfo m_headInfo;
    WebPrintADInfo m_ADInfo;
    WebPrintBodyInfo m_bodyInfo;
    WebPrintDrugInfo m_DrugInfo[100];
    int m_drugNum ;
};

#endif // CREATPIX_H
