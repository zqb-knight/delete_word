#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

//登录

void Login::on_pushButton_login_clicked()
{
    //从文本框中获取输入和账户和密码
    int role = ui->comboBox->currentIndex();
    QString account = ui->lineEdit_account->text();;
    QString password = ui->lineEdit_password->text();
    int role_t;
    QString account_t;
    QString password_t;
    QMessageBox msbox;
    qDebug() << "输入的账户为：" << account << endl;
    qDebug() << "输入的密码为：" << password << endl;

    QSqlQuery sql_query;
    QString select_sql = "select Account, Password, Role from account";
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            account_t = sql_query.value(0).toString();
            password_t = sql_query.value(1).toString();
            role_t = sql_query.value(2).toInt();
            if(account == account_t && role == role_t)
            {
                if(password == password_t)
                {
                    qDebug() << "登录成功";
                    close();
                    return;
                }
                msbox.setText("密码错误");
                msbox.exec();
                qDebug() << "密码错误";
                return;
            }
        }
        msbox.setText("账户不存在，请重新输入");
        msbox.exec();
        qDebug() << "账户不存在,请重新输入";
        return;

    }
}


//注册
void Login::on_pushButton_register_clicked()
{
    //从文本框中获取输入和账户和密码
    int role = ui->comboBox->currentIndex();
    QString account = ui->lineEdit_account->text();;
    QString password = ui->lineEdit_password->text();
    int role_t;
    QString account_t;
    QString password_t;
    qDebug() << "输入的账户为：" << account << endl;
    qDebug() << "输入的密码为：" << password << endl;

    //判断账户是否已经存在
    QSqlQuery sql_query;
    QString select_sql = "select Account, Password, Role from account";
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            account_t = sql_query.value(0).toString();
            password_t = sql_query.value(1).toString();
            role_t = sql_query.value(3).toInt();
            if(account == account_t && password == password_t && role == role_t)
            {
                QMessageBox msbox;
                msbox.setText("账户已存在");
                msbox.exec();
                qDebug() << "账户已存在,请更换账户名称";
                return;
            }
        }
    }

    QString insert_sql = "insert into account values (?, ?, ?, ?, ?, ?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(account);
    sql_query.addBindValue(password);
    sql_query.addBindValue(role);
    sql_query.addBindValue(0);
    sql_query.addBindValue(0);
    sql_query.addBindValue(0);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "inserted succeed!";
    }
    QMessageBox msbox;
    msbox.setText("账户注册成功");
    msbox.exec();
    qDebug() << "账户注册成功";
    return;
}


