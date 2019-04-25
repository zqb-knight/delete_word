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
    QString account;
    QString password;
    std::string account_t;
    std::string password_t;
    account = ui->lineEdit_account->text();
    password = ui->lineEdit_password->text();
    qDebug() << "输入的账户为：" << account << endl;
    qDebug() << "输入的密码为：" << password << endl;

    //判断账号是否存在
    std::ifstream in;
    in.open("account.txt");
    while(!in.eof())
    {
        in >> account_t;
        in >> password_t;
        if(account_t == account.toStdString())
        {
            //判断密码是否正确
            if(password_t == password.toStdString())
            {
               qDebug() << "登录成功";
               g.show();
               return;
            }
            else
            {
                qDebug() << "密码错误";
                QMessageBox msbox;
                msbox.setText("密码错误");
                msbox.exec();
                return;
            }
        }
    }


}

//注册
void Login::on_pushButton_register_clicked()
{
    QString account;
    QString password;
    std::string account_t;
    std::string password_t;
    account = ui->lineEdit_account->text();
    password = ui->lineEdit_password->text();
    qDebug() << "输入的账户为：" << account << endl;
    qDebug() << "输入的密码为：" << password << endl;

    //判断账户是否已经存在
    std::ifstream in;
    in.open("account.txt");
    while(!in.eof())
    {
        in >> account_t;
        in >> password_t;
        if(account_t == account.toStdString())
        {
            QMessageBox msbox;
            msbox.setText("账户已存在");
            msbox.exec();
            qDebug() << "账户已存在,请更换账户名称";
            return;
        }
    }
    //添加新的账号与密码
    std::ofstream write;
    write.open("account.txt", std::ios::app);
    write << "\n" << account.toStdString() << " ";
    write << password.toStdString();
    QMessageBox msbox;
    msbox.setText("账户注册成功");
    msbox.exec();
    qDebug() << "账户注册成功";
}
