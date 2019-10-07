#ifndef OSSCHANNEL_H
#define OSSCHANNEL_H
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include "oss_api.h"
#include "aos_http_io.h"
class OssChannel
{
public:
    static OssChannel &getInstance(void)
    {
        static OssChannel *instance;
        if(!instance){
                instance = new OssChannel();
            }
        return *instance;
   }
   int PushFile(QString file);
private:
   explicit OssChannel();
    ~OssChannel();
   aos_pool_t *pool;
   oss_request_options_t *oss_client_options;
};


#endif
