#include <QApplication>
#include "game.h"

QSqlDatabase database;   //数据库
Login* login;    //登录窗口
Player player;         //玩家
Questioner questioner; //出题者
int model;     //此时的模式，0代表玩家模式，1代表出题模式，-1代表未登录模式
Game* g;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    g = new(Game);
    //打开游戏界面
    g->show();

/*
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("MyDataBase.db");
        database.setUserName("XingYeZhiXia");
        database.setPassword("123456");
    }
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        // do something
    }
    QSqlQuery sql_query(database);
    QString create_sql = "create table account (Account varchar(15), Password varchar(15), Role int, Level int, Ex int, Class int)";
    sql_query.prepare(create_sql);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create table." << sql_query.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }
    QString insert_sql = "insert into account values (?, ?, ?, ?, ?, ?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue("admin");
    sql_query.addBindValue("admin");
    sql_query.addBindValue(1);
    sql_query.addBindValue(100);
    sql_query.addBindValue(10);
    sql_query.addBindValue(100);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "inserted admin!";
    }
    */
    /*
    if(!sql_query.exec("INSERT INTO student VALUES(3, \"Li\", 23)"))
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "inserted Admin!";
    }
    */
    /*
    QString select_sql = "select id, name from student";
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            int id = sql_query.value(0).toInt();
            QString name = sql_query.value(1).toString();
            qDebug()<<QString("id:%1    name:%2").arg(id).arg(name);
        }
    }

     * QString clear_sql = "delete from student";
    sql_query.prepare(clear_sql);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "table cleared";
    }
    */

    //qDebug("7777");

    return a.exec();
}
