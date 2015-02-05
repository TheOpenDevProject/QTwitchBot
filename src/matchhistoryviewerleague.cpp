#include "matchhistoryviewerleague.h"
#include "ui_matchhistoryviewerleague.h"
#include <leaguematchhistorybox.h>
MatchHistoryViewerLeague::MatchHistoryViewerLeague(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatchHistoryViewerLeague)
{
    ui->setupUi(this);
    ui->listWidget->addItem(new LeagueMatchHistoryBox());
}

MatchHistoryViewerLeague::~MatchHistoryViewerLeague()
{
    delete ui;
}
