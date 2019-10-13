#ifndef COSSUPDATE_H
#define COSSUPDATE_H

#include <QObject>
#include <QtCore>
#include <QImage>
#include "oss_api.h"
#include <QMutex>

class COSSUpdate : public QObject
{
    Q_OBJECT
public:
    explicit COSSUpdate(QObject *parent = nullptr);
    virtual ~COSSUpdate();
    static COSSUpdate* instance();
    QString ImageEndPoint();
    bool m_bUseOSS;



private:
    QByteArray m_EndPoint;
    QByteArray m_AccessKey;
    QByteArray m_AccessSecret;
    QByteArray m_BucketName;
    QString m_ImageEndPoint;

    aos_pool_t* m_Pool;
    oss_request_options_t *oss_client_options;

    static COSSUpdate* m_pThis;
    bool OSSInit();
    void output(QString msg);

    QTextStream* m_DebugStream;
    QFile* m_DebugFile;
    QMutex m_DataMutex;

public slots:
    void slot_OSSUpload(QString imgUrl, QImage img);
signals:
    void emit_OSSUpload(QString imgUrl, QImage img);

};

#endif // COSSUPDATE_H



#if 0
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
#endif
