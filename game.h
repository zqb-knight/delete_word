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
#include <QTimer>
#include "QMovie"
//#include "QFrame"


extern Login* login;    //登录窗口
extern QSqlDatabase database;   //数据库


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

    //void on_pushButton_2_clicked();

    void on_rank_PB_clicked();

    void on_update_pushButton_clicked();

    void on_start_pushButton_clicked();

    void on_unlogin_pushButton_clicked();

    void on_stage_comboBox_currentIndexChanged(int index);

    void handleTimeout();   //超时处理函数
    void ready_handleTimeout();

    void on_commit_pushButton_clicked();

    void on_next_pushButton_clicked();

    void on_question_commit_pushButton_clicked();

    void on_re_pushButton_clicked();

private:
    Ui::Game *ui;

    //窗口属性
    List list;      //用户查询窗口
    Rank rank;      //排行榜窗口

    int current_stage;
    QString current_word;

    //实现窗口可整体拖动，重写鼠标事件函数
    bool m_dragging; // 是否正在拖动
    QPoint m_startPosition; // 拖动开始前的鼠标位置
    QPoint m_framePosition; // 窗体的原始位置
    void game_init();      //游戏初始化
    //定时器
    QTimer *timer = new QTimer(this);
    QTimer *ready_timer = new QTimer(this);
    //QFrame *frame = new QFrame;
    QMovie* three_movie = new QMovie("3s.gif");

};

#endif // GAME_H
