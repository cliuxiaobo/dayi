#include "basehelper.h"
#include <QDateTime>

static QString hospital_name;
static int hospital_id;

namespace BaseHelper
{

     int SetHospitalInfo(QString name,int id)
     {
        hospital_name = name;
        hospital_id = id;
        return 0;

     }
     int GetHospitalId()
     {
        return hospital_id;
     }

    // 获取commd
    int getWebCommandType(const QByteArray &message)
    {
        QJsonParseError json_error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(message,&json_error);
        if(json_error.error != QJsonParseError::NoError)
        {
            qDebug() << " 1 json error!";
            // 回复Web端
            return -1;
        }
        QJsonObject rootObj = jsonDoc.object();
        QStringList keys = rootObj.keys();
        for(int i = 0; i < keys.size(); i++)
        {
            qDebug() << "key" << i << " is:" << keys.at(i);
        }
        //因为是预先定义好的JSON数据格式，所以这里可以这样读取
        if(rootObj.contains("code"))
        {
           int command = rootObj["code"].toInt();
           return command;
        }
        return 0 ;
    }


    // 获取fast head 指定信息
    int getWebInfo(const QByteArray &message,WebHeadInfo *info)
    {
        QJsonParseError json_error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(message,&json_error);
        if(json_error.error != QJsonParseError::NoError)
        {
            qDebug() << "json error!";
            // 回复Web端
            return -1;
        }
        QJsonObject rootObj = jsonDoc.object();
        QStringList keys = rootObj.keys();
        //因为是预先定义好的JSON数据格式，所以这里可以这样读取
        if(rootObj.contains("first head"))
        {
           QJsonObject subObj = rootObj.value("first head").toObject();
           info->command_type = subObj["command_type"].toInt();
           info-> userID = subObj["userID"].toInt();
           info-> userName = subObj["userName"].toString();
           info->hostName = subObj["hospitalNmane"].toString();
           info->serialNumber = subObj["serialNumber"].toString();
           info->command_child = subObj["command_child"].toInt();
            return 1;
        }
        return 0 ;
    }

    // 获取 打印的body 指定信息
    int getWebInfo(const QByteArray &message,WebPrintBodyInfo *info)
    {
        QJsonParseError json_error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(message,&json_error);
        if(json_error.error != QJsonParseError::NoError)
        {
            qDebug() << "json error!";
            // 回复Web端
            return -1;
        }
        QJsonObject rootObj = jsonDoc.object();
        //因为是预先定义好的JSON数据格式，所以这里可以这样读取
        if(rootObj.contains("body"))
        {
           QJsonObject subObj = rootObj.value("body").toObject();
           info->voice_content = subObj["voice_content"].toString();
           info->DocumentNum = subObj["DocumentNum"].toInt();

           info->creat_Time = subObj["creat_Time"].toString();
           info->pay_method = subObj["pay_method"].toString();
           info->pay_Concessions = subObj["pay_Concessions"].toString();
           info->note_info = subObj["note_info"].toString();
           info->pay_total = subObj["pay_total"].toString();
           return 1;
        }
        return 0 ;
    }

    QString creat_Time; // 开药时间
    QString pay_method; // 支付方式
    QString pay_Concessions; // 优惠金额
    QString concessions_info; //优惠金额附加信息
    QString pay_total;    // 总计


    int getWebInfo(const QByteArray &message,WebPrintADInfo *info)
    {
        QJsonParseError json_error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(message,&json_error);
        if(json_error.error != QJsonParseError::NoError)
        {
            qDebug() << "json error!";
            // 回复Web端
            return -1;
        }
        QJsonObject rootObj = jsonDoc.object();
        //因为是预先定义好的JSON数据格式，所以这里可以这样读取
        if(rootObj.contains("adInfo"))
        {
           QJsonObject subObj = rootObj.value("adInfo").toObject();
           info->ADQRcode = subObj["ADQRcode"].toString();
           info->ADfistInfo = subObj["ADfistInfo"].toString();
           info->ADSecondInfo = subObj["ADSecondInfo"].toString();
           info->ADvoice_content = subObj["ADvoice_content"].toString();
            return 1;
        }
        return 0 ;
    }

    int getWebInfo(const QByteArray &message,WebPrintDrugInfo *info)
    {
        QJsonParseError json_error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(message,&json_error);
        if(json_error.error != QJsonParseError::NoError)
        {
            qDebug() << "json error!";
            // 回复Web端
            return -1;
        }
        QJsonObject rootObj = jsonDoc.object();
        //因为是预先定义好的JSON数据格式，所以这里可以这样读取
        if(rootObj.contains("drug list"))
        {
           QJsonArray subArray = rootObj.value("drug list").toArray();
           int i = 0;
           for(i = 0;i < subArray.size();i++){
                QJsonObject subObj = subArray.at(i).toObject();
                info[i].drug_name =subObj["drug_name"].toString();
                info[i].drug_num = subObj["drug_num"].toString();
                info[i].drug_spec = subObj["drug_spec"].toString();
                info[i].drug_value = subObj["drug_value"].toString();
                info[i].drug_id = subObj["drug_id"].toString();
                info[i].drug_total = subObj["drug_total"].toString();
           }
            return i;
        }
        return 0 ;
    }

    int getWebInfo(const QByteArray &message,WebTitleData *info)
    {
        QJsonParseError json_error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(message,&json_error);
        if(json_error.error != QJsonParseError::NoError)
        {
            qDebug() << "json error!";
            // 回复Web端
            return -1;
        }
        QJsonObject rootObj = jsonDoc.object();
        //因为是预先定义好的JSON数据格式，所以这里可以这样读取
        if(rootObj.contains("data"))
        {
           QJsonObject subObj = rootObj.value("data").toObject();
           info->id = subObj["hospital_id"].toInt();
           info->name = subObj["hospital_name"].toString();
            return 1;
        }
        return 0 ;
    }
    int getWebInfo(const QByteArray &message,WebAudioData *info)
    {
        QJsonParseError json_error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(message,&json_error);
        if(json_error.error != QJsonParseError::NoError)
        {
            qDebug() << "json error!";
            // 回复Web端
            return -1;
        }
        QJsonObject rootObj = jsonDoc.object();
        //因为是预先定义好的JSON数据格式，所以这里可以这样读取
        if(rootObj.contains("data"))
        {
           QJsonObject subObj = rootObj.value("data").toObject();
           info->order_id = subObj["order_id"].toString();
           info->user_id = subObj["user_id"].toInt();
           info->user_name = subObj["user_name"].toInt();
            return 1;
        }
        return 0 ;
    }

    //获取data数据
    int getWebData(const QByteArray &message,QString &info)
    {
        QJsonParseError json_error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(message,&json_error);
        if(json_error.error != QJsonParseError::NoError)
        {
            qDebug() << "json error!";
            // 回复Web端
            return -1;
        }
        QJsonObject rootObj = jsonDoc.object();
        //因为是预先定义好的JSON数据格式，所以这里可以这样读取
        if(rootObj.contains("data"))
        {
           QJsonObject subObj = rootObj.value("data").toObject();
           info= subObj["content"].toString();
            return 1;
        }
        return 0 ;
    }


    //获取时间戳
    long getTimeStamp()
    {
        long nStamp = 0;
        time_t result = time(nullptr);
        nStamp = result;
        return nStamp;
    }

    QString getStrTime()
    {
         QDateTime current_time = QDateTime::currentDateTime();
       return current_time.toString("yyyy-MM-dd hh-mm-ss");
    }
}
