#ifndef APIMANAGER_H
#define APIMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class RiotAPI : public QObject
{
    Q_OBJECT
public:
    explicit RiotAPI(QObject *parent = 0);
    QByteArray getDataAndFlushBuffer();
    void requestBasicProfile(QString summoner_name);
private:
QNetworkAccessManager *qnam = new QNetworkAccessManager(this);
    const QString riotAPI_Key = "INSERT_API_KEY";
protected:

signals:
void requestComplete(QByteArray data);
public slots:
void replyFinished(QNetworkReply*);
};

#endif // APIMANAGER_H
