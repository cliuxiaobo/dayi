#ifndef PROXYCPP_H
#define PROXYCPP_H
#include <string>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
class ProxyCPP : public QObject
{
public:
    ProxyCPP();
    ~ProxyCPP();
    void ProxyUpload(QString url,QString order_id);
public slots:
   void slot_requestFinished(QNetworkReply* reply);

private:
   QNetworkAccessManager* naManager;
};

#endif // PROXYCPP_H
