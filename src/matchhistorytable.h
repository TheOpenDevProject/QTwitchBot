#ifndef MATCHHISTORYTABLE_H
#define MATCHHISTORYTABLE_H

#include <QWidget>

namespace Ui {
class MatchHistoryTable;
}

class MatchHistoryTable : public QWidget
{
    Q_OBJECT

public:
    explicit MatchHistoryTable(QWidget *parent = 0);
    ~MatchHistoryTable();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MatchHistoryTable *ui;
    void init();
    QStringList mht_headers;
};

#endif // MATCHHISTORYTABLE_H
