#include "twitchjsonapiamanger.h"

TwitchJSONAPIAManger::TwitchJSONAPIAManger()
{
    connect(qnam,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)),Qt::AutoConnection);
}

QStringList TwitchJSONAPIAManger::getModerators()
{
    return modList;
}

QStringList TwitchJSONAPIAManger::getUsers()
{
return userList;
}



void TwitchJSONAPIAManger::makeRequest(QString ChannelName)
{
    qDebug() << "Requesting User List From tmi.twitch.tv";
    qnam->get(QNetworkRequest(QUrl("https://tmi.twitch.tv/group/user/" + ChannelName + "/chatters")));
    emit(dataRequestable());
}

void TwitchJSONAPIAManger::parseJSON()
{
    if(rawRequest.isEmpty()){
        qDebug() << "There is no data to parse - Error #16";
       return;
    }

                QJsonParseError jerror;
                    QJsonDocument jdoc = QJsonDocument::fromJson(rawRequest,&jerror);
            const QJsonObject rootObject = jdoc.object();

                QJsonArray moderatorList = rootObject["chatters"].toObject()["moderators"].toArray();
                QJsonArray userList_local = rootObject["chatters"].toObject()["viewers"].toArray();
            //Finished Parse for Mods and Users
            //Convert to QStringLists from the QVariant Method
               for(int i = 0;i < moderatorList.size(); i++){
                   modList << moderatorList.at(i).toVariant().toString();
               }
               qDebug() << modList;

               for(int i = 0;i < userList_local.size(); i++){
                   userList << userList_local.at(i).toVariant().toString();
               }
               qDebug() << userList;
}

void TwitchJSONAPIAManger::replyFinished(QNetworkReply *reply){

        rawRequest = reply->readAll();
        parseJSON();
}
