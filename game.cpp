#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    all_time = 0; //用于防沉迷
    total_timer->start(1000);
    model = -1;
    login = new(Login);
    //初始设置为未登录
    ui->setupUi(this);
    //设置窗口大小
    setFixedSize(1280, 720);
    //设置游戏背景
    QPixmap pixmap = QPixmap(":/back.png").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);
    // 不显示标题栏(亦无边框)
    //setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    game_init();

    //创建数据库
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

    //创建表格
    create_sql = "create table if not exists question_A (word varchar(15))";
    sql_query.prepare(create_sql);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create table." << sql_query.lastError();
    }
    else
    {
        qDebug() << "question_Table created!";
    }
    create_sql = "create table if not exists question_B (word varchar(15))";
    sql_query.prepare(create_sql);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create table." << sql_query.lastError();
    }
    else
    {
        qDebug() << "question_Table created!";
    }
    create_sql = "create table if not exists question_C (word varchar(15))";
    sql_query.prepare(create_sql);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create table." << sql_query.lastError();
    }
    else
    {
        qDebug() << "question_Table created!";
    }

    //定时器connect函数
    connect(timer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    connect(ready_timer, SIGNAL(timeout()), this, SLOT(ready_handleTimeout()));
    connect(game_timer, SIGNAL(timeout()), this, SLOT(game_handleTimeout()));
    connect(total_timer, SIGNAL(timeout()), this, SLOT(total_handleTimeout()));
}

//退出游戏
void Game::on_pushButton_clicked()
{
    close();
    database.close();
}

//显示登录框
void Game::on_login_PB_clicked()
{
    if(model == -1){
        game_init();
        login->show();
    }
    else{
        QMessageBox msbox;
        msbox.setText("同时只允许一人登录，请注销后再登录");
        msbox.exec();
        //update_user_info();
        return;
    }
}


//显示用户信息列表
void Game::on_list_PB_clicked()
{
    list.show();
    list.List_init();
}


//显示排行榜
void Game::on_rank_PB_clicked()
{
    rank.show();
    rank.Rank_init();
}

//更新用户信息
void Game::update_user_info()
{
    //面板信息更新
    questioner.clas = questioner.ex / 15;
    player.clas = player.ex / 10;
    QSqlQuery sql_query(database);
    QString update_sql = "UPDATE account SET Level = ?, Ex = ?, Class = ? WHERE Account = ?";
    sql_query.prepare(update_sql);
    if(model == 0)
    {
        ui->name_label->setText(player.name);
        ui->class_lebel->setText(QString::number(player.clas));
        ui->ex_label->setText(QString::number(player.ex));
        ui->level_label->setText(QString::number(player.level));
        sql_query.addBindValue(player.level);
        sql_query.addBindValue(player.ex);
        sql_query.addBindValue(player.clas);
        sql_query.addBindValue(player.name);

    }
    else if(model == 1)
    {
        ui->name_label->setText(questioner.name);
        ui->class_lebel->setText(QString::number(questioner.clas));
        ui->ex_label->setText(QString::number(questioner.ex));
        ui->level_label->setText(QString::number(questioner.question_number));
        sql_query.addBindValue(questioner.question_number);
        sql_query.addBindValue(questioner.ex);
        sql_query.addBindValue(questioner.clas);
        sql_query.addBindValue(questioner.name);
    }
    else {
        ui->name_label->setText("未登录");
        ui->class_lebel->setText("未登录");
        ui->ex_label->setText("未登录");
        ui->level_label->setText("未登录");
    }
    //数据库信息更新
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "inserted succeed!";
    }
}



//未点开始游戏前的界面，显示开始游戏按钮和图片
void Game::game_init()
{

    i = 0;
    t = 0;
    ui->start_pushButton->show();
    ui->re_pushButton->hide();
    ui->stage_L_label->hide();
    ui->stage_r_label->hide();
    ui->word_input_line->hide();
    ui->word_show_label->hide();
    ui->stage_comboBox->hide();
    ui->commit_pushButton->hide();
    ui->next_pushButton->hide();
    ui->word_input_line->hide();
    ui->word_show_label->hide();
    ui->title_label->hide();
    ui->select_comboBox->hide();
    ui->question_lineEdit->hide();
    ui->question_commit_pushButton->hide();
    ui->hard_label->hide();
    ui->stage_L_label_2->hide();
    ui->stage_M_label_2->hide();
    ui->stage_r_label_2->hide();
    ui->ready_label->hide();
    ui->tip_label->hide();
}

//选关界面
void Game::on_start_pushButton_clicked()
{
    if(model == -1)
    {

        QMessageBox msbox;
        msbox.setText("请先登录");
        msbox.exec();
    }
    else if(model == 0)
    {
        ui->start_pushButton->hide();
        ui->re_pushButton->show();
        ui->title_label->show();
        ui->stage_L_label->show();
        ui->stage_r_label->show();
        ui->stage_comboBox->show();
    }
    else {
        ui->start_pushButton->hide();
        ui->re_pushButton->show();
        ui->select_comboBox->show();
        ui->question_lineEdit->show();
        ui->question_lineEdit->clear();
        ui->question_commit_pushButton->show();
        ui->hard_label->show();
    }
}

//正式游戏界面
void Game::on_stage_comboBox_currentIndexChanged(int index)
{
    if(index <= player.level)
    {

        current_stage = index;
        ui->word_input_line->clear();
        ui->stage_M_label_2->setText(QString::number(current_stage));
        ui->next_pushButton->hide();
        ui->title_label->hide();
        ui->stage_L_label->hide();
        ui->stage_r_label->hide();
        ui->stage_comboBox->hide();
        ui->stage_L_label_2->show();
        ui->stage_M_label_2->show();
        ui->stage_r_label_2->show();
        ui->ready_label->show();
        t = 0;
        QSqlQuery sql_query(database);
        QString select_sql;
        //不同关卡难度设置不同
        if(current_stage <= 3)
            select_sql = "select word from question_A order by random() limit 1";
        else if(current_stage >= 4 && current_stage <= 7)
            select_sql = "select word from question_B order by random() limit 1";
        else
            select_sql = "select word from question_C order by random() limit 1";
        if(!sql_query.exec(select_sql))
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
            while(sql_query.next())
            {
                current_word = sql_query.value(0).toString();
            }
        }

        ui->word_show_label->setText(current_word);
        game_timer->start(1000);
        ready_timer->start(3000);
    }
    else {
        QMessageBox msbox;
        msbox.setText("请先解锁前面的关卡");
        msbox.exec();
    }
}


//答案提交处理
void Game::on_commit_pushButton_clicked()
{
    QString in_word = ui->word_input_line->text();
    if(in_word == current_word)
    {

        ui->word_input_line->hide();
        ui->commit_pushButton->hide();

        //实现不同关卡单词数目不同
        if(current_stage <= 3)
        {
            ui->next_pushButton->show();
            game_timer->stop();
            if(current_stage == player.level)
            {
                player.level++;
            }
        }

        else if(current_stage >= 4 && current_stage <= 7)
        {
            if(i != 1)
            {
                on_stage_comboBox_currentIndexChanged(current_stage);
                i++;
            }
            else{
                ui->next_pushButton->show();
                game_timer->stop();
                if(current_stage == player.level)
                {
                    player.level++;

                }
            }
        }
        else
        {
            if(i != 2)
            {
                on_stage_comboBox_currentIndexChanged(current_stage);
                i++;
            }
            else{
                ui->next_pushButton->show();
                game_timer->stop();
                if(current_stage == player.level)
                {
                    player.level++;

                }
            }
        }
    }

    else{
        QMessageBox msbox;
        msbox.setText("输入错误，已退回游戏开始环节");
        msbox.exec();
        game_init();
    }
    update_user_info();
}


//下一关按钮槽函数
void Game::on_next_pushButton_clicked()
{
    i = 0;
    player.ex = player.ex + current_stage * 10 - t * 2;
    t = 0;
    current_stage++;
    on_stage_comboBox_currentIndexChanged(current_stage);
    update_user_info();
}

//出题界面
void Game::on_question_commit_pushButton_clicked()
{
    QSqlQuery sql_query(database);
    int m = ui->select_comboBox->currentIndex();
    qDebug() << m;
    QString word = ui->question_lineEdit->text();
    int len = word.length();
    qDebug() << len;
    if((m == 0 && len <= 5) || (m == 1 && len >= 6 && len <= 10) || (m == 2 && len > 10))
    {
        QString insert_sql;
        if(m == 0)
            insert_sql = "insert into question_A values (?)";
        else if(m == 1)
            insert_sql = "insert into question_B values (?)";
        else
            insert_sql = "insert into question_C values (?)";
        sql_query.prepare(insert_sql);
        sql_query.addBindValue(word);

        if(!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            qDebug() << "inserted succeed!";
        }
    }
    else{
        QMessageBox msbox;
        msbox.setText("单词长度不符合要求");
        msbox.exec();
    }

    questioner.ex++;  //经验加1
    questioner.question_number++;
    update_user_info();
}

//注销操作
void Game::on_unlogin_pushButton_clicked()
{
    model = -1;
    update_user_info();
}

//返回操作
void Game::on_re_pushButton_clicked()
{
    game_init();
}

//更新用户信息框数据
void Game::on_update_pushButton_clicked()
{
    update_user_info();
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

//定时器超时处理槽函数
void Game::handleTimeout()
{
    timer->stop();
    ui->tip_label->hide();
    ui->word_show_label->hide();
    ui->word_input_line->show();
    ui->commit_pushButton->show();

}
void Game::ready_handleTimeout()
{
    ready_timer->stop();
    ui->ready_label->hide();
    ui->tip_label->show();
    //实现不同关卡时间不同
    timer->start(5000 - (current_stage * 200));
    ui->commit_pushButton->show();
    ui->word_show_label->show();
    ui->word_input_line->hide();
    ui->commit_pushButton->hide();
}

void Game::game_handleTimeout()
{
    t++;
}

void Game::total_handleTimeout()
{
    all_time++;
    if(all_time / 600)
    {
        QMessageBox msbox;
        msbox.setText("请休息一会儿吧");
        msbox.exec();
    }
}
Game::~Game()
{
    delete ui;
}
