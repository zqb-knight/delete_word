#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    //设置窗口大小
    setFixedSize(1280, 720);
    // 不显示标题栏(亦无边框)
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    // 背景透明(全自画)
    //setAttribute(Qt::WA_TranslucentBackground);

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
    QString create_sql = "create table if not exists account (Account varchar(15), Password varchar(15), Role int, Level int, Ex int, Class int)";
    sql_query.prepare(create_sql);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create table." << sql_query.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }
//    QString insert_sql = "insert or ignore into account values (?, ?, ?, ?, ?, ?)";
//    sql_query.prepare(insert_sql);
//    sql_query.addBindValue("admin");
//    sql_query.addBindValue("admin");
//    sql_query.addBindValue(1);
//    sql_query.addBindValue(100);
//    sql_query.addBindValue(10);
//    sql_query.addBindValue(100);
//    if(!sql_query.exec())
//    {
//        qDebug() << sql_query.lastError();
//    }
//    else
//    {
//        qDebug() << "inserted admin!";
//    }
}

Game::~Game()
{
    delete ui;
}

void Game::mousePressEvent(QMouseEvent *event)
{
    // 只响应左键
    if (event->button() == Qt::LeftButton)
    {
        m_dragging = true;
        m_startPosition = event->globalPos();
        m_framePosition = frameGeometry().topLeft();
    }

    QWidget::mousePressEvent(event);
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    // 只响应左键
    if (event->buttons() & Qt::LeftButton)
    {
        if(m_dragging)
        {
            // delta 相对偏移量,
            QPoint delta = event->globalPos() - m_startPosition;

            // 新位置：窗体原始位置  + 偏移量
            move(m_framePosition + delta);
        }
    }

    QWidget::mouseMoveEvent(event);
}

void Game::mouseReleaseEvent ( QMouseEvent * event )
{
    // 结束dragging
    m_dragging = false;
    QWidget::mouseReleaseEvent(event);
}

void Game::on_pushButton_clicked()
{
    close();
}

void Game::on_login_PB_clicked()
{
    login.show();
}



void Game::on_list_PB_clicked()
{

    list.show();
    list.add_data();
}

void Game::on_pushButton_2_clicked()
{
    QSqlQuery sql_query;
    sql_query.prepare("delete from account");
    if(!sql_query.exec())
    {
    qDebug()<<sql_query.lastError();
    }
    else
    {
    qDebug()<<"cleared";
    }
}

void Game::on_rank_PB_clicked()
{
    rank.show();
    rank.ranktable();
}
