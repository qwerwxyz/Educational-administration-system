#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <teacher.h>
#include <course.h>
#include <student.h>
#include <vector>
#include <QMap>
#define forcom(type, it, com) for (vector<type>::iterator it = com.begin(); it != com.end(); it++)


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void new_connect();
    void read();
    void cinput();
    void oinput();
    void studentin();
    void teacherin();
    void savecom();
    void saveopt();
    void savestudent();
    void saveteacher();
    void update1();
    static bool comparenum1(const stu_data& a, const stu_data& b);
    static bool comparenum2(const stu_data& a,const stu_data &b);
    static bool comparenum3(const stu_data& a, const stu_data& b);
    static bool comparenum4(const stu_data& a, const stu_data& b);
public:
    static bool compare5(const coursedata &a,const coursedata &b);
    static bool compare6(const coursedata &a, const coursedata &b);
    static bool compare7(const coursedata &a, const coursedata &b);
    static bool compare8(const coursedata &a, const coursedata &b);
public:
    vector<student> stu;
private:
    Ui::MainWindow *ui;
    QTcpServer *server;
    QTcpSocket *socket;
    QList<QTcpSocket*> sockets;
    vector<teacher> tea;

    vector<compulsory>compulsory1;//必修课库
    vector<optional>optional1;//选修课库
    QMap<QString, bool> stumap;
    QMap<QString, bool> teamap;


};


#endif // MAINWINDOW_H
