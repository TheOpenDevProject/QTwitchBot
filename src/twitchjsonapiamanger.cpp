#include "twitchjsonapiamanger.h"

TwitchJSONAPIAManger::TwitchJSONAPIAManger()
{
    connect(qnam,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)),Qt::AutoConnection);
}

TwitchJSONAPIAManger::~TwitchJSONAPIAManger()
{
    //Free up the memory from the allocated users (This could be a massive memory leak if not done
    for(int i = 0;i < userList.size(); i++){
        delete userList.at(i);
    }
    //Let Qt's event loop manage the lifetime of our object. (When it returns to the main event loop we dont need it).
    qnam->deleteLater();
}

std::vector<TwitchUser *> TwitchJSONAPIAManger::getUserList()
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
    //Call clear method
    userList.clear();
    for(int i = 0;i < moderatorList.size(); i++){
        TwitchUser *tUser = new TwitchUser();
        tUser->setUsername(moderatorList.at(i).toVariant().toString());
        tUser->setAccessLevel(1);
        userList.push_back(tUser);
        qDebug() << "Moderator Added";
    }


    for(int i = 0;i < userList_local.size(); i++){
        TwitchUser *tUser = new TwitchUser();
        tUser->setUsername(userList_local.at(i).toVariant().toString());
        tUser->setAccessLevel(0);
        userList.push_back(tUser);
    }

    qDebug() << "SizeOf user list" << userList.size();
}

void TwitchJSONAPIAManger::replyFinished(QNetworkReply *reply){

    rawRequest = reply->readAll();
    parseJSON();
}
