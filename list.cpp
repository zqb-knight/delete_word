#include "list.h"
#include "ui_list.h"

List::List(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::List)
{
    qDebug() << "666";
    ui->setupUi(this);
}

List::~List()
{
    delete ui;


}

void List::add_data()
{
//        QSqlQueryModel *model = new QSqlQueryModel;
//        model->setQuery("SELECT * FROM account", database);	//从给定的数据库db执行sql操作, db需预先制定并打开

//        int column = model->columnCount();	//获取列数
//        int row = model->rowCount();		//获取行数
    int i = 0;
    ui->tableWidget->clearContents();
    QSqlQuery sql_query;
    QString select_sql = "select Account, Level, Ex, Class from account";
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
