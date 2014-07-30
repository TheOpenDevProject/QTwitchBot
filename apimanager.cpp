#include "apimanager.h"
#include <QDebug>

RiotAPI::RiotAPI(QObject *parent):
    QObject(parent)
{
    connect(qnam,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
}

void RiotAPI::replyFinished(QNetworkReply *reply){
    QByteArray byteReply = reply->readAll();
    emit requestComplete(byteReply);
}
void RiotAPI::requestBasicProfile(QString summoner_name){
    if(riotAPI_Key.isEmpty() || riotAPI_Key.size() < 36){
        qDebug() << "Riot API Key Is Not Valid";
    }else{
        qnam->get(QNetworkRequest(QUrl("https://oce.api.pvp.net/api/lol/oce/v1.4/summoner/by-name/"+ summoner_name +"?api_key=" + riotAPI_Key)));
    }

}

void RiotAPI::setAPIKey(QString riotAPIKey)
{
    riotAPI_Key = riotAPIKey;
}
void RiotAPI::ParseAndSet(){

}

/*
void RiotAPI::requestSummonerIcon(QString summoner_name){
    qnam->get(QNetworkRequest(QUrl("http://avatar.leagueoflegends.com/OC1/" + summoner_name + ".png")));
}
*/


void LeagueRankedInfo::requestBasicProfile(QString summoner_id)
{
    qnam->get(QNetworkRequest(QUrl("https://oce.api.pvp.net/api/lol/oce/v1.4/summoner/by-name/"+  summoner_id +"?api_key=" + riotAPI_Key)));
}
