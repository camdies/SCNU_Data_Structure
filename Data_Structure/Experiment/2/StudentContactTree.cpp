//********** coding: GBK **********/
//程序名: StudentContact.cpp
/*
*版权信息: 该文件为数据结构实验作业，仅供完成数据结构实验作业以及学习交流使用
* 文件名: StudentContactTree.cpp
* 摘要: 定义学生信息的结构体，单链表节点的存储类以及实验文档要求的函数的声明
* @Version: 2.0
* @author: Cairenbin
* 完成日期: 2025.11.15
*/
#include <iostream>
#include <fstream>
#include "StudentContactTree.h"
using namespace std;

///////////////////////////////////////////////////
//主函数: 学生通讯录管理系统
//函数参数: 无
//参数返回值: int, 返回0表示程序正常结束
//                返回非0表示程序异常结束
int main() {
    BinTree StudentLists;
    while(1) {
        cout << "欢迎使用erchashu管理系统!" << endl;
        cout << "1------ 新建学生通讯录" << endl;
        cout << "2------ 向学生通讯录插入新的学生信息" << endl;
        cout << "3------ 在通讯录中查询学生信息(按学号查询)" << endl;
        cout << "4------ 在通讯录中查询学生信息(按姓名查询)" << endl;
        cout << "5------ 在通讯录中查询学生信息(按电话号码查询)" << endl;
        cout << "6------ 在通讯录中删除学生信息" << endl;
        cout << "7------ 输出年龄最小学生信息" << endl;
        cout << "8------ 找到并输出所有在通讯录中学生地址位置横坐标相同学生信息" << endl;
        cout << "9------ 在屏幕中输出全部学生信息(前序遍历)" << endl;
        cout << "10------ 从文件中读取所有学生通讯录信息" << endl;
        cout << "11------ 向文件写入所有学生通讯录信息" << endl;
        cout << "12------ 退出" << endl;
        int judge;
        cin >> judge;
        switch (judge)
        {
            //////////////////////////////////////////////////////////
            //选项1
            //选项一作用: 建立新学生通讯录(层次化遍历输入学生信息)
            //选项输入: int 要添加学生人数、学生信息
            //选项返回: 无
            case 1:
                {
                    StudentLists.makeEmpty();
                    StudentLists.input();
                    cout << "建立空学生通讯录成功! " << endl;
                }
                break;
            /////////////////////////////////////////////////////////
            //选项2
            //选项二作用: 向通讯录插入学生信息
            //选项输入: 重载Student输入学生信息
            //选项返回: 无
            case 2:
                {
                    cout << "请输入要添加的学生信息" << endl
                         << "(姓名 学号 出生年 月 日 性别 电话 地址名 x坐标 y坐标) :" << endl;
                    cin >> ws;
                    Student newStu;
                    cin >> newStu;
                    if(StudentLists.existsId(newStu.id)) {
                        cout << "不允许相同学号" << newStu.id << "出现!" << endl;
                    } else {
                        BinTreeNode* node = new BinTreeNode(newStu);
                        if (StudentLists.addStudent(node)) {
                            cout << "添加成功! " << endl;
                        } else {
                            delete node;
                            cout << "添加失败!" << endl;
                        }
                    }
                }
                break;
            /////////////////////////////////////////////////////////
            //选项3
            //选项三作用: 按学号查询通讯录中已有学生信息
            //选项输入: string id 学生学号
            //选项返回: 无
            case 3:
                {
                    string idin;
                    cout << "输入要查询的学生学号: ";
                    cin >> idin;
                    if(StudentLists.existsId(idin)) {
                        StudentLists.output(StudentLists.existsId(idin));
                    } else {
                        cout << "未能找到该学号学生!" << endl;
                    }
                }
                break;
            /////////////////////////////////////////////////////////
            //选项4
            //选项四作用: 按姓名查询通讯录中已有学生信息
            //选项输入: string nam 学生姓名
            //选项返回: 无  
            case 4:
                {
                    string nam;
                    cout << "输入要查询的学生姓名: ";
                    cin >> nam;
                    if(StudentLists.existsName(nam)) {
                        StudentLists.output(StudentLists.existsName(nam));
                    } else {
                        cout << "未能找到该姓名学生!" << endl;
                    }
                }
                break;
            /////////////////////////////////////////////////////////
            //选项5
            //选项五作用: 按电话号码查询通讯录中已有学生信息
            //选项输入: string phon 学生电话号码
            //选项返回: 无
            case 5:
                {
                    string phon;
                    cout << "输入要查询的学生电话号码: ";
                    cin >> phon;
                    if(StudentLists.existsPhone(phon)) {
                        StudentLists.output(StudentLists.existsPhone(phon));
                    } else {
                        cout << "未能找到该电话号码学生!" << endl;
                    }
                }
                break;
            /////////////////////////////////////////////////////////
            //选项6
            //选项六作用: 在通讯录中删除学生信息
            //选项输入: int judge 删除学生定位选择
            //          string key 学生信息特征
            //选项返回: 无
            case 6:
                {
                    StudentLists.deleStudent();
                }
                break;
            /////////////////////////////////////////////////////////
            //选项7
            //选项七作用: 输出年龄最小学生信息
            //选项输入: 无
            //选项返回: 无
            case 7:
                {
                    StudentLists.output_smallestStu();
                }
                break;
            /////////////////////////////////////////////////////////
            //选项8
            //选项八作用: 找到并输出所有在通讯录中学生地址位置横坐标相同的学生信息
            //选项输入: double xin 学生横坐标信息
            //选项返回: 无
            case 8:
                {
                    double xin;
                    cout << "输入你要查询的横坐标: ";
                    cin >> xin;
                    StudentLists.output_sameX(xin);
                }
                break;
            /////////////////////////////////////////////////////////
            //选项9
            //选项九作用: 前序遍历输出全部学生信息
            //选项输入: 无
            //选项返回: 无
            case 9:
                {
                    cout << "前序遍历下所有学生信息为:" << endl;
                    StudentLists.output(StudentLists.getRoot(), cout);
                }
                break;
            /////////////////////////////////////////////////////////
            //选项10
            //选项十作用: 学生信息文件读取
            //选项输入: 无
            //选项返回: 无
            case 10:
                {
                    ifstream infile;
                    infile.open("StudentContactTree.txt", ios::in);
                    if(!infile) {
                        cerr << "无法打开文件进行读取!" << endl;
                        break;
                    }
                    infile >> StudentLists;
                    infile.close();
                    cout << "从文件读取学生信息成功!" << endl;
                }
                break;
            /////////////////////////////////////////////////////////
            //选项11
            //选项十一作用: 学生信息文件写入
            //选项输入: 无
            //选项返回: 无
            case 11:
                {
                    ofstream outfile;
                    outfile.open("StudentContactTree.txt", ios::out);
                    if(!outfile) {
                        cerr << "无法打开文件进行写入!" << endl;
                        break;
                    }
                    outfile << StudentLists;
                    outfile.close();
                    cout << "向文件写入学生信息成功!" << endl;
                }
                break;
            /////////////////////////////////////////////////////////
            //选项12
            //选项十二作用: 退出程序
            //选项输入: 无
            //选项返回: 0返回表示程序正常退出
            //         非0返回表示程序错误退出
            case 12:
                {
                    cout << "程序退出!" << endl;
                    return 0;
                }
            //似乎没用？
            default:
                break;
            }
    }
    return 0;
}