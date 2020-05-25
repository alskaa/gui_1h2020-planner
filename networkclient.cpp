#include "networkclient.h"

NetworkClient::NetworkClient(QWidget *parent) : QWidget(parent){
  m_manager = new QNetworkAccessManager();
  connect( m_manager, SIGNAL( finished( QNetworkReply* ) ), SLOT( onResponse( QNetworkReply* ) ) );
}

void NetworkClient::postRequest(QJsonObject json, QString url, QString token){
    QUrl qUrl(url);
    QNetworkRequest request( qUrl );
    request.setUrl(qUrl);
    request.setRawHeader("Content-Type","application/json");
    if(token != "") {
            request.setRawHeader("Authorization",token.toUtf8());
    }
    m_manager->post(request, QJsonDocument(json).toJson());
}

void NetworkClient::getRequest(QString url, QString token){
    QUrl qUrl(url);
    QNetworkRequest request( qUrl );
    request.setUrl(qUrl);
    if(token != "") {
            request.setRawHeader("Authorization",token.toUtf8());
    }
    m_manager->get(request);
}

void NetworkClient::deleteRequest(QString url, QString token){
    QUrl qUrl(url);
    QNetworkRequest request( qUrl );
    request.setUrl(qUrl);
    if(token != "") {
            request.setRawHeader("Authorization",token.toUtf8());
    }
    m_manager->deleteResource(request);
}

void NetworkClient::onResponse(QNetworkReply *reply) {
    QJsonObject json = QJsonDocument::fromJson(reply->readAll()).object();
    emit(responce(json));
}
