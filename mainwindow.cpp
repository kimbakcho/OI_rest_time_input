#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    input_flag = false;
    ui->timeEdit->setTime(QTime(8,0,0));
    input_timer.setInterval(1000);
    connect(&input_timer,SIGNAL(timeout()),SLOT(input_timer_timeout()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::input_timer_timeout()
{
    QTime current_time;
    current_time = QTime::currentTime();
    if((current_time.hour()==ui->timeEdit->time().hour()) && (current_time.minute()==ui->timeEdit->time().minute())){
        qDebug()<<"time ok message "<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        db.removeDatabase("temp_db1");
        db.close();
        db = QSqlDatabase::addDatabase("QMYSQL","temp_db1");
        db.setHostName("fabsv.wisol.co.kr");
        db.setUserName("EIS");
        db.setPassword("wisolfab!");
        db.setDatabaseName("FAB");
        if(!db.open()){
            qDebug()<<"open false";
            ui->textEdit->append("open false");
        }
        QSqlQuery query(db);
        QSqlQuery query1(db);
        QString query_txt = QString("select * from OI_system_rest_time_repeat_table");
        query.exec(query_txt);
        while(query.next()){
              QDateTime resttime;
              QDate rest_date = QDate::currentDate().addDays(query.value("puls_day").toInt());
              resttime.setDate(rest_date);
              resttime.setTime(query.value("rest_time").toTime());
              QString query_txt1 = QString("INSERT INTO `OI_system_remove_event_time` (`remove_time`, `remove_sec`,`content`) "
                                           "VALUES ('%1', '%2','%3')").arg(resttime.toString("yyyy-MM-dd hh:mm:ss")).arg(query.value("time_sec").toInt()).arg(query.value("content").toString());
              query1.exec(query_txt1);
              qDebug()<<"insert row message "<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
              ui->textEdit->append(QString("insert row message %1 ").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));
        }
        input_timer.setInterval(70000);
    }else {
        input_timer.setInterval(10000);

    }
}


void MainWindow::on_server_startbtn_clicked()
{
    input_timer.start();
    ui->textEdit->append("start sever");
}
