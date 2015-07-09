#include "networkmanager.h"
#include <QDebug>
#include <QNetworkCookieJar>
#include <QNetworkReply>
NetworkManager * NetworkManager::mInstance = NULL;

NetworkManager::NetworkManager(QObject * parent )
    :QNetworkAccessManager(parent)
{


//    QByteArray data="username=ionuser&password=ionuser&remember_me=on";


//    QNetworkReply * reply = post(QNetworkRequest(QUrl("http://10.67.70.16/login/ajax/")),data);


//    connect(reply,SIGNAL(finished()),this,SLOT(logged()));





}

void NetworkManager::authRequired()
{
    qDebug()<<"auth required";
}

void NetworkManager::logged()
{
//    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());
//    qDebug()<<"logged";

//    qDebug()<<reply->errorString();


//    foreach ( QByteArray key, reply->rawHeaderList())
//    {
//        qDebug()<<key<<" "<< reply->rawHeader(key);
//    }


}

