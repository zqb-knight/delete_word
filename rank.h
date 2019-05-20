#ifndef RANK_H
#define RANK_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

extern QSqlDatabase database;

namespace Ui {
class Rank;
}

class Rank : public QWidget
{
    Q_OBJECT

public:
    explicit Rank(QWidget *parent = nullptr);
    ~Rank();
    void Rank_init();
    void update_table(int role, int index);

private slots:


    void on_model_comboBox_currentIndexChanged(int index);

    void on_role_comboBox_currentIndexChanged(int index);

private:
    Ui::Rank *ui;
};

#endif // RANK_H
