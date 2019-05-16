#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
//#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

//extern QSqlDatabase database;   //数据库
//extern QSqlQuery sql_query;

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
private slots:

    void on_pushButton_login_clicked();

    void on_pushButton_register_clicked();

private:
    Ui::Login *ui;
    //Game g;
    //Dialog log;
};

#endif // LOGIN_H
