#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "player.h"
#include "questioner.h"

extern Player player;         //玩家
extern Questioner questioner; //出题者
extern int model;     //此时的模式，0代表玩家模式，1代表出题模式，-1代表未登录模式

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

};

#endif // LOGIN_H
