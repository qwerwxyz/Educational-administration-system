#pragma once
#include<iostream>
#include<string>
#include<vector>
#include"course.h"
using namespace std;
#include <QString>
class coursedata {
public:
        string name;
        int num;
        double grade;
        double gpa;
        coursedata(string name, int num, double grade, double gpa) {
                this->name = name;
                this->grade = grade;
                this->gpa = gpa;
                this->num = num;
        }
        coursedata(const coursedata &A) {
                this->name = A.name;
                this->grade = A.grade;
                this->gpa = A.gpa;
                this->num = A.num;
        }
};
class student {
public:
        string num;
        string name;
        string college;
        string classnum;
        int clen;
        int olen;
        student(string num, string name, string college, string classnum, vector<int>opt) {//构造函数
                this->name = name;
                this->num = num;
                this->college = college;
                this->classnum = classnum;
                this->s_compulsory = { compulsory1[0].num,compulsory1[1].num,compulsory1[2].num,compulsory1[3].num,compulsory1[4].num };
                this->s_optional = opt;
        }
        student() {
                s_compulsory = { 0,1,2,3,4 };
        }
        //void getccourse();//获得必修课成绩
        //void getocourse();//获得选修课成绩
        void getcoursegrade(vector<compulsory> &compulsory1, vector<optional> &optional1);

        bool choose(optional &A, vector<student> &stu);
        bool del(optional &A, vector<student> &stu);
        void del_course();//删除课程
        void del(optional &A);
        void show_course();//显示全校课程
        void show_own_course();//显示自身课程
        QString showallgrade(int a, vector<compulsory> &compulsory1, vector<optional> &optional1);//显示所有成绩
        //void sort(vector<int>a, vector<int>b);
        void for_student();//主菜单
        vector<int>s_compulsory;//学生的必修课
        vector<int>s_optional;//学生的选修课
        vector<coursedata>coursedata1;
};

/*extern student stu01;
extern student stu02;
extern student stu03;
extern student stu04;
extern student stu05;*/
extern vector<student>stu;
