#ifndef DYCONFIG_H
#define DYCONFIG_H
#include <QObject>
#include <QtCore>
#include <QImage>
#include "oss_api.h"
#include <QMutex>

class DyConfig
{
public:
    DyConfig();
    void writeIni(QString videoDevice);
};

#endif // DYCONFIG_H
