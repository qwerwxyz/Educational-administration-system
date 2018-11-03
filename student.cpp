#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
bool student::choose(optional &A, vector<student> &stu) {
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
}
