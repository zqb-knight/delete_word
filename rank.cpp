#include "rank.h"
#include "ui_rank.h"

Rank::Rank(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Rank)
{
    ui->setupUi(this);
}

Rank::~Rank()
{
    delete ui;
}

void Rank::Rank_init()
{
    update_table(0, 0);
}

//更新排行榜
void Rank::update_table(int role, int index)
{
    int i = 0;
    int model = index;      //排序方式，默认按照闯关数
    ui->tableWidget->clearContents();
    QSqlQuery sql_query;
    QString select_sql;
    if(model == 0)
        select_sql = "select Account, Role, Level, Ex, Class from account order by Level desc";
    else if(model == 1)
        select_sql = "select Account, Role, Level, Ex, Class from account order by Class desc";
    else {
        select_sql = "select Account, Role, Level, Ex, Class from account order by Ex desc";
    }

    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            QString account = sql_query.value(0).toString();
            int Roles = sql_query.value(1).toInt();
            int Level = sql_query.value(2).toInt();
            int Ex = sql_query.value(3).toInt();
            int clas = sql_query.value(4).toInt();
            //int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(i);
            // id
            if(role == Roles)
            {
                QTableWidgetItem* item = new QTableWidgetItem();
                item->setText(account);
                ui->tableWidget->setItem(i, 0, item);

                item = new QTableWidgetItem();
                item->setText(QString::number(Level));
                ui->tableWidget->setItem(i, 1, item);

                item = new QTableWidgetItem();
                item->setText(QString::number(Ex));
                ui->tableWidget->setItem(i, 2, item);

                item = new QTableWidgetItem();
                item->setText(QString::number(clas));
                ui->tableWidget->setItem(i, 3, item);

                i++;
            }

        }
    }
}

void Rank::on_model_comboBox_currentIndexChanged(int index)
{
    update_table(ui->role_comboBox->currentIndex(), index);
}

void Rank::on_role_comboBox_currentIndexChanged(int index)
{
    update_table(index, ui->model_comboBox->currentIndex());
}
