#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <qtimer.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new QTcpServer();
    connect(server, &QTcpServer::newConnection, this, &MainWindow::new_connect);
    try {
        if (!server->listen(QHostAddress::Any, 8765)) throw 1;
        cinput();
        oinput();
        teacherin();
        studentin();
    }
    catch (int x) {
        if (x == 1) {
            QMessageBox::warning(this, "警告", "端口错误");
        }
    }
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update1()));
    timer->start(10);
}
void MainWindow::update1(){
    QString str="world";
    qDebug()<<"hello0 "<<str<<"!"<<endl;
    saveteacher();
    savestudent();
    savecom();
    saveopt();
    qDebug()<<"hello "<<str<<"!"<<endl;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::new_connect() {
    socket = server->nextPendingConnection();
    sockets.append(socket);
    connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
}

void MainWindow::read() {
    QByteArray message;
    for (int ii = 0; ii < sockets.length(); ii++)
    {
        QDataStream in(sockets.at(ii));
        in.setVersion(QDataStream::Qt_5_4);
        message = sockets.at(ii)->readLine();
        if (message.isEmpty()) continue;
        try{
            if (message == "log\n") {
                ui->textEdit->insertPlainText("处理登录请求\n");
                message = sockets.at(ii)->readLine();
                if (message == "1\n") {
                    message = sockets.at(ii)->readLine();
                    if (stumap[message] == 1) throw 1;
                    bool flag = 0;
                    for (int i = 0; i < stu.size(); i++) {
                        if (QString::fromStdString(stu[i].num) + "\n" == QString::fromLatin1(message))
                        {
                            flag = 1;
                            break;
                        }
                    }
                    if (!flag) throw 1;
                    stumap[message] = 1;
                    sockets.at(ii)->write(tr("success\n").toLatin1());
                    sockets.at(ii)->write(tr("stu\n").toLatin1());
                    sockets.at(ii)->write(message);
                    sockets.at(ii)->flush();
                }
                else if (message == "2\n") {
                    message = sockets.at(ii)->readLine();
                    if (teamap[message] == 1) throw 1;
                    bool flag = 0;
                    for (int i = 0; i < tea.size(); i++) {
                        if (QString::fromStdString(tea[i].num) + "\n" == QString::fromLatin1(message))
                        {
                            flag = 1;
                            break;
                        }
                    }
                    if (!flag) throw 1;
                    teamap[message] = 1;
                    sockets.at(ii)->write(tr("success\n").toLatin1());
                    sockets.at(ii)->write(tr("tea\n").toLatin1());
                    sockets.at(ii)->write(message);
                    sockets.at(ii)->flush();
                }
                else throw 0;
            }
            else if (message == "course\n") {
                ui->textEdit->insertPlainText("处理显示全校课程\n");
                QString str = "全校必修课如下：\n课程名称\t\t课程编号\t\t学分\n";
                forcom(compulsory, it, compulsory1)
                    str += QString::fromStdString(it->name) + "\t\t"
                        + QString::number(it->num) + "\t\t" + QString::number(it->credit)
                            + "\n";

                str += "全校选修课：\n课程名称\t\t课程编号\t\t学分\n";
                forcom(optional, it, optional1)
                    if(it->name!="demo")
                        str += QString::fromStdString(it->name)
                        + "\t\t" + QString::number(it->num) + "\t\t" + QString::number(it->credit)
                                + "\n";

                sockets.at(ii)->write(tr("data\n").toLatin1());
                sockets.at(ii)->write(str.toUtf8());
                sockets.at(ii)->flush();
            }
            else if(message == "self\n") {
                ui->textEdit->insertPlainText("处理显示任教课程请求\n");
                message = sockets.at(ii)->readLine();
                vector<int> t_compulsory, t_optional;
                for (int i = 0; i < tea.size(); i++)
                    if (QString::fromLatin1(message) == QString::fromStdString(tea[i].num) + "\n")
                        t_compulsory = tea[i].t_compulsory;
                QString str = "您任教的必修课如下：\n课程名称\t\t课程编号\t\t学分\n";
                for (int i = 0; i < t_compulsory.size(); i++) {
                    str += QString::fromStdString(compulsory1[t_compulsory[i]].name)
                            + "\t\t" + QString::number(compulsory1[t_compulsory[i]].num)
                            + "\t\t" + QString::number(compulsory1[t_compulsory[i]].credit)
                            + "\n";
                }
                str += "您任教的选修课如下：\n";
                for (int i = 0; i < tea.size(); i++)
                    if (QString::fromLatin1(message) == QString::fromStdString(tea[i].num) + "\n")
                        t_optional = tea[i].t_optional;
                for (int i = 0; i < t_optional.size(); i++) {
                    str += QString::fromStdString(optional1[t_optional[i]].name)
                            + "\t\t" + QString::number(optional1[t_optional[i]].num)
                            + "\t\t" + QString::number(optional1[t_optional[i]].credit)
                            + "\n";
                }
                sockets.at(ii)->write(tr("data\n").toLatin1());
                sockets.at(ii)->write(str.toUtf8());
                sockets.at(ii)->flush();
            }
            else if(message == "showstu\n"){
                ui->textEdit->insertPlainText("处理显示所教学生请求\n");
                message = sockets.at(ii)->readLine();
                vector<int> t_compulsory, t_optional;
                for (int i = 0; i < tea.size(); i++)
                    if (QString::fromLatin1(message) == QString::fromStdString(tea[i].num) + "\n")
                        t_compulsory = tea[i].t_compulsory;
                QString str = "您任教的必修课有：\n";
                for (int i = 0; i < t_compulsory.size(); i++) {
                    str += QString::fromStdString(compulsory1[t_compulsory[i]].name)
                           +"\n该课程的学生有：\n姓名\t学号\t班级\t学院\n";
                    forcom(stu_data, it2, compulsory1[t_compulsory[i]].data) {
                        str += QString::fromStdString(it2->name)+"\t"+ QString::fromStdString(it2->num) + "\t"
                            + QString::fromStdString(it2->classnum) + "\t" +  QString::fromStdString(it2->college)+"\n";
                    }
                }
                str += "您任教的选修课有：\n";
                for (int i = 0; i < tea.size(); i++)
                    if (QString::fromLatin1(message) == QString::fromStdString(tea[i].num) + "\n")
                        t_optional = tea[i].t_optional;
                for (int i = 0; i < t_optional.size(); i++) {
                    str += QString::fromStdString(optional1[t_optional[i]].name)
                           +"\n该课程的学生有：\n姓名\t学号\t班级\t学院\n";
                    forcom(stu_data, it2, optional1[t_optional[i]].data) {
                        str += QString::fromStdString(it2->name)+"\t"+ QString::fromStdString(it2->num) + "\t"
                            + QString::fromStdString(it2->classnum) + "\t" +  QString::fromStdString(it2->college)+"\n";
                    }
                }
                sockets.at(ii)->write(tr("data\n").toLatin1());
                sockets.at(ii)->write(str.toUtf8());
                sockets.at(ii)->flush();

            }
            else if(message == "askstu\n"){
                ui->textEdit->insertPlainText("处理输入成绩预选择请求\n");
                message = sockets.at(ii)->readLine();//读老师的编号
                int k;
                for (k = 0; k < tea.size(); k++)
                    if (QString::fromLatin1(message) == QString::fromStdString(tea[k].num) + "\n")
                        break;
                int ctype = QString::fromLatin1(sockets.at(ii)->readLine()).toInt();
                message = sockets.at(ii)->readLine();//课编号
                QString str = QString::fromLatin1(message);
                int m = str.toInt();
                QString str1;
                bool flag = 0;
                if (ctype == 1) {
                    for (int i = 0; i < tea[k].t_compulsory.size(); i++)
                        if (compulsory1[tea[k].t_compulsory[i]].num == m)
                            flag = 1;
                }
                else {
                    for (int i = 0; i < tea[k].t_optional.size(); i++)
                        if (optional1[tea[k].t_optional[i]].num == m)
                            flag = 1;
                }
                if (!flag) throw 4;
                if (ctype == 1) forcom(stu_data, it, compulsory1[m].data) {
                        if (it->grade == -1)
                            str1 += QString::fromStdString(it->name)+
                                    "成绩尚未输入\t"+"\t"+ ":\n";
                        else
                            str1 +=QString::fromStdString(it->name)+
                                    "当前成绩为\t"+QString::number(it->grade)+"\n";
                        //it->gpa = compulsory1[tea[k].t_compulsory[i - 1]].getgpa(r);
                    }
                else forcom(stu_data, it, optional1[m].data) {
                                        if (it->grade == -1)
                                            str1 += QString::fromStdString(it->name)+
                                                    "成绩尚未输入\t"+"\t"+ ":\n";
                                        else
                                            str1 +=QString::fromStdString(it->name)+
                                                    "当前成绩为\t"+QString::number(it->grade)+"\n";
                                        //it->gpa = compulsory1[tea[k].t_compulsory[i - 1]].getgpa(r);
                                    }
                sockets.at(ii)->write(tr("returnstu\n").toLatin1());
                if (ctype == 1)
                    sockets.at(ii)->write((QString::number(compulsory1[m].stu_num)+"\n").toLatin1());
                else
                    sockets.at(ii)->write((QString::number(optional1[m].stu_num)+"\n").toLatin1());
                sockets.at(ii)->write(str1.toUtf8());
                sockets.at(ii)->flush();
            }

            else if(message == "inputgrade\n"){
                ui->textEdit->insertPlainText("处理输入成绩请求\n");
                message = sockets.at(ii)->readLine();//读老师的编号
                int k;
                for (k = 0; k < tea.size(); k++)
                    if (QString::fromLatin1(message) == QString::fromStdString(tea[k].num) + "\n")
                        break;
                int ctype = QString::fromLatin1(sockets.at(ii)->readLine()).toInt();
                message = sockets.at(ii)->readLine();//课编号
                QString str = QString::fromLatin1(message);
                int m = str.toInt();
                bool flag = 0;
                if (ctype == 1) {
                    for (int i = 0; i < tea[k].t_compulsory.size(); i++)
                        if (compulsory1[tea[k].t_compulsory[i]].num == m)
                            flag = 1;
                }
                else {
                    for (int i = 0; i < tea[k].t_optional.size(); i++)
                        if (optional1[tea[k].t_optional[i]].num == m)
                            flag = 1;
                }
                QVector<QString> ss;
                int astu = QString::fromLatin1(sockets.at(ii)->readLine()).toInt();
                for (int i = 0; i < astu; i++) ss.push_back(QString::fromLatin1(sockets.at(ii)->readLine()));
                if (!flag) throw 4;
                int realstu = ctype == 1? compulsory1[m].stu_num:
                        optional1[m].stu_num;


                if (astu != realstu) {
                    throw 5;
                }
                int i = 0;
                if (ctype == 1) forcom(stu_data, it, compulsory1[m].data) {
                    QString str = ss[i++];
                    if (str == "\n") continue;
                    bool ok;
                    int mm = str.toInt(&ok);
                    if (!ok) throw 7;
                    if (it->flag) throw 6;
                    it->grade = mm;
                    it->gpa = compulsory1[m].getgpa(mm);
                }
                else forcom(stu_data, it, optional1[m].data){
                    message = sockets.at(ii)->readLine();//读学生成绩
                    QString str = ss[i++];
                    if (str == "\n") continue;
                    bool ok;
                    int mm = str.toInt(&ok);
                    if (!ok) throw 7;
                    if (it->flag) throw 6;
                    it->grade = mm;
                    it->gpa = optional1[m].getgpa(mm);
                }
            }
            else if (message == "handgrade\n") {
                ui->textEdit->insertPlainText("处理提交成绩请求\n");
                message = sockets.at(ii)->readLine();//读老师的编号
                int k;
                for (k = 0; k < tea.size(); k++)
                    if (QString::fromLatin1(message) == QString::fromStdString(tea[k].num) + "\n")
                        break;
                int ctype = QString::fromLatin1(sockets.at(ii)->readLine()).toInt();
                message = sockets.at(ii)->readLine();//课编号
                QString str = QString::fromLatin1(message);
                int m = str.toInt();
                bool flag = 0;
                if (ctype == 1) {
                    for (int i = 0; i < tea[k].t_compulsory.size(); i++)
                        if (compulsory1[tea[k].t_compulsory[i]].num == m)
                            flag = 1;
                }
                else {
                    for (int i = 0; i < tea[k].t_optional.size(); i++)
                        if (optional1[tea[k].t_optional[i]].num == m)
                            flag = 1;
                }

                if (ctype == 1) forcom(stu_data, it, compulsory1[m].data) {
                    if (it->grade < 0) throw -1;
                    it->flag = 1;
                }
                else forcom(stu_data, it, optional1[m].data){
                    if (it->grade < 0) throw -1;
                    it->flag = 1;
                }
                str = "handsuccess\n";
                sockets.at(ii)->write(str.toLatin1());
                sockets.at(ii)->flush();
            }
            else if (message == "logout\n") {
                ui->textEdit->insertPlainText("处理登出请求\n");
                QByteArray tmp = sockets.at(ii)->readLine();
                message = sockets.at(ii)->readLine();
                if (tmp == "1\n") stumap[message] = 0;
                else teamap[message] = 0;
            }
            else if(message == "asksort\n"){
                ui->textEdit->insertPlainText("处理老师排序\n");
                message = sockets.at(ii)->readLine();//读老师的编号
                int k;
                for (k = 0; k < tea.size(); k++)
                    if (QString::fromLatin1(message) == QString::fromStdString(tea[k].num) + "\n")
                        break;
                int ctype = QString::fromLatin1(sockets.at(ii)->readLine()).toInt();
                message = sockets.at(ii)->readLine();//课编号
                QString str = QString::fromLatin1(message);
                int m = str.toInt();
                bool flag = 0;
                if (ctype == 1) {
                    for (int i = 0; i < tea[k].t_compulsory.size(); i++)
                        if (compulsory1[tea[k].t_compulsory[i]].num == m)
                            flag = 1;
                }
                else {
                    for (int i = 0; i < tea[k].t_optional.size(); i++)
                        if (optional1[tea[k].t_optional[i]].num == m)
                            flag = 1;
                }
                if (!flag) throw 4;
                int y = QString::fromLatin1(sockets.at(ii)->readLine()).toInt();
                str = "";
                if (ctype == 1) {
                    if (y == 1) sort(compulsory1[m].data.begin(), compulsory1[m].data.end(), comparenum1);
                    else if (y == 2)sort(compulsory1[m].data.begin(), compulsory1[m].data.end(), comparenum2);
                    else if (y == 3)sort(compulsory1[m].data.begin(), compulsory1[m].data.end(), comparenum3);
                    else if (y == 4)sort(compulsory1[m].data.begin(), compulsory1[m].data.end(), comparenum4);
                    forcom (stu_data, it, compulsory1[m].data) {
                        str += QString::fromStdString(it->name) + "\t"
                                + QString::fromStdString(it->num) + "\t"
                                + QString::number(it->grade) + "\t" +
                                QString::number(it->gpa) + "\n";
                    }
                }
                else {
                    if (y == 1) sort(optional1[m].data.begin(), optional1[m].data.end(), comparenum1);
                    else if (y == 2) sort(optional1[m].data.begin(), optional1[m].data.end(), comparenum2);
                    else if (y == 3) sort(optional1[m].data.begin(), optional1[m].data.end(), comparenum3);
                    else if (y == 4) sort(optional1[m].data.begin(), optional1[m].data.end(), comparenum4);
                    forcom (stu_data, it, optional1[m].data) {
                        str += QString::fromStdString(it->name) + "\t"
                                + QString::fromStdString(it->num) + "\t"
                                + QString::number(it->grade) + "\t" +
                                QString::number(it->gpa) + "\n";
                    }
                }
                sockets.at(ii)->write(tr("data\n").toLatin1());
                sockets.at(ii)->write(str.toLatin1());

                sockets.at(ii)->flush();
            }
            else if(message == "show_own_course\n"){
                ui->textEdit->insertPlainText("处理显示学生课程请求\n");
                message = sockets.at(ii)->readLine();
                vector<int> s_compulsory, s_optional;
                for (int i = 0; i < stu.size(); i++)
                    if (QString::fromLatin1(message) == QString::fromStdString(stu[i].num) + "\n")
                        s_compulsory = stu[i].s_compulsory;
                QString str = "你的必修课如下：\n课程名称\t课程编号\t学分\n";
                for (int i = 0; i < s_compulsory.size(); i++) {
                    str += QString::fromStdString(compulsory1[s_compulsory[i]].name)
                            + "\t" + QString::number(compulsory1[s_compulsory[i]].num)
                            + "\t" + QString::number(compulsory1[s_compulsory[i]].credit)
                            + "\n";
                }
                str += "你的选修课如下：\n";
                for (int i = 0; i < stu.size(); i++)
                    if (QString::fromLatin1(message) == QString::fromStdString(stu[i].num) + "\n")
                        s_optional = stu[i].s_optional;
                if(s_optional.size()==0){
                    str += "你没有选修课\n";
                }
                else{
                    for (int i = 0; i < s_optional.size(); i++) {
                    str += QString::fromStdString(optional1[s_optional[i]].name)
                            + "\t" + QString::number(optional1[s_optional[i]].num)
                            + "\t" + QString::number(optional1[s_optional[i]].credit)
                            + "\n";
                    }
                }
                sockets.at(ii)->write(tr("data\n").toLatin1());
                sockets.at(ii)->write(str.toUtf8());
                sockets.at(ii)->flush();
            }
            else if (message == "choose\n") {
                ui->textEdit->insertPlainText("处理选课\n");
                message = sockets.at(ii)->readLine();
                int x = QString::fromLatin1(sockets.at(ii)->readLine()).toInt();
                if (x >= 0 && x < optional1.size()) {
                    for (int i = 0; i < stu.size(); i++)
                        if (QString::fromLatin1(message) == QString::fromStdString(stu[i].num) + "\n")
                            if (stu[i].choose(optional1[x], stu)) {
                                sockets.at(ii)->write(tr("tip\n").toLatin1());
                                sockets.at(ii)->write(tr("选课成功\n").toUtf8());
                                sockets.at(ii)->flush();
                            }
                            else {
                                sockets.at(ii)->write(tr("tip\n").toLatin1());
                                sockets.at(ii)->write(tr("选课失败\n").toUtf8());
                                sockets.at(ii)->flush();
                            }
                }
                else throw 4;
            }
            else if (message == "withdraw\n") {
                ui->textEdit->insertPlainText("处理退课\n");
                message = sockets.at(ii)->readLine();
                int x = QString::fromLatin1(sockets.at(ii)->readLine()).toInt();
                if (x >= 0 && x < optional1.size()) {
                    for (int i = 0; i < stu.size(); i++)
                        if (QString::fromLatin1(message) == QString::fromStdString(stu[i].num) + "\n")
                            if (stu[i].del(optional1[x], stu)) {
                                sockets.at(ii)->write(tr("tip\n").toLatin1());
                                sockets.at(ii)->write(tr("退课成功\n").toUtf8());
                                sockets.at(ii)->flush();
                            }
                            else {
                                sockets.at(ii)->write(tr("tip\n").toLatin1());
                                sockets.at(ii)->write(tr("退课失败\n").toUtf8());
                                sockets.at(ii)->flush();
                            }
                }
                else throw 4;
            }
            else if (message == "showallgrade\n") {
                ui->textEdit->insertPlainText("处理课程排序\n");
                message = sockets.at(ii)->readLine();//读学生的编号
                int k;
                for (k = 0; k < stu.size(); k++)
                    if (QString::fromLatin1(message) == QString::fromStdString(stu[k].num) + "\n")
                        break;
                int a = QString::fromLatin1(sockets.at(ii)->readLine()).toInt();
                sockets.at(ii)->write(tr("data\n").toLatin1());
                sockets.at(ii)->write(stu[k].showallgrade(a, compulsory1, optional1).toUtf8());
                sockets.at(ii)->flush();
            }
        }
        catch (int x) {
            if (x == 1) {
                QString str = "fail\n";
                sockets.at(ii)->write(str.toLatin1());
                sockets.at(ii)->flush();
            }
            else if (x == 4 || x == 5){
                QString str = "numerror\n";
                sockets.at(ii)->write(str.toLatin1());
                sockets.at(ii)->flush();
            }
            else if (x == 6) {
                QString str = "changeerror\n";
                sockets.at(ii)->write(str.toLatin1());
                sockets.at(ii)->flush();
            }
            else if (x == 7) {
                QString str = "gradeerror\n";
                sockets.at(ii)->write(str.toLatin1());
                sockets.at(ii)->flush();
            }
            else if (x == -1) {
                QString str = "handfail\n";
                sockets.at(ii)->write(str.toLatin1());
                sockets.at(ii)->flush();
            }
        }
    }
}

bool MainWindow::comparenum1(const stu_data& a, const stu_data& b) {
    if (a.num > b.num) return true;
    return false;
}
bool MainWindow::comparenum2(const stu_data& a,const stu_data &b) {
    if (b.num > a.num) return true;
    return false;
}
bool MainWindow::comparenum3(const stu_data& a, const stu_data& b) {
    if (a.grade > b.grade) return true;
    return false;
}
bool MainWindow::comparenum4(const stu_data& a, const stu_data& b) {
    if (b.grade > a.grade) return true;
    return false;
}

bool MainWindow::compare5(const coursedata &a,const coursedata &b) {//按成绩排序
    if (a.grade > b.grade)return true;
    return false;
}
bool MainWindow::compare6(const coursedata &a, const coursedata &b) {
    if (a.grade < b.grade)return true;
    return false;
}
bool MainWindow::compare7(const coursedata &a, const coursedata &b) {//按绩点排序
    if (a.gpa > b.gpa)return true;
    return false;
}
bool MainWindow::compare8(const coursedata &a, const coursedata &b) {
    if (a.gpa < b.gpa)return true;
    return false;
}

/*bool student::choose(optional &A, vector<student> &stu) {
    for (vector<stu_data>::iterator it = A.data.begin(); it != A.data.end(); it++) {//在A课程中找学生
        if (it->name == name) {

            return 0;
        }
    }
    stu_data a = stu_data(false, "空", "0","0","0" ,-1, 0);
    forcom (student, itnum, stu) {//将学生放入课程的信息中
        if (itnum->name == name) {
            stu_data buffer = stu_data(false, itnum->name,itnum->num,itnum->classnum,itnum->college, -1, 0);
            a = buffer;
            break;
        }
    }
    olen++;
    s_optional.push_back(A.num);//将课程放入学生的信息中
    A.data.push_back(a);
    A.stu_num++;
    return 1;
}

bool student::del(optional &A, vector<student> &stu) {
    int flag = 0;
    vector<stu_data>::iterator it;
    for ( it = A.data.begin(); it != A.data.end(); it++) {//将学生从课程的信息中删除
        if (it->flag == true) {

            return 0;
        }
        if (it->num == num) {
            flag = 1;
            break;
        }
    }
    if (flag == 0) {//在课程的学生名单中找不到该学生

        return 0;
    }
    A.data.erase(it);
    vector<int>::iterator it2;
    for (it2 = s_optional.begin(); it2 != s_optional.end(); it2++) {
        if ((*it2) == A.num) {//遍历找到课程
            break;
        }
    }
    olen--;
    s_optional.erase(it2);//删除课程信息
    A.stu_num--;
    return 1;
}

void student::getcoursegrade(vector<compulsory> &compulsory1, vector<optional> &optional1) {
    coursedata1.clear();
    for (int i = 0; i < s_compulsory.size(); i++) {
        if (compulsory1[s_compulsory[i]].data[0].grade == -1) continue;
        else
            for (int j = 0; j < 5; j++) {
                if (compulsory1[s_compulsory[i]].data[j].name == this->name) {
                    coursedata A = coursedata(compulsory1[s_compulsory[i]].name, compulsory1[s_compulsory[i]].num, compulsory1[s_compulsory[i]].data[j].grade, compulsory1[s_compulsory[i]].data[j].gpa);
                    coursedata1.push_back(A);
            }
        }
    }
    for (int i = 0; i < s_optional.size(); i++) {
        if (optional1[s_optional[i]].data[0].grade == -1) continue;
        else
            for (int j = 0; j < optional1[s_optional[i]].data.size(); j++) {
                if (optional1[s_optional[i]].data[j].name == this->name) {
                    coursedata A = coursedata(optional1[s_optional[i]].name, optional1[s_optional[i]].num, optional1[s_optional[i]].data[j].grade, optional1[s_optional[i]].data[j].gpa);
                    coursedata1.push_back(A);
                }
            }
    }
}

QString student::showallgrade(int a, vector<compulsory> &compulsory1, vector<optional> &optional1) {
    getcoursegrade(compulsory1, optional1);
    if (a == 1) sort(coursedata1.begin(), coursedata1.end(), MainWindow::compare5);
    else if (a == 2)sort(coursedata1.begin(), coursedata1.end(), MainWindow::compare6);
    else if (a == 3)sort(coursedata1.begin(), coursedata1.end(), MainWindow::compare7);
    else if (a == 4)sort(coursedata1.begin(), coursedata1.end(), MainWindow::compare8);
    QString str = "名称    \t成绩     \t绩点\n";
    for (int i = 0; i < coursedata1.size(); i++) {
        str += QString::fromStdString(coursedata1[i].name) + "\t" +
                QString::number(coursedata1[i].grade) + "\t" + QString::number(coursedata1[i].gpa) + "\n";
    }
    return str;
}*/
