#include "apimanager.h"
#include <QDebug>
//The-Sprinter Branch Maker
RiotAPI::RiotAPI(QObject *parent):
    QObject(parent)
{
    connect(qnam,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
}

void RiotAPI::replyFinished(QNetworkReply *reply){
    QByteArray byteReply = reply->readAll();
    rawapidata = byteReply;
    ParseAndSet();
    emit requestComplete(byteReply);
}
void RiotAPI::requestBasicProfile(QString summoner_name){
    if(riotAPI_Key.isEmpty() || riotAPI_Key.size() < 36){
        qDebug() << "Riot API Key Is Not Valid";
    }else{
        summonerName = summoner_name.toLower();
        qnam->get(QNetworkRequest(QUrl("https://oce.api.pvp.net/api/lol/oce/v1.4/summoner/by-name/"+ summoner_name +"?api_key=" + riotAPI_Key)));
    }

}

void RiotAPI::setAPIKey(QString riotAPIKey)
{
    riotAPI_Key = riotAPIKey;
}

void RiotAPI::ParseAndSet(){

    //Each state considered critical to valid data can cause a break in the function because, proceeding with an error would be useless.
    if(rawapidata.isEmpty()){
        qDebug() << "Basic profile no json data found";
   return;
    }

    //We have data, Proceed with JSON specific validation + loading document
        QJsonParseError jerror;
        QJsonDocument jdoc  = QJsonDocument::fromJson(rawapidata,&jerror);

       //Get the root element of the basic summoner profile, Currently we can expect this to be the summoners name.
    const QJsonObject jObject = jdoc.object();
    QJsonValue jVal = jObject.value(summonerName);
//qDebug() << jVal;
    QJsonObject playerDetails = jVal.toObject();
    //Basic Summoner Profile values
    QJsonValue playerID = playerDetails["id"];
    QJsonValue playerServerName = playerDetails["name"];
    QJsonValue playerProfileIconId = playerDetails["profileIconId"];
    QJsonValue playerLevel = playerDetails["summonerLevel"];
    //Now we just store these as members
        summonerID = playerID.toVariant().toString();
        summonerLevel = playerLevel.toVariant().toString();
}
