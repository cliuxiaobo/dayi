#include "orderpix.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QPrinterInfo>
#include <QPixmap>
#include <QProgressDialog>
#include <QPainter>
OrderPix::OrderPix()
{
    painter = new QPainter(this);
    m_scaleSize = 1;
    m_printWith = 0;
    m_printHigh = 0;

}

OrderPix::~OrderPix()
{
    delete painter;
}

int OrderPix::setTemplateSize(float scaleSize)
{
    m_scaleSize = scaleSize;
    return 0;
}

int OrderPix::setPixHeadInfo(OrderHeadInfo HeadInfo)
{
    m_headInfo = HeadInfo;
    return 0;
}

// 设置广告部分内容
int OrderPix::setPixInfo(WebPrintADInfo Info)
{
    m_ADInfo = Info;
    return 0;
}

// 设置药品部分内容
int OrderPix::setPixDrugInfo(WebPrintDrugInfo *info,int num)
{
    m_drugNum = num;
    int i = 0;
    for(i = 0;i<m_drugNum;i++){
        m_DrugInfo[i] = info[i];
    }
    return 0;
}


// 设置body 部分内容
int OrderPix::setPixInfo(WebPrintBodyInfo Info)
{
    m_bodyInfo = Info;
    return 0;
}

// 传入基础尺寸，返回实际尺寸
int OrderPix::agreeTempPrintSize(int *w,int *h)
{
    m_printWith = *w;
    m_printHigh = *h;
    return 0;
}


/*
 *                 惠民诊所
 *          门诊收费单
 *          收费时间：2019-10-04 11:06:06
 *          姓名：刘浩     类别：自费
 *           -----------------------
 *           名称        数量     金额
 *           xxxx         1      15
 *           xxxx         2      30
 *           -----------------------
 *           实收金额：
 *           支付方式：
 *           医生：
 *           诊所电话:
 *           ________________________
 *           广告位：          二维码区
 *           广告位：          二维码区
 *           打印时间：2019-10-04 12:00:00
*/
int OrderPix::GetDrugTemplate(QPixmap *pix)
{
    painter->begin(pix);
    painter->setRenderHint(QPainter::Antialiasing, true);
    // 设置画笔颜色、宽度
    painter->setPen(QPen(QColor(255, 255, 255), 1));
    // 设置画刷颜色
    painter->setBrush(QColor(255, 255, 255));
    QRect rect(0,0,m_printWith,m_printHigh);
    //整张图设置画刷白底
    painter->fillRect(rect,QColor(255, 255, 255));
    painter->drawRect(rect);
    //画数据部分的线条
    painter->setPen(QPen(QColor(0, 0, 0), 2));
// 第一部分
    // 药店名
    QFont font;
    font.setPointSize(12);
    font.setFamily("微软雅黑");
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(1,1,190,30,Qt::AlignCenter,m_headInfo.hospitalNmane);
    //门诊费用清单
    font.setPointSize(10);
    font.setFamily("宋体");
    painter->setFont(font);
    QString titlinfo(QString::fromLocal8Bit("门诊费用清单"));
    painter->drawText(1,30,190,20,Qt::AlignVCenter,titlinfo);
   // 开单时间
    font.setPointSize(8);
    font.setFamily("宋体");
    painter->setFont(font);
    QString reatTime(QString::fromLocal8Bit("创建时间:"));
    painter->drawText(1,50,190,20,Qt::AlignVCenter,reatTime+m_bodyInfo.creat_Time.toLocal8Bit());
    painter->drawText(1,70,90,20,Qt::AlignVCenter,QString(QString::fromLocal8Bit("姓名:刘小波")));
    painter->drawText(100,70,95,20,Qt::AlignVCenter,QString(QString::fromLocal8Bit("类别:自费")));


    // 药品栏分割线
    QVector<QLine> lines;
    lines.append(QLine(QPoint(1,95),QPoint(190,95)));//上边
    painter->drawLines(lines);

    // 收费打印单
    font.setPointSize(7);
    font.setFamily("宋体");
    painter->setFont(font);

    // 设置药品标题
    int i = 0;
    int TextHigh = 15;
    int TextY = 100;
    int TextW = 80;
     int TextX = 1;
    char DrugInfo[4][1024] = {"药品","数量","单价","总价"};
    for(i = 0;i < 4; i++)
    {
        painter->drawText(TextX,TextY,TextW,TextHigh,Qt::AlignCenter,QString(QString::fromLocal8Bit(DrugInfo[i])));
       // TextW = TextW + 33;
        TextX = TextX + TextW;
        TextW =37;
    }
    TextW = 190;
    TextY = TextY + TextHigh;
    TextX = 1;
    for(i = 0;i<m_drugNum;i++)
    {
        // 打印药品名称
        painter->drawText(TextX,TextY,TextW,TextHigh,Qt::AlignVCenter,m_DrugInfo[i].drug_name);
        // 装载药品信息
        int b;
        for(b=0;b<4;b++){
            memset(DrugInfo[b],0,1024);
        }
        strncpy(DrugInfo[0],m_DrugInfo[i].drug_id.toLocal8Bit().data(),1024);
        strncpy(DrugInfo[1],m_DrugInfo[i].drug_num.toLocal8Bit().data(),1024);
        strncpy(DrugInfo[2],m_DrugInfo[i].drug_value.toLocal8Bit().data(),1024);
        strncpy(DrugInfo[3],m_DrugInfo[i].drug_total.toLocal8Bit().data(),1024);
        TextW = 90;
        TextY = TextY + TextHigh;
        TextX = 1;
        for(b = 0; b< 4; b++){
            painter->drawText(TextX,TextY,TextW,TextHigh,Qt::AlignCenter,QString(DrugInfo[b]));
            TextX = TextX + TextW;
            TextW = 33;
        }
        // 调整布局
        TextY = TextY + TextHigh;
        TextX = 1;
        TextW = 190;
    }

    // 药品结束栏分割线
    lines.append(QLine(QPoint(1,TextY+5),QPoint(190,TextY+5)));//上边
    painter->drawLines(lines);
// 开始绘画收银部分
    TextY = TextY+10;
    //收款对象
    TextW = 90;
    painter->drawText(TextX,TextY,TextW,TextHigh,Qt::AlignVCenter,QString(QString::fromLocal8Bit("收银员:刘小波")));
    TextX = TextW;
    painter->drawText(TextX+10,TextY,TextW,TextHigh,Qt::AlignVCenter,QString(QString::fromLocal8Bit("医生:昌有权")));
// 结算金额
    TextY = TextY + TextHigh;
    TextX = 1;
    TextW = 100;
    painter->drawText(TextX,TextY,TextW,TextHigh,Qt::AlignVCenter,QString(QString::fromLocal8Bit("实收金额:"))+ m_bodyInfo.pay_total);
    TextX = TextW;
    painter->drawText(TextX,TextY,TextW,TextHigh,Qt::AlignVCenter,QString(QString::fromLocal8Bit("优惠:"))+ m_bodyInfo.pay_Concessions);

    TextY = TextY + TextHigh;
    TextX = 1;
    TextW = 190;
    painter->drawText(TextX,TextY,TextW,TextHigh,Qt::AlignVCenter,QString(QString::fromLocal8Bit("付费方式:")) + m_bodyInfo.pay_method);
    if(m_bodyInfo.note_info != ""){  // 有备注信息打印备注
            TextY = TextY + TextHigh;
            painter->drawText(TextX,TextY,TextW,TextHigh,Qt::AlignVCenter,QString(QString::fromLocal8Bit("备注:")) + m_ADInfo.ADfistInfo);
    }
    TextY = TextY + TextHigh;
    //两行广告
    painter->drawText(TextX,TextY,TextW,TextHigh,Qt::AlignVCenter,m_ADInfo.ADfistInfo);
    TextY = TextY + TextHigh;
    painter->drawText(TextX,TextY,TextW,TextHigh,Qt::AlignVCenter,m_ADInfo.ADSecondInfo);
    // 打印时间
    TextY = TextY + TextHigh;
    painter->drawText(TextX,TextY,TextW,TextHigh,Qt::AlignVCenter,QString(QString::fromLocal8Bit("打印时间"))+BaseHelper::getStrTime());
    painter->end();
    return 0;
}

/*
 *           大医.惠民诊所
 *           前台取药单
 *           取药号：
 *
 *            1  2   3    4
 *           ___________________
 *           就诊医生：
 *           诊所电话:
             ________________________
 *           广告位：          二维码区
 *           广告位：          二维码区
 *           打印时间：2019-10-04 12:00:00
*/
int OrderPix::GetVoucherTemplate(QPixmap *pix)
{
    painter->begin(pix);
    painter->setRenderHint(QPainter::Antialiasing, true);
    // 设置画笔颜色、宽度
    painter->setPen(QPen(QColor(255, 255, 255), 2));
    // 设置画刷颜色
    painter->setBrush(QColor(255, 255, 255));
    QRect rect(0,0,m_printWith,m_printHigh);
    //整张图设置画刷白底
    painter->fillRect(rect,QColor(255, 255, 255));
    painter->drawRect(rect);
    //画数据部分的线条
    painter->setPen(QPen(QColor(0, 0, 0), 2));
// 第一部分
    // 标题
    QFont font;
    int TextY = 1;
    int TextX = 1;
    int TextW = 190;
    int TextH = 30;
    font.setPointSize(20);
    font.setFamily("宋体");
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(TextX,TextY,TextW,TextH,Qt::AlignCenter,m_headInfo.hospitalNmane);
    //前台取药单
    font.setPointSize(12);
    font.setFamily("宋体");
    painter->setFont(font);
    QString titlinfo(QString::fromLocal8Bit("前台取药凭证"));
    TextY = TextY + TextH;
    painter->drawText(TextX,TextY,TextW,TextH,Qt::AlignVCenter,titlinfo);

   // 编号
    font.setPointSize(12);
    font.setFamily("宋体");
    painter->setFont(font);
    TextY = TextY + TextH;
    painter->drawText(TextX,TextY,TextW,TextH,Qt::AlignVCenter,QString(QString::fromLocal8Bit("编号")));

   // 编号码
    font.setPointSize(40);
    font.setFamily("宋体");
    painter->setFont(font);
    TextY = TextY + TextH;
    TextH = 100;
    painter->drawText(TextX,TextY,TextW,TextH,Qt::AlignCenter,QString("1234"));

    TextY =TextY + TextH;
    // 分割线
    QVector<QLine> lines;
    lines.append(QLine(QPoint(1,TextY+5),QPoint(TextW,TextY+5)));//上边
    painter->drawLines(lines);

// 医生\电话
    font.setPointSize(12);
    font.setFamily("宋体");
    painter->setFont(font);
    TextY = TextY + 10;
    TextH = 30;
    painter->drawText(TextX,TextY,TextW,TextH,Qt::AlignVCenter,QString(QString::fromLocal8Bit("医生")) + m_headInfo.doctorName);
    TextY = TextY + TextH;
    painter->drawText(TextX,TextY,TextW,TextH,Qt::AlignVCenter,QString(QString::fromLocal8Bit("电话"))+ m_headInfo.hospitalTelephone);
// 广告
    font.setPointSize(8);
    font.setFamily("宋体");
    painter->setFont(font);
    TextY = TextY + TextH;
    TextH = 20;
    painter->drawText(TextX,TextY,TextW,TextH,Qt::AlignVCenter,m_ADInfo.ADfistInfo);
    TextY = TextY + TextH;
    painter->drawText(TextX,TextY,TextW,TextH,Qt::AlignVCenter,m_ADInfo.ADSecondInfo);
    //二维码暂无
    // 时间
    font.setPointSize(7);
    font.setFamily("宋体");
    painter->setFont(font);
    TextY = TextY + TextH;
    painter->drawText(TextX,TextY,TextW,TextH,Qt::AlignVCenter,QString(QString::fromLocal8Bit("打印时间"))+BaseHelper::getStrTime());
    painter->end();
    return 0;
}

