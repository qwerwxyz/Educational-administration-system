#include"course.h"
#include"teacher.h"
#include"student.h"
#include "mainwindow.h"

#include<fstream>
istream& operator>>(istream& FILE, compulsory &A) {//重载运算符
    FILE >> A.name >> A.num >> A.stu_num >> A.credit;
    while (A.name.length() < 15) A.name += " ";
    return FILE;
}
istream& operator>>(istream& FILE, stu_data &A) {//重载运算符
    FILE >> A.flag >> A.name >> A.num >> A.classnum >> A.college >> A.grade >> A.gpa;
    return FILE;
}

string root = "C:/Users/1wxyw/Desktop/kkk/";
void MainWindow::cinput() {
    //课程的读取
    compulsory1.clear();
    int i = 0, j = 0;
    ifstream file(root + "compulsory2.txt", ios::in);
    if (!file)
    {
        throw 0;
    }
    while (i < 5) {
        j = 0;
        compulsory Q;
        file >> Q;
        while (j < Q.stu_num) {
            stu_data P;
            file >> P;
            Q.data.push_back(P);
            j++;
        }
        i++;
        compulsory1.push_back(Q);
    }
}
istream& operator>>(istream& FILE, optional &A) {
    FILE >> A.name >> A.num >> A.stu_num >> A.credit;
    while (A.name.length() < 15) A.name += " ";
    return FILE;
}
void MainWindow::oinput() {
    //课程的读取
    optional1.clear();
    int i = 0, j = 0;
    ifstream file(root + "optional2.txt", ios::in);
    if (!file)
    {
        throw 0;
    }
    while (i < 5) {
        j = 0;
        optional Q;
        file >> Q;
        while (j < Q.stu_num) {
            stu_data P;
            file >> P;
            Q.data.push_back(P);
            j++;
        }
        i++;
        optional1.push_back(Q);
    }
}
istream& operator>>(istream& FILE, teacher &A) {
    FILE >> A.name >> A.num >> A.college >> A.clen>>A.olen;
    return FILE;
}
istream& operator>>(istream& FILE, vector<int> &A) {
    int a;
    FILE >> a;
    A.push_back(a);
    return FILE;
}
void MainWindow::teacherin() {
    //课程的读取
    tea.clear();
    int i = 0, j = 0;
    ifstream file(root + "teacher2.txt", ios::in);
    if (!file)
    {
        throw 0;
    }
    while (i < 5) {
        teacher Q;
        file >> Q;
        for (int j = 0; j < Q.clen; j++) {
            file >> Q.t_compulsory;
        }
        for (int j = 0; j < Q.olen; j++) {
            file >> Q.t_optional;
        }
        tea.push_back(Q);
        i++;
    }
}
istream& operator>>(istream& FILE, student &A) {
    FILE >> A.name >> A.num >> A.college >>A.classnum>> A.olen;
    return FILE;
}
void MainWindow::studentin() {
    //课程的读取
    stu.clear();
    int i = 0, j = 0;
    ifstream file(root + "student2.txt", ios::in);
    if (!file)
    {
        throw 0;
    }
    while (i < 5) {
        student Q;
        file >> Q;
        for (int j = 0; j < Q.olen; j++) {
            file >> Q.s_optional;
        }
        stu.push_back(Q);
        i++;
    }
}
ostream& operator<<(ostream& FILE, compulsory &A) {//重载运算符
    FILE << A.name<< " " << A.num <<" "<< A.stu_num <<" "<< A.credit<<endl;
    return FILE;
}
ostream& operator<<(ostream& FILE, stu_data &A) {
    FILE << A.flag <<" "<< A.name<< " " << A.num<< " " << A.classnum <<" "<< A.college<<" " << A.grade <<" "<< A.gpa<<endl;
    return FILE;
}
void MainWindow::savecom() {
    //课程的保存
    int i = 0, j = 0;
    ofstream file(root + "compulsory2.txt", ios::out);
    if (!file)
    {
        throw 0;
    }
    while (i < 5) {
        j = 0;
        file << compulsory1[i];
        while (j < compulsory1[i].stu_num) {
            file << compulsory1[i].data[j];
            j++;
        }
        i++;
    }
}
ostream& operator<<(ostream& FILE, optional &A) {
    FILE << A.name<< " " << A.num<< " " << A.stu_num<< " " << A.credit<<endl;
    return FILE;
}
void MainWindow::saveopt() {
    //课程的读取
    int i = 0, j = 0;
    ofstream file(root + "optional2.txt", ios::out);
    if (!file)
    {
        throw 0;
    }
    while (i < optional1.size()) {
        j = 0;
        file << optional1[i];
        while (j < optional1[i].data.size()) {
            file << optional1[i].data[j];
            j++;
        }
        i++;
    }
}
ostream& operator<<(ostream& FILE, teacher &A) {
    FILE << A.name<<" "<< A.num <<" "<< A.college<<" "<< A.clen<<" " <<A.olen;
    return FILE;
}
ostream& operator<<(ostream& FILE, vector<int> &A) {
    for (int i = 0; i < A.size(); i++) {
        FILE <<" "<< A[i];
    }
    return FILE;
}
void MainWindow::saveteacher() {
    //课程的读取
    int i = 0, j = 0;
    ofstream file(root + "teacher2.txt", ios::out);
    if (!file)
    {
        cout << "不可以打开文件" << endl;
        exit(1);
    }
    while (i < 5) {
        file << tea[i];
        for (int j = 0; j < tea[i].clen; j++) {
            file << tea[i].t_compulsory;
        }
        for (int j = 0; j < tea[i].olen; j++) {
            file <<tea[i].t_optional;
        }
        file << endl;
        i++;
    }
}
ostream& operator<<(ostream& FILE, student &A) {
    FILE << A.name<<" " << A.num <<" "<< A.college<<" " << A.classnum<<" "<< A.olen;
    return FILE;
}
void MainWindow::savestudent() {
    int i = 0, j = 0;
    ofstream file(root + "student2.txt", ios::out);
    if (!file)
    {
        throw 0;
    }
    while (i < 5) {
        file << stu[i];
        for (int j = 0; j < stu[i].olen; j++) {
            file <<" "<< stu[i].s_optional;
        }
        i++;
        file << endl;
    }

}
