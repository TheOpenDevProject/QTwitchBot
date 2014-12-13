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
#include <QPixmap>
//This defines the most basic class for a Riot API Request and should be used to instansiate all other members
class RiotAPI : public QObject
{
    Q_OBJECT
public:
    explicit RiotAPI(QObject *parent = 0);
    void requestBasicProfile(QString summoner_name);
    void requestSummonerIcon(QString summoner_name);
  void setAPIKey(QString riotAPIKey);
  void setSummonerRegion(QString region);
  QPixmap getSummonerProfilePixmap(){return summonerProfilePixmap;}
  QString getSummonerID(){return summonerID;}
  QString getSummonerName(){return summonerName;}
  QString getSummonerLevel(){return summonerLevel;}
  QString getSummonerProfileIcon(){return summonerProfileIcon;}
  QString getAPIKey(){return riotAPI_Key;}
    QString getSummonerRegion(){return summonerRegion;}
private:
QByteArray rawapidata;
protected:
    virtual void ParseAndSet();
    QString riotAPI_Key;
    QNetworkAccessManager *qnam = new QNetworkAccessManager(this);
    QString summonerName;
    QString summonerID;
    QString summonerLevel;
    QString summonerProfileIcon;
    QString summonerRegion;
    QPixmap summonerProfilePixmap;
signals:
void requestComplete(QByteArray data);
void requestComplete();
public slots:

virtual void replyFinished(QNetworkReply*);
};

class RiotAPI_RankedStats: public RiotAPI{
Q_OBJECT
public:
    explicit RiotAPI_RankedStats(QObject *parent =0);
    void getRankedStats();
    void setSummonerID(QString s_id);
    //Get Info
    QString getTierName(){return tierName;}
    QString getTier(){return tier;}
    QString getDivision(){return division;}
    QString getLeaguePoints(){return leaguePoints;}
    QString getSoloWins(){return soloWins;}
    QString getIsHotStreak(){return isHotStreak;}

private:
    QByteArray rawapidata;
    //Ranked specific data
    QString tierName,tier,division,leaguePoints,soloWins,isHotStreak;
protected:
    void ParseAndSet();

signals:
    void requestComplete(QByteArray data);
public slots:
    void replyFinished(QNetworkReply*);
};

class RiotAPI_InGameStats: public RiotAPI{
    Q_OBJECT
public:
    explicit RiotAPI_InGameStats(QObject *parent = 0);
    void getLastGameInfo();
    void setSummonerID(QString s_id);

};

#endif // APIMANAGER_H
