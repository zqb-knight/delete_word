#include "list.h"
#include "ui_list.h"

List::List(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::List)
{
    is_looked = 0;
    ui->setupUi(this);
}

List::~List()
{
    delete ui;
}

void List::List_init()
{
    sreach(1);
}

void List::sreach(int f)
{
    int model = ui->comboBox->currentIndex();
    QString in = ui->lineEdit->text();
    int i = 0, temp = ui->lineEdit->text().trimmed().toInt();
    ui->tableWidget->clearContents();
    QString Roles;
    qDebug() << temp;
    QString select_sql;
    QSqlQuery sql_query(database);
    if(!f)
    {
        if(model == 0)
            select_sql = QString("select Account, Role, Level, Ex, Class from account where Account like '%1'").arg(in + '%');
        else if(model == 1)
            select_sql = QString("select Account, Role, Level, Ex, Class from account where Role = '%1' ").arg(temp);
        else if(model == 2)
            select_sql = QString("select Account, Role, Level, Ex, Class from account where Level = '%1' ").arg(temp);
        else if(model == 3)
            select_sql = QString("select Account, Role, Level, Ex, Class from account where Ex = '%1' ").arg(temp);
        else
            select_sql = QString("select Account, Role, Level, Ex, Class from account where Class = '%1' ").arg(temp);
    }
    else
       select_sql = "select Account, Role, Level, Ex, Class from account";



    if(!sql_query.exec(select_sql))
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            QString account = sql_query.value(0).toString();
            int flag = sql_query.value(1).toInt();
            int Level = sql_query.value(2).toInt();
            int Ex = sql_query.value(3).toInt();
            int clas = sql_query.value(4).toInt();

            if(flag == 1) Roles = "玩家";
            else {
                Roles = "出题者";
            }
            //int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(i);
            // id
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setText(account);
            ui->tableWidget->setItem(i, 0, item);

            item = new QTableWidgetItem();
            item->setText(Roles);
            ui->tableWidget->setItem(i, 1, item);

            item = new QTableWidgetItem();
            item->setText(QString::number(Level));
            ui->tableWidget->setItem(i, 2, item);

            item = new QTableWidgetItem();
            item->setText(QString::number(Ex));
            ui->tableWidget->setItem(i, 3, item);

            item = new QTableWidgetItem();
            item->setText(QString::number(clas));
            ui->tableWidget->setItem(i, 4, item);
            i++;
        }
    }


}

void List::on_sreach_PB_clicked()
{
    sreach(0);
}
