#pragma once
#include<iostream>
#include<string>
#include<vector>
#include"course.h"
using namespace std;
class teacher {
public:
    string name;
    string college;
    string num;
    teacher(string num, string name, string college, vector<int>com,vector<int>opt) {//构造函数
        this->name = name;
        this->num = num;
        this->college = college;
        this->t_compulsory = com;
        this->t_optional = opt;
    }
    teacher() {
    }
    teacher(const teacher &A) {//拷贝构造
        name = A.name;
        college = A.college;
        num = A.num;
        t_compulsory =A.t_compulsory;
        t_optional = A.t_optional;
        clen = A.clen;
        olen = A.olen;
    }
    int clen;
    int olen;
    vector<int>t_compulsory;//老师的必修课
    vector<int>t_optional;//老师的选修课
    void show_course();//显示课程
    void show_own_course();//显示自身课程
    void show_stu();//显示学生名单
    void hand_in_grade();//提交成绩
    void hand_in_c(vector<int>A);
    void hand_in_o(vector<int>A);
    void put_in_grade();//输入成绩
    void put_in_c(vector<int>A);
    void put_in_o(vector<int>A);
    //bool comparenum1(const stu_data &a,const stu_data &b);//对学号进行排序
    //static bool comparenum2(const stu_data &a,const stu_data &b);
    void for_teacher();//主菜单
    //void show_stu_grade(vector<int>A,vector<int>B);
    void show_stu_data();
};

/*extern teacher tea01;
extern teacher tea02;
extern teacher tea03;
extern teacher tea04;
extern teacher tea05;*/
extern vector<teacher>tea;//老师名单
