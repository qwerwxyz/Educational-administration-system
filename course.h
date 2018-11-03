#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<math.h>
using namespace std;

class stu_data {//课程类中的学生信息
public:
    bool flag;
    string name;
    string num;
    string classnum;
    string college;
    double grade;
    double gpa;
    stu_data(bool flag, string name, string num,string classnum,string college, double grade, double gpa) {//构造函数
        this->flag = flag;
        this->gpa = gpa;
        this->grade = grade;
        this->num = num;
        this->name = name;
        this->classnum = classnum;
        this->college = college;
    }
    stu_data() {

    }
    stu_data(stu_data const &a){//拷贝构造
        flag = a.flag;
        name = a.name;
        num = a.num;
        grade = a.grade;
        gpa = a.gpa;
        classnum = a.classnum;
        college = a.college;
    }
};

/*extern stu_data AA;
extern stu_data BB;
extern stu_data CC;
extern stu_data DD;
extern stu_data EE;*/
class course {//课程的子类
public:
    string name;
    int stu_num;
    string num;
    double credit;
    virtual double getgpa(double a)=0;//虚函数
    vector<stu_data>data;
};

class compulsory: public course {//必修课
public:
    string name;
    int num;
    int stu_num;
    double credit;
    virtual double getgpa(double a) {//实例化
        return (a / 10) * this->credit;
    }
    vector<stu_data>data;//学生库
    //void input();
    compulsory(string name, int num, double credit, int stu_num) {//构造函数
        this->stu_num = stu_num;
        this->name = name;
        this->num = num;
        this->credit = credit;
    }
    compulsory(){}
    compulsory(const compulsory &A) {//拷贝构造
        name = A.name;
        num = A.num;
        stu_num = A.stu_num;
        credit = A.credit;
        data = A.data;
    }
};
class optional : public course {//选修课
public:
    string name;
    int num;
    int stu_num;
    double credit;
    virtual double getgpa(double a) {
        return sqrt(a) / 10 * this->credit;
    }
    optional(string name, int num, double credit, int stu_num) {//构造函数
        this->name = name;
        this->num = num;
        this->credit = credit;
        this->stu_num = stu_num;
    }
    optional(){}
    //virtual void input();
    vector<stu_data>data;//选修课的学生库
    optional(const optional &A) {//拷贝构造
        name = A.name;
        num = A.num;
        stu_num = A.stu_num;
        credit = A.credit;
        data = A.data;
    }
};

extern vector<compulsory>compulsory1;//必修课库
extern vector<optional>optional1;//选修课库

//extern vector<stu_data>stu000;//学生库

/*extern compulsory chinese;
extern compulsory math;
extern compulsory English;
extern compulsory physics;
extern compulsory chemistry;*/

extern void cinput();
extern void oinput();
extern void teacherin();
extern void studentin();
extern void saveteacher();
extern void savestudent();
extern void  savecom();
extern void saveopt();
/*extern optional music;
extern optional art;
extern optional computer;
extern optional PE;
extern optional demo;*/

