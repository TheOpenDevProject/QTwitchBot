#include "apimanager.h"
#include <QDebug>

RiotAPI::RiotAPI(QObject *parent):
    QObject(parent)
{
    connect(qnam,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
}

QByteArray RiotAPI::getDataAndFlushBuffer()
{

}

void RiotAPI::replyFinished(QNetworkReply *reply){
    QByteArray byteReply = reply->readAll();
    emit requestComplete(byteReply);
}
void RiotAPI::requestBasicProfile(QString summoner_name){
    qnam->get(QNetworkRequest(QUrl("https://oce.api.pvp.net/api/lol/oce/v1.4/summoner/by-name/"+ summoner_name +"?api_key=" + riotAPI_Key)));
}
