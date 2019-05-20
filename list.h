#ifndef LIST_H
#define LIST_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QDebug>

extern QSqlDatabase database;

namespace Ui {
class List;
}

class List : public QWidget
{
    Q_OBJECT

public:
    int is_looked;    //查看标志，避免重复添加表格
    explicit List(QWidget *parent = nullptr);
    void List_init();
    void sreach(int f);
    ~List();

private slots:
    void on_sreach_PB_clicked();

private:
    Ui::List *ui;

};

#endif // LIST_H
