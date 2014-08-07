#ifndef APIMANAGER_H
#define APIMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>
#include <QJsonArray>
//This defines the most basic class for a Riot API Request and should be used to instansiate all other members
class RiotAPI : public QObject
{
    Q_OBJECT
public:
    explicit RiotAPI(QObject *parent = 0);
    void requestBasicProfile(QString summoner_name);
  void setAPIKey(QString riotAPIKey);
  QString getSummonerID(){return summonerID;}
  QString getSummonerName(){return summonerName;}
  QString getSummonerLevel(){return summonerLevel;}
  QString getSummonerProfileIcon(){return summonerProfileIcon;}
  QString getAPIKey(){return riotAPI_Key;}
private:
QByteArray rawapidata;
protected:
    void ParseAndSet();
    QString riotAPI_Key;
    QNetworkAccessManager *qnam = new QNetworkAccessManager(this);
    QString summonerName;
    QString summonerID;
    QString summonerLevel;
    QString summonerProfileIcon;

signals:
void requestComplete(QByteArray data);

public slots:

void replyFinished(QNetworkReply*);
};

#endif // APIMANAGER_H
