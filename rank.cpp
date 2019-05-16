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

void Rank::ranktable()
{
    int i = 0;
    ui->tableWidget->clearContents();
    QSqlQuery sql_query;
    QString select_sql = "select Account, Level, Ex, Class from account order by Level desc";
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            QString account = sql_query.value(0).toString();
            int Level = sql_query.value(3).toInt();
            int Ex = sql_query.value(4).toInt();
            int clas = sql_query.value(5).toInt();
            //int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(i);
            // id
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setText(account);
            ui->tableWidget->setItem(i, 0, item);

            item = new QTableWidgetItem();
            item->setText(QString::number(Level));
            ui->tableWidget->setItem(i, 1, item);

            i++;

        }
    }
}
