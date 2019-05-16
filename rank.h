#ifndef RANK_H
#define RANK_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

namespace Ui {
class Rank;
}

class Rank : public QWidget
{
    Q_OBJECT

public:
    explicit Rank(QWidget *parent = nullptr);
    ~Rank();
    void ranktable();

private:
    Ui::Rank *ui;
};

#endif // RANK_H
