#include "matchhistorytable.h"
#include "ui_matchhistorytable.h"
#include <QCheckBox>
MatchHistoryTable::MatchHistoryTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatchHistoryTable)
{
    ui->setupUi(this);
    mht_headers << "Map";
    mht_headers << "Duration";
    mht_headers << "Mode";
    mht_headers << "Type";
    mht_headers << "Queue Type";
    mht_headers << "Champion";
    mht_headers << "Summoner Spell 1";
    mht_headers << "Summoner Spell 2";
    mht_headers << "Assists";
    mht_headers << "Max Level";
    mht_headers << "Deaths";
    mht_headers << "Double Kills";
    mht_headers << "Helped Get First Blood";
    mht_headers << "First Blood";
    mht_headers << "First Inhib";
    mht_headers << "First Tower";
    mht_headers << "Total Gold";
    mht_headers << "Gold Spent";
    mht_headers << "Inhibs Killed";
    mht_headers << "Item 1";
    mht_headers << "Item 2";
    mht_headers << "Item 3";
    mht_headers << "Item 4";
    mht_headers << "Item 5";
    mht_headers << "Item 6";
    mht_headers << "Trinket";

                   this->init();
}

MatchHistoryTable::~MatchHistoryTable()
{
    delete ui;
}

void MatchHistoryTable::on_pushButton_clicked()
{

}

void MatchHistoryTable::init()
{
    ui->MatchHistoryViewTbl->setColumnCount(66);
    ui->MatchHistoryViewTbl->setRowCount(15);
    for(int i = 0; i < ui->MatchHistoryViewTbl->rowCount();i++){
     ui->MatchHistoryViewTbl->setCellWidget(i,65,new QCheckBox(this));
     ui->MatchHistoryViewTbl->setAlternatingRowColors(true);
    }
    ui->MatchHistoryViewTbl->setHorizontalHeaderLabels(mht_headers);
}
