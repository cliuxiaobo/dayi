#include "dyconfig.h"
DyConfig::DyConfig()
{

}
//写入配置信息
void DyConfig::writeIni(QString videoDevice)
{
    QSettings settings(QCoreApplication::applicationDirPath() + "/config/config.config", QSettings::IniFormat);
    settings.beginGroup("device");
    settings.setValue("video", videoDevice.toLocal8Bit().data());
    settings.endGroup();
}
