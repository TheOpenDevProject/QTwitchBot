#ifndef MATCHHISTORYVIEWERLEAGUE_H
#define MATCHHISTORYVIEWERLEAGUE_H

#include <QWidget>

namespace Ui {
class MatchHistoryViewerLeague;
}

class MatchHistoryViewerLeague : public QWidget
{
    Q_OBJECT

public:
    explicit MatchHistoryViewerLeague(QWidget *parent = 0);
    ~MatchHistoryViewerLeague();

private:
    Ui::MatchHistoryViewerLeague *ui;
};

#endif // MATCHHISTORYVIEWERLEAGUE_H
