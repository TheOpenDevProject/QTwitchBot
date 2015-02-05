#ifndef TWITCHJSONAPIAMANGER_H
#define TWITCHJSONAPIAMANGER_H
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QStringListModel>
#include <QDebug>
#include <twitchuser.h>
class TwitchJSONAPIAManger: public QObject
{
    Q_OBJECT

public:
    TwitchJSONAPIAManger();
    ~TwitchJSONAPIAManger();
    std::vector<TwitchUser*> getUserList();
    void makeRequest(QString ChannelName);
private:
    QNetworkAccessManager *qnam  = new QNetworkAccessManager();

    QStringListModel userList_m,modList_m;
    std::vector<TwitchUser*> userList;
signals:
    //Pain-point
    void dataRequestable();
protected:
    QByteArray rawRequest;
    void parseJSON();

protected slots:
    virtual void replyFinished(QNetworkReply*);

};

#endif // TWITCHJSONAPIAMANGER_H
