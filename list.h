#ifndef LIST_H
#define LIST_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QDebug>

namespace Ui {
class List;
}

class List : public QWidget
{
    Q_OBJECT

public:
    explicit List(QWidget *parent = nullptr);
    void add_data();
    ~List();

private:
    Ui::List *ui;
};

#endif // LIST_H
