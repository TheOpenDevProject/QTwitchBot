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
    //This is probably our Summoner profile icon, Either way its a PNG.
    if(byteReply.startsWith("137 80 78 71 13 10 26 10")){
        summonerProfilePixmap.loadFromData(byteReply);
        //Emmit the signal that the data has finished
        emit requestComplete();
        return;
    }
    //Otherwise treat the data as JSON
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

void RiotAPI::requestSummonerIcon(QString summoner_name)
{
    if(summoner_name.isEmpty()){
        qDebug() << "Summoner name must be provided";
    }else {
       qnam->get(QNetworkRequest(QUrl("http://avatar.leagueoflegends.com/oce/" + summoner_name + ".png")));
    }
}

void RiotAPI::setAPIKey(QString riotAPIKey)
{
    riotAPI_Key = riotAPIKey;
}

void RiotAPI::ParseAndSet(){
    //First 8 bytes of a png image are 137 80 78 71 13 10 26 10 (ref:libpng.org)
        if(rawapidata.startsWith("137 80 78 71 13 10 26 10")){
            qDebug() << "Data is a PNG file (Parse not available)";
            return;
        }
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
        summonerProfileIcon = playerProfileIconId.toVariant().toString();
}


RiotAPI_RankedStats::RiotAPI_RankedStats(QObject *parent)
{
    connect(qnam,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
}

void RiotAPI_RankedStats::getRankedStats()
{
    if(riotAPI_Key.isEmpty() || riotAPI_Key.size() < 36){
        qDebug() << "Riot API Key Is Not Valid";
    }else{

        qnam->get(QNetworkRequest(QUrl("https://oce.api.pvp.net/api/lol/oce/v2.4/league/by-summoner/"+ summonerID +"/entry?api_key=" + riotAPI_Key)));
    }
}

void RiotAPI_RankedStats::setSummonerID(QString s_id)
{
    summonerID = s_id;
}

void RiotAPI_RankedStats::ParseAndSet()
{

    QJsonParseError jerror;
    QJsonDocument jdoc = QJsonDocument::fromJson(rawapidata,&jerror);
    const QJsonObject jObject = jdoc.object();
     QJsonArray playerArray = jdoc.object()[summonerID].toArray()[0].toObject()["entries"].toArray();
     QJsonArray playerDataArray = playerArray[0].toArray();
     QJsonValue playerLP = playerDataArray[0];
     qDebug() << playerLP;


    //Access by key

}

void RiotAPI_RankedStats::replyFinished(QNetworkReply *reply){
    QByteArray byteReply = reply->readAll();
    rawapidata = byteReply;

    ParseAndSet();
    emit requestComplete(byteReply);
}
