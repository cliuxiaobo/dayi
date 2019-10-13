#ifndef COMMON_H
#define COMMON_H
#include <string>
#include <vector>
#include <map>
#include <list>
#include <memory>
#include <set>
#define VERSION "2.4.5"


typedef struct _WebAudioData{
    int code;     // 主命令
    int user_id;    // 子命令
    _WebAudioData(){
        code = 0;
        user_id = 0;
    }
}WebAudioData;


typedef struct _WebHeadInfo{
    int command_type;     // 主命令
    int command_child;    // 子命令
    int userID;           // 当前操作人ID
    QString userName;     // 当前操作者姓名
    QString hostName;     // 诊所名称
    QString serialNumber; // 序列ID; 做回馈认证用
    _WebHeadInfo(){
        command_type = 0;
        userID = 0;
        userName = "";
        hostName = "";
        serialNumber = "";
    }
}WebHeadInfo;

typedef struct _WebPrintBodyInfo{
    int DocumentNum;           //单据号码
    QString voice_content;     // 播报声音，(未开发)
    QString creat_Time;        // 开药时间
    QString pay_method;        // 支付方式
    QString pay_Concessions;   // 优惠金额
    QString note_info;         // 备注信息
    QString doctor_name;        // 主治医生
    QString patient_name;       // 病人名字
    QString Patient_age;        // 病人年龄
    QString Patient_sex;        // 病人性别
    QString pay_total;         // 总计
    _WebPrintBodyInfo(){
       DocumentNum = 0;
       voice_content = "";
       creat_Time = "";
       pay_method = "";
       pay_Concessions = "";
       note_info   = "";
       doctor_name = "";
       patient_name = "";
       Patient_age = "";
       Patient_sex = "";
       pay_total   = "";
    }
}WebPrintBodyInfo;

typedef struct _WebPrintADInfo{
    QString ADQRcode;          // 广告二维码
    QString ADfistInfo;        // 第一行显示文字
    QString ADSecondInfo;      // 第二行显示文字
    QString ADvoice_content;   // 广告声音
    _WebPrintADInfo(){
       ADQRcode = "";
       ADfistInfo = "";
       ADSecondInfo = "";
       ADvoice_content = "";
    }
}WebPrintADInfo;

typedef struct _WebPrintDrugInfo{
    QString drug_name; // 药品名称
    QString drug_spec; // 药品规格
    QString drug_value; // 药品单价
    QString drug_num;   // 药品数量
    QString drug_total; // 药品总计金额
    QString drug_id;    //药品条形码
    _WebPrintDrugInfo(){
       drug_name = "";
       drug_spec = "";
       drug_value = "";
       drug_num = "";
    }
}WebPrintDrugInfo;

typedef struct _WebTitleData{
  int id;
  QString name;
  int status;
    _WebTitleData(){
       id = 0;
       name = "";
       status = 0;
    }
}WebTitleData;



//@brief:服务器工作模式
enum class WorkMode
{
    ONLY_LOCAL,
    ONLY_CLOUD,
    LOCAL_CLOUD
};

//@brief:网络状态
enum class NetStatus
{
    OFFLINE_STATUS,
    ONLINE_STATUS
};
#endif // COMMON_H
