#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <QWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>

class QNetworkReply;
class QNetworkAccessManager;

class NetworkClient : public QWidget
{
    Q_OBJECT
public:
    explicit NetworkClient(QWidget *parent = 0);
    QNetworkAccessManager * m_manager;

signals:
    void responce(QJsonObject object);

public slots:
    void postRequest(QJsonObject json, QString url, QString token);
    void getRequest(QString url, QString token);
    void deleteRequest(QString url, QString token);
    void onResponse( QNetworkReply* reply );
};

#endif // NETWORKCLIENT_H
