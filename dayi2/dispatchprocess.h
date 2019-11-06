//所有控件可它打交道，负责调度任务
#ifndef DISPATCHPROCESS_H
#define DISPATCHPROCESS_H
#include <QMainWindow>
#include <QWebEngineView>
#include <QDialog>
#include <QVariantMap>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMutex.h>
#include <Qqueue>
#include <QThread>
#include <QQueue>
#include "audioctl/audiorecorder.h"
#include "print/fontPrint.h"
#include "./webchannel/channeldialog.h"
using namespace std;
struct eventInfo{
    int srcID;
    int dstID;
    QString msg;
    eventInfo(){
        srcID = 0;
        dstID = 0;
        msg = "";
    }
};
enum WebCommdType{
    START_RECORD = 1,    // 开始录音
    STOP_RECORD = 2,     // 结束录音
    PRINT_REPERTORY = 3, // 打印库存信息
    PRINT_MEDICINE_INFO = 4, // 打印买药信息
    PRINT_ACCEPTS_INFO = 5, // 打印接诊、卖药，化疗 信息
    PRINT_VOUCHER = 6,      //打印取药凭证
    QUERY_AUDIO_DEVICE = 101, // 查询音频输入设备
    SET_AUDIO_DEVICE = 102,   // 查询录音设备
    QUERY_PRINT_DEVICE = 103, // 获取打印设备信息
    ADD_PRINT_DEVICE = 104,   // 添加打印设备
    SET_PRINT_DEVICE = 105    // 设置打印设备
};

class DispatchProcess : QThread
{
    Q_OBJECT
public:
    static DispatchProcess &getInstance(void)
    {
        static DispatchProcess *instance;
        if(!instance){
                instance = new DispatchProcess();
            }
        return *instance;
   }


    void run();
    int Webview();
public slots:
   // void adjustLocation();
    void slot_ProcessMsg(const QByteArray &message);

signals:
    void emit_ProcessMsg(const QByteArray &message);

   // void adjustLocation();

private:
   explicit DispatchProcess();
    ~DispatchProcess();

    // 设置标题
  //  int SetWebTitle(const QByteArray &message );
    //回复信息函数
    int DispatchRspWeb(int ErrorType, QString ErrorInfo);
    QQueue<eventInfo> QProcess;
    bool m_running;
    AudioRecorder *m_audioRecord;
    FontPrint *m_Print;
//    QWebEngineView *m_view;
//    QWidget *m_start_Screen;
    MainWindow  *m_windos;
};

#endif // DISPATCHPROCESS_H
