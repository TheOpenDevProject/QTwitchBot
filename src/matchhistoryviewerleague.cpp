#include "matchhistoryviewerleague.h"
#include "ui_matchhistoryviewerleague.h"

MatchHistoryViewerLeague::MatchHistoryViewerLeague(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatchHistoryViewerLeague)
{
    ui->setupUi(this);
}

MatchHistoryViewerLeague::~MatchHistoryViewerLeague()
{
    delete ui;
}
