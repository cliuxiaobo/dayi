#ifndef COSSUPDATE_H
#define COSSUPDATE_H

#include <QObject>
#include <QtCore>
#include <QImage>
#include "oss_api.h"
#include "../../proxycpp.h"
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

public slots:
    void slot_OSSUpload(QString fileFullUrl,QString name,QString order_id);
signals:
    void emit_OSSUpload(QString fileFullUrl,QString name,QString order_id);

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

    ProxyCPP *m_Proxcpp;
};

#endif // COSSUPDATE_H
