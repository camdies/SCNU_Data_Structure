//********** coding: GBK **********/
//程序名: StudentContact.cpp
/*
*版权信息: 该文件为数据结构实验作业，仅供完成数据结构实验作业以及学习交流使用
* 文件名: StudentContact.cpp
* 摘要: 定义学生信息的结构体，单链表节点的存储类以及实验文档要求的函数的声明
* @Version: 1.0
* @author: Cairenbin
* 完成日期: 2025.10.10
*/
#include <iostream>
#include <fstream>
#include "StudentContact.h"
using namespace std;

///////////////////////////////////////////////////
//主函数: 学生通讯录管理系统
//函数参数: 无
//参数返回值: int, 返回0表示程序正常结束
//                返回非0表示程序异常结束
int main() {
    List StudentLists;
    while(1) {
        cout << "欢迎使用ruizhi管理系统!" << endl;
        cout << "1------ 新建学生通讯录" << endl;
        cout << "2------ 向学生通讯录添加新的学生信息" << endl;
        cout << "3------ 向学生通讯录插入新的学生信息（按位置号来描述插入点）" << endl;
        cout << "4------ 在通讯录删除指定学生的信息（按学号操作）" << endl;
        cout << "5------ 为某个学生修改通讯录地址名或地址位置等信息（按学号操作）" << endl;
        cout << "6------ 按学生的学号排序并显示结果" << endl;
        cout << "7------ 在通讯录中查询学生信息（按学生学号来进行查找）" << endl;
        cout << "8------ 在屏幕中输出全部学生信息" << endl;
        cout << "9------ 输出地址位置（坐标）相距最近的两个学生的全部学生信息" << endl;
        cout << "10------ 从文件中读取所有学生通讯录信息" << endl;
        cout << "11------ 向文件写入所有学生通讯录信息" << endl;
        cout << "12------ 退出" << endl;
        int judge;
        cin >> judge;
        switch (judge)
        {
            //////////////////////////////////////////////////////////
            //选项1
            //选项一作用: 建立新学生通讯录
            //选项输入: 无
            //选项返回: 无
            case 1:
                {
                    StudentLists.makeEmpty();
                    cout << "建立空学生通讯录成功! " << endl;
                }
                break;
            /////////////////////////////////////////////////////////
            //选项2
            //选项二作用: 添加一次输入的学生信息
            //选项输入: 重载Student输入学生信息
            //选项返回: 无
            case 2:
                {
                    cout << "请输入要添加的学生信息(姓名 学号 性别 地址 X坐标 Y坐标) :" << endl;
                    cin >> ws;
                    Student stu;
                    cin >> stu;
                    if (StudentLists.existsId(stu.id)) {
                        cout << "添加失败：学号 " << stu.id << " 已存在，已拒绝。" << endl;
                    } else {
                        LinkNode* node = new LinkNode(stu);
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
            //选项三作用: 插入的学生信息
            //选项输入: int posin插入位置号
            //         重载Student输入学生信息
            //选项返回: 无
            case 3:
                {
                    int posin;
                    cout << "请输入要插入的位置号(从1开始计数): ";
                    cin >> posin;
                    cout << "请输入要插入的学生信息(姓名 学号 性别 地址 X坐标 Y坐标) :" << endl;
                    cin >> ws;
                    Student stu;
                    cin >> stu;
                    if (StudentLists.existsId(stu.id)) {
                        cout << "插入失败：学号 " << stu.id << " 已存在，已拒绝。" << endl;
                    } else {
                        LinkNode* node = new LinkNode(stu);
                        if(StudentLists.addStuInfo(node, posin)) {
                            cout << "插入成功! " << endl;
                        } else {
                            cout << "插入位置无效, 插入失败! " << endl;
                            delete node;
                        }
                    }
                }
                break;
            /////////////////////////////////////////////////////////
            //选项4
            //选项四作用: 删除的学生信息
            //选项输入: int iddele学生学号
            //选项返回: 无  
            case 4:
                {
                    string iddele;
                    cout << "输入要删除的学生学号: ";
                    cin >> iddele;
                    if(StudentLists.deleStudent(iddele)) {
                        cout << "删除成功!" << endl;
                    } else {
                        cout << "未能找到该学号学生, 删除失败!" << endl;
                    }
                }
                break;
            /////////////////////////////////////////////////////////
            //选项5
            //选项五作用: 输入的学生学号、输入学生信息并修改学生信息
            //选项输入: int idaddr要修改的学生学号
            //         重载Student输入学生信息
            //选项返回: 无
            case 5:
                {
                    string idaddr;
                    cout << "请输入要修改信息的学生学号: ";
                    cin >> idaddr;
                    // 先检查是否存在，若不存在直接取消修改并提示
                    if (!StudentLists.existsId(idaddr)) {
                        cout << "未找到该学号，修改已取消。" << endl;
                    } else {
                        // 显示当前信息
                        StudentLists.search_output(idaddr);
                        // 只修改地址名和地址位置（按要求）
                        cout << "输入修改后的地址名和地址坐标(地址 X坐标 Y坐标): ";
                        Student stuin;
                        cin >> ws;
                        cin >> stuin.address >> stuin.x >> stuin.y;
                        if (StudentLists.modifyStudent(idaddr, stuin)) {
                            cout << "修改成功!" << endl;
                        } else {
                            cout << "修改失败!" << endl;
                        }
                    }
                }
                break;
            /////////////////////////////////////////////////////////
            //选项6
            //选项六作用: 排序输出学生信息
            //选项输入: 无
            //选项返回: 无
            case 6:
                {
                    StudentLists.sort();
                    cout << "排序后所有学生信息: " << endl;
                    StudentLists.output();
                }
                break;
            /////////////////////////////////////////////////////////
            //选项7
            //选项七作用: 输入学生信息查询徐盛
            //选项输入: int idsearch输入查询学号
            //选项返回: 无
            case 7:
                {
                    string idsearch;
                    cout << "输入你要查询的学生学号: ";
                    cin >> idsearch;
                    StudentLists.search_output(idsearch);
                }
                break;
            /////////////////////////////////////////////////////////
            //选项8
            //选项八作用: 输出全部的学生信息
            //选项输入: 无
            //选项返回: 无
            case 8:
                {
                    cout << "所有学生信息如下: " << endl;
                    StudentLists.output();
                }
                break;
            /////////////////////////////////////////////////////////
            //选项9
            //选项九作用: 输出最近的学生信息
            //选项输入: 无
            //选项返回: 无
            case 9:
                {
                    StudentLists.output_closest();
                }
                break;
            /////////////////////////////////////////////////////////
            //选项10
            //选项十作用: 学生信息文件读取
            //选项输入: 无
            //选项返回: 无
            case 10:
                {
                    if(StudentLists.loadFromBinFile("StudentContact.dat")) {
                        cout << "二进制读取成功!" << endl;
                    } else {
                        cout << "二进制读取失败!" << endl;
                    }
                }
                break;
            /////////////////////////////////////////////////////////
            //选项11
            //选项十一作用: 学生信息文件写入
            //选项输入: 无
            //选项返回: 无
            case 11:
                {
                    if(StudentLists.saveToBinFile("StudentContact.dat")) {
                        cout << "二进制写入成功!" << endl;
                    } else {
                        cout << "二进制写入失败!" << endl;
                    }
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