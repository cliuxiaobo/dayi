#include"./cossupdate.h"
#include "aos_http_io.h"
#pragma comment(lib, "ws2_32.lib")

COSSUpdate* COSSUpdate::m_pThis = NULL;
COSSUpdate::COSSUpdate(QObject *parent) : QObject(parent)
{
    m_Pool = nullptr;
    m_bUseOSS = false;
    m_DebugStream = NULL;
    m_Proxcpp = new ProxyCPP();
    QString path = QCoreApplication::applicationDirPath();
    QDir dir(QCoreApplication::applicationDirPath() + "/log");
    if (!dir.exists())
    {
        dir.mkdir(dir.path());
    }
    //线程日志
    QDateTime time = QDateTime::currentDateTime();
    QString year = time.toString("yyyy");
    QString mm = time.toString("MM");
    QString dd = time.toString("dd");
    QString logstr = QString(year + "_" + mm + "_" + dd + "_chemi_OSS.log");
    m_DebugFile = new QFile(QCoreApplication::applicationDirPath() + "/log/" + logstr);
    if (m_DebugFile->open(QFile::WriteOnly | QFile::Append))
    {
        m_DebugStream = new QTextStream(m_DebugFile);
    }

    // 获取配置信息
    QSettings set(QCoreApplication::applicationDirPath() + "/config/config.config", QSettings::IniFormat);
    set.beginGroup("OSS");
    m_bUseOSS = set.value("UseOSS").toBool();
    if (false == m_bUseOSS)
    {
        return;
    }
    m_EndPoint = set.value("EndPoint").toByteArray();
    m_AccessKey = set.value("AccessKey").toByteArray();
    m_AccessSecret = set.value("AccessSecret").toByteArray();
    m_BucketName = set.value("BucketName").toByteArray();
    m_ImageEndPoint = set.value("ImageEndPoint").toByteArray();
    OSSInit();
    connect(this,SIGNAL(emit_OSSUpload(QString , QString,QString)),this,SLOT(slot_OSSUpload(QString, QString,QString)));
}

COSSUpdate::~COSSUpdate()
{
    if (m_bUseOSS)
    {
        if (m_Pool)
        {
            aos_pool_destroy(m_Pool);
        }
        aos_http_io_deinitialize();
    }
}

COSSUpdate*COSSUpdate::instance()
{
    if(m_pThis != NULL){
        return m_pThis;
    }
    else{
        m_pThis = new COSSUpdate();
    }
    return m_pThis;
}

bool COSSUpdate::OSSInit()
{
    if (false == m_bUseOSS)
    {
        return true;
    }
    if (AOSE_OK !=aos_http_io_initialize(NULL, 0))
    {
        return false;
    }
    aos_pool_create(&m_Pool, NULL);
    oss_client_options = oss_request_options_create(m_Pool);
    oss_client_options->config = oss_config_create(oss_client_options->pool);
    aos_str_set(&oss_client_options->config->endpoint, m_EndPoint.data());
    aos_str_set(&oss_client_options->config->access_key_id, m_AccessKey.data());
    aos_str_set(&oss_client_options->config->access_key_secret, m_AccessSecret.data());
    oss_client_options->config->is_cname = 0;
    oss_client_options->ctl = aos_http_controller_create(oss_client_options->pool, 0);
    qDebug() << "COSSUpdate init OSSInit end";

    return true;
}

void COSSUpdate::output(QString msg)
{
    if (m_DebugStream)
    {
        *m_DebugStream  << QDateTime::currentDateTime().toString("yy-MM-dd HH:mm:ss  ") << msg << "\r\n";
        m_DebugStream->flush();
    }
}

void COSSUpdate::slot_OSSUpload(QString fileFullUrl, QString name,QString order_id)
{
    QTime _t;
    qDebug() << "info status";
    qDebug() << order_id;
    _t.start();
    if (false == m_bUseOSS)
    {
        output(QString::fromLocal8Bit("OSSUpload: OSS 未使用") + name) ;
    }
    else
    {
        qDebug() << fileFullUrl;
        QFileInfo fileInfo(fileFullUrl);
        if(!fileInfo.isFile())
        {
             output(QString::fromLocal8Bit("OSSUpload: OSS 文件不存在") + fileFullUrl) ;
             return;
        }
        else
        {
            QFile loadFile(fileFullUrl);
            if(!loadFile.open(QIODevice::ReadOnly))
            {
                qDebug() << "could't open projects json";
                return;
            }
            QByteArray ba = loadFile.readAll();
            loadFile.close();
            void* data = ba.data();
            int size = ba.size();
            QByteArray arr = name.toLocal8Bit();
            char *urlName = arr.data();

            aos_string_t bucket;
            aos_string_t object;
            aos_list_t buffer;
            aos_buf_t *content = NULL;
            aos_table_t *headers = NULL;
            aos_table_t *resp_headers = NULL;
            aos_status_t *resp_status = NULL;
            aos_str_set(&bucket, m_BucketName.data());
            aos_str_set(&object, urlName);
            aos_list_init(&buffer);
            content = aos_buf_pack(oss_client_options->pool, data, size);
            aos_list_add_tail(&content->node, &buffer);
             qDebug() << "111111";
            resp_status = oss_put_object_from_buffer(oss_client_options, &bucket, &object, &buffer, headers, &resp_headers);
                  qDebug() << resp_status;
            if (aos_status_is_ok(resp_status))
            {
                output(QString::fromLocal8Bit("OSSUpload: 上传成功 耗时：") + _t.elapsed() + "ms " + name);
                // 将地址通知到php
                char buff[1024] = "";
                sprintf(buff,"https://%s.%s/%s",m_BucketName.data(),m_EndPoint.data()+ 7,name.toLocal8Bit().data());
                QString url = buff;
                m_Proxcpp->ProxyUpload(url,order_id);

            }
            else
            {
                output(QString::fromLocal8Bit("OSSUpload: 上传失败 耗时：") + _t.elapsed() + "ms " + name + " " + resp_status->error_code + " " + resp_status->error_msg);
            }
        }
    }
    output(QString::fromLocal8Bit("OSSUpload: 调用总耗时：") + _t.elapsed() + "ms " + name)  ;
}

