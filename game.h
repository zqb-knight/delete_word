#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QtGui>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "login.h"
#include "rank.h"
#include "list.h"


static QSqlDatabase database;   //数据库


namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();
    void update_user_info();
    //实现窗口可整体拖动，重写鼠标事件函数
    virtual void mouseMoveEvent ( QMouseEvent * event );
    virtual void mousePressEvent ( QMouseEvent * event );
    virtual void mouseReleaseEvent ( QMouseEvent * event );



private slots:
    void on_pushButton_clicked();

    void on_login_PB_clicked();


    void on_list_PB_clicked();

    void on_pushButton_2_clicked();

    void on_rank_PB_clicked();

private:
    Ui::Game *ui;

    Login login;    //登录窗口
    List list;      //用户查询窗口
    Rank rank;      //排行榜窗口



    //实现窗口可整体拖动，重写鼠标事件函数
    bool m_dragging; // 是否正在拖动
    QPoint m_startPosition; // 拖动开始前的鼠标位置
    QPoint m_framePosition; // 窗体的原始位置
};

#endif // GAME_H
