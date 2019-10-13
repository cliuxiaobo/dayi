#ifndef BASEHELPER_H
#define BASEHELPER_H
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include <time.h>
#include "./Common.h"
namespace BaseHelper
{
    // 获取web端发出命令类型
    int getWebCommandType(const QByteArray &message);

    // 获取web端头部信息
    int getWebInfo(const QByteArray &message,WebHeadInfo *info );

    // 获取web端body信息
    int getWebInfo(const QByteArray &message,WebPrintBodyInfo *info);

    // 获取广告部分信息
    int getWebInfo(const QByteArray &message, WebPrintADInfo *info);

    // 获取药品清单
    int getWebInfo(const QByteArray &message,WebPrintDrugInfo *info);

    // 获取头信息
    int getWebInfo(const QByteArray &message,WebTitleData *info);

    // 获取音频设备的DATA
    int getWebInfo(const QByteArray &message,WebAudioData *info);

    // 获取时间戳
    long getTimeStamp();
    // 获取时间格式
    QString getStrTime();
}
#endif // BASEHELPER_H
