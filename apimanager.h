#ifndef APIMANAGER_H
#define APIMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
//This defines the most basic class for a Riot API Request and should be used to instansiate all other members
class RiotAPI : public QObject
{
    Q_OBJECT
public:
    explicit RiotAPI(QObject *parent = 0);
//This method should not be called from any children
    void requestBasicProfile(QString summoner_name);
  void setAPIKey(QString riotAPIKey);
  QString getSummonerID(){return summonerID;}
  QString getSummonerName(){return summonerName;}
  QString getSummonerLevel(){return summonerLevel;}
  QString getSummonerProfileIcon(){return summonerProfileIcon;}

private:

protected:
  virtual void ParseAndSet(); //Each class should over-ride this depending on the JSON returned
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

/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
class LeagueRankedInfo :public RiotAPI
{
    Q_OBJECT
public:
QString getDivision(){return division;}
QString getLP(){return leaguePoints;}
QString getWins(){return wins;}
QString getTier(){return tier;}
QString getIsHotStreak(){return isHotStreak;}
QString getRankedSoloGamesPlayed(){return rankedSoloGamesPlayed;}
void requestBasicProfile(QString summoner_id);
private:

protected:
QString tier;
QString division;
QString isHotStreak;
QString wins;
QString rankedSoloGamesPlayed;
QString leaguePoints;
};

#endif // APIMANAGER_H
