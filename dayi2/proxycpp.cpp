#include "proxycpp.h"
#include "common.h"
ProxyCPP::ProxyCPP()
{
    naManager = new QNetworkAccessManager(this);
    QMetaObject::Connection connRet = QObject::connect(naManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_requestFinished(QNetworkReply*)));
    Q_ASSERT(connRet);

}

ProxyCPP::~ProxyCPP()
{
    delete naManager;
}


// 上传PHP服务端
void ProxyCPP::ProxyUpload(QString AliUrl,QString order_id)
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://192.168.1.9:83/serverclinic/notifyVoice"));
    QString postData = "order_id=" + order_id + "&" + "url=" + AliUrl;
    qDebug() << postData;
    QByteArray append(postData.toLocal8Bit().data());
    QNetworkReply* reply = naManager->post(request, append);
}

void ProxyCPP::slot_requestFinished(QNetworkReply* reply)
{
    // 获取http状态码
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid())
        qDebug() << "status code=" << statusCode.toInt();

    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    if(reason.isValid())
        qDebug() << "reason=" << reason.toString();

    QNetworkReply::NetworkError err = reply->error();
    if(err != QNetworkReply::NoError) {
        qDebug() << "Failed: " << reply->errorString();
    }
    else {
        // 获取返回内容
        qDebug() << reply->readAll();
    }
}
