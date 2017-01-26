#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QTimer>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QSqlDatabase db;
    QTimer input_timer;
    bool input_flag;
    ~MainWindow();

private slots:
    void input_timer_timeout();
    void on_server_startbtn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
