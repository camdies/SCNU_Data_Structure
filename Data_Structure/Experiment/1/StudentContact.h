//********** coding: GBK **********/
//程序名: StudentContact.h
/*
*版权信息: 该文件为数据结构实验作业，仅供完成数据结构实验作业以及学习交流使用
* 文件名: StudentContact.h
* 摘要: 定义学生信息的结构体，单链表节点的存储类以及实验文档要求的函数的声明
* @Version: 1.0
* @author: Cairenbin
* 完成日期: 2025.10.10
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

///////////////////////////////////////////////////
/********************************* 结构体Student类定义 *********************************/
//存储学生信息
struct Student {
    char name[32];      // 姓名
    char id[20];        // 学号
    char sex[8];        // 性别
    char address[64];   // 地址
	double x;    //地址x轴坐标
	double y;    //地址y轴坐标
	//double z;		//地址z轴坐标，应该不会使用这么多？
};    //学生信息结构体定义结束

///////////////////////////////////////////////////
/********************************** 单链表节点结构体定义 **********************************/
//存储学生信息的链表节点
struct LinkNode {
	Student data;    //学生信息数据域
	LinkNode* link;    //链表指针
	LinkNode(LinkNode* ptr = NULL) { link = ptr; }
	LinkNode(const Student& stu, LinkNode* ptr = NULL)
	{
		data = stu; link = ptr;
	}
};    //链表节点结构体定义结束

///////////////////////////////////////////////////
/********************************** 单链表类定义 **********************************/
//实现学生通讯录的各种操作
class List {
protected:
	LinkNode* first;    //链表节点的头指针，使用附加头结点的方式实现
public:
	List() { first = new LinkNode; }    //构造函数
	List(const Student& x) {    //构造函数
		first = new LinkNode();    //建立附加头结点
		first->link = new LinkNode(x);    //头结点下一个开始建立数据节点
	}
	~List() { makeEmpty(); }    //析构函数
	void makeEmpty();    //将链表置空
	bool isEmpty() {    //判断链表是否为空
		return first->link == NULL ? true : false;
	}
	int Amount() const;    //学生人数计算
	bool existsId(const string& id) const;// 新增：判断学号是否存在（声明处或适当位置）
	bool addStudent(LinkNode * p);    //添加学生
	bool addStuInfo(LinkNode* p, int pos);	//按位置号向通讯录插入新学生信息
	bool deleStudent(string id);    //删除学生
	bool modifyStudent(const string& id, const Student& newStu);	//修改学生信息
	void sort();	//按照id排序
	void input();    //输入
	void search_output(string id/*, LinkNode *t*/);    //查找输出单个学生信息
	void output();	  //输出
	void output_closest();		//输出地址最近两个学生全部信息
	friend istream& operator>>(istream& in, Student& stu);	//学生信息文件读写_输入
	friend ostream& operator<<(ostream& out, const Student& stu);	//学生信息文件读写_输出
	friend istream& operator>>(istream& in, List& list);	//链表整体信息文件读写_输入
	friend ostream& operator<<(ostream& out, const List& list);		//链表整体文件读写_输出
    bool saveToBinFile(const char* filename) const;
    bool loadFromBinFile(const char* filename);
};

/////////////////////////////////////////////////
//函数功能：单链表类成员函数实现
//将链表置空
void List::makeEmpty() {
    LinkNode *q;
    while (first -> link != NULL)
    {
        q = first -> link;
        first -> link = q -> link;
        delete q;    //依次摘下first的下一节点并删除
    }
	//这个删除函数会保留根节点first
}   //makEmpty函数结束

/////////////////////////////////////////////////
//函数功能：计算学生人数
//函数参数：无
//参数返回值：学生人数int
int List::Amount() const {
    LinkNode *p = first -> link;
    int count = 0;
    while (p != NULL)
    {
        p = p -> link; count++;
    }
    return count;
}	//Amount const函数结束

bool List::existsId(const string& id) const {
    LinkNode* p = first->link;
    while (p) {
        if (strcmp(p->data.id, id.c_str()) == 0) return true;
        p = p->link;
    }
    return false;
}

///////////////////////////////////////////////////
//函数功能：添加学生信息到链表尾部
//函数参数：LinkNode* newstu，指向新学生节点的指针
//参数返回值：bool，添加成功返回true，失败返回false
bool List::addStudent(LinkNode *newstu) {
	if(!newstu) return false;	//newstu为空指针则返回false
	if (existsId(newstu->data.id)) {
        // 拒绝重复，调用方负责 delete newstu（若需要）
        return false;
    }
    LinkNode *p = first;   // p 指向当前节点的前一个节点
	while(p->link != NULL) p = p->link;
	p->link = newstu;
	newstu->link = NULL;
	return true;
}    //addStudent函数结束

///////////////////////////////////////////////////
//函数功能：按位置号向通讯录插入新学生信息
//函数参数：LinkNode* p，指向新学生节点的指针
//         int pos，插入位置号
//参数返回值：bool，插入成功返回true，失败返回false
bool List::addStuInfo(LinkNode* newNode, int pos) {
    if (!newNode || pos < 1) return false;
	if (existsId(newNode->data.id)) {
        return false;
    }
    LinkNode* cur = first; // 前驱指针，从头结点开始
    int i = 1;
    // 移动到第 pos-1 个数据节点（即插入位置的前驱），但不要越过尾部
    while (i < pos && cur->link != NULL) {
        cur = cur->link;
        ++i;
    }
    // 插入
    newNode->link = cur->link;
    cur->link = newNode;
    return true;
	/*
	if(!p || pos < 0) return false;
    LinkNode* cur = first;
    int idx = 0;
    while (cur != NULL && idx < pos) {	//位移到pos位置
        cur = cur->link;
        idx++;
    }
    if (!cur) return false;		//cur越界
    p->link = cur->link;
    cur->link = p;
    return true;
	*/
}	//addStuInfo函数结束

///////////////////////////////////////////////////
//函数功能：按学号删除指定学生
//函数参数：string id，表示学生学号
//参数返回值：bool，删除成功返回true，失败返回false
bool List::deleStudent(string id) {
	LinkNode *p = first;
	while(p->link != NULL) {
		if(strcmp(p->link->data.id, id.c_str()) == 0) {	//查找数据域里面id是否符合
			LinkNode *q = p -> link;
			p -> link = q->link;
			delete q;
			return true;	//删除成功
		}
		p = p->link;
	}
	return false;	//删除失败
}	//deleStudent函数结束

///////////////////////////////////////////////////
//函数功能: 按学号查找修改学生信息
//
//
bool List::modifyStudent(const string& id, const Student& newStu) {
    LinkNode *p = first->link;
    while(p != NULL) {
        if(strcmp(p->data.id, id.c_str()) == 0) {
            strcpy(p->data.address, newStu.address); // 修正
            p->data.x = newStu.x;
            p->data.y = newStu.y;
            return true;	//修改成功
        }
        p = p->link;
    }
    return false;
}
///////////////////////////////////////////////////
//函数功能：按学号排序
//函数参数：无
//参数返回值：无
void List::sort() {
    if (isEmpty()) return;	//链表为空则直接返回
    for (LinkNode* i = first->link; i != NULL; i = i->link) {
        for (LinkNode* j = i->link; j != NULL; j = j->link) {
            if (strcmp(i->data.id, j->data.id) > 0) {
                swap(i->data, j->data);
            }
        }
    }
}	//sort函数结束

///////////////////////////////////////////////////
//函数功能：输入学生信息
//函数参数：无；
//参数返回值：无；
void List::input() {
    int n;
    cout << "请输入学生人数: ";
    cin >> n;
    cin.ignore(); // 清除换行符
    if(n <= 0) return;
    makeEmpty();
    for (int i = 0; i < n; ++i) {
        Student stu;
        cout << "输入第" << i + 1 << "个学生信息(姓名 学号 性别 地址 x y):\n";
        cin.getline(stu.name, 32);
        cin.getline(stu.id, 20);
        cin.getline(stu.sex, 8);
        cin.getline(stu.address, 64);
        cin >> stu.x >> stu.y;
        cin.ignore(); // 清除换行符
        addStudent(new LinkNode(stu));
    }
}	//input函数结束

///////////////////////////////////////////////////
//函数功能：查找对应学生id并输出其信息
//函数参数：string id，表示学生学号
//参数返回值：无
void List::search_output(string id/*, LinkNode *t */){
    LinkNode* p = first->link;
    while (p) {
        if (p->data.id == id) {
            cout << "姓名: " << p->data.name << endl;
            cout << "学号: " << p->data.id << endl;
            cout << "性别: " << p->data.sex << endl;
            cout << "地址: " << p->data.address << endl;
            cout << "X坐标: " << p->data.x << ", Y坐标: " << p->data.y << endl;
            return;
        }
        p = p->link;
    }
    cout << "未找到该学生信息!" << endl;
	/*
	LinkNode *search = first->link;
	while(search->link != NULL) {
		search = search->link;		//while循环不停往后遍历
		if(search->data.id == id) break;	//找到对应id则跳出循环
	}
	if(search->data.id == id) {	//处理找到id后break跳出循环的情况
		cout << "姓名: " << search->data.name << endl;
		cout << "学号: " << search->data.id << endl;
		cout << "性别: " << search->data.sex << endl;
		cout << "地址: " << search->data.address << endl;
		cout << "X坐标: " << search->data.x << ", Y坐标: " << search->data.y << endl;
	}
	else {	//处理while循环结束未找到id的情况
		cout << "未找到该学生信息!" << endl;
	}
	*/
}	//output(string id)函数结束

////////////////////////////////////////////////////
//函数功能：输出所有学生信息
//函数参数：无
//参数返回值：无
void List::output() {
	int i = 0;
    LinkNode *p = first -> link;
    if (p == NULL)
    {
        cout << "链表为空!" << endl;
        return;
    }
    //cout << "链表节点值为: ";
    while (p != NULL)
    {
		cout << "第" << ++i << "个学生:" << endl;
		cout << "姓名: " << p->data.name << endl;
		cout << "学号: " << p->data.id << endl;
		cout << "性别: " << p->data.sex << endl;
		cout << "地址: " << p->data.address << endl;
		cout << "X坐标: " << p->data.x << ", Y坐标: " << p->data.y << endl;
		p = p->link;	//继续遍历下一个节点
    }
    cout << endl;
}   //output函数结束

////////////////////////////////////////////////////
//函数功能：输出地址最近两个学生全部信息
//函数参数：无
//参数返回值：无
void List::output_closest() {
    LinkNode* head = first->link;
    if (!head || !head->link) {
        cout << "学生数量不足！至少需要两名学生。" << endl;
        return;
    }
    LinkNode* a = nullptr;
    LinkNode* b = nullptr;
    double minDist = 1e300;
    for (LinkNode* i = head; i != NULL; i = i->link) {
        for (LinkNode* j = i->link; j != NULL; j = j->link) {
            double dx = i->data.x - j->data.x;
            double dy = i->data.y - j->data.y;
            double dist = sqrt(dx*dx + dy*dy);
            if (dist < minDist) {
                minDist = dist;
                a = i; b = j;
            }
        }
    }
    if (a && b) {
        cout << "最近的两个学生信息如下：" << endl;
        cout << "学生1：姓名: " << a->data.name << ", 学号: " << a->data.id << ", 地址: " << a->data.address << ", 坐标: (" << a->data.x << "," << a->data.y << ")" << endl;
        cout << "学生2：姓名: " << b->data.name << ", 学号: " << b->data.id << ", 地址: " << b->data.address << ", 坐标: (" << b->data.x << "," << b->data.y << ")" << endl;
        cout << "距离: " << minDist << endl;
    } else {
        cout << "学生数量不足！" << endl;
    }
	/*
	if(first->link == NULL || first->link->link == NULL) {
		cout << "学生数量不足, 至少为2!" << endl;
		return;
	}
	LinkNode *stu1 = nullptr;
	LinkNode *stu2 = nullptr;
	double minDistance = 1000000;
	for (LinkNode *i = first->link; i != NULL; i = i->link)
	{
		for(LinkNode *j = i->link; j != NULL; j = j->link) {
			double dx = i->data.x - j->data.x;
			double dy = i->data.y - j->data.y;
			double distance = sqrt(dx * dx + dy * dy);
			if(distance < minDistance) {
				minDistance = distance;
				stu1 = i; stu2 = j;
			}
		}
	}
	if(stu1 != NULL && stu2 != NULL) {
		cout << "距离最近的两个学生信息如下:" << endl;
		cout << "学生1:" << endl;
		search_output(stu1->data.id);
		cout << "学生2:" << endl;
		search_output(stu2->data.id);
	} else {
		cout << "学生数量不足2!" << endl;
	}
	*/
}	//output_closest函数结束

/*************** 单个学生信息输入输出流重载 ******************/
/////////////////////////////////////////////////
//函数功能：学生信息文件读写_输入
//函数参数：istream& in，输入流引用
//         Student& stu，学生信息结构体引用
//参数返回值：istream&，输入流引用
istream& operator>>(istream& in, Student& stu) {
    in.getline(stu.name, 32);
    in.getline(stu.id, 20);
    in.getline(stu.sex, 8);
    in.getline(stu.address, 64);
    in >> stu.x >> stu.y;
    in.ignore();
    return in;
}	//学生输入重载结束

///////////////////////////////////////////////
//函数功能：学生信息文件读写_输出
//函数参数：ostream& out，输出流引用
//         const Student& stu，学生信息结构体常引用
//参数返回值：ostream&，输出流引用
ostream& operator<<(ostream& out, const Student& stu) {
    out << stu.name << "\n" << stu.id << "\n" << stu.sex << "\n"
        << stu.address << "\n" << stu.x << " " << stu.y << "\n";
    return out;
}	//学生输出重载结束

/***************** 单链表整体输入输出流重载 ******************/
/////////////////////////////////////////////////
//函数功能：链表整体信息文件读写_输入
//函数参数：istream& in，输入流引用
//         List& list，单链表类引用
//参数返回值：istream&，输入流引用
istream& operator>>(istream& in, List& list) {
    list.makeEmpty();
    Student stu;
    while (in >> stu) {
		if (list.existsId(stu.id)) {
            // 跳过重复记录
            continue;
        }
        LinkNode* node = new LinkNode(stu);
        list.addStudent(node);
		if (!list.addStudent(node)) { // 若 addStudent 失败（理论上已被 existsId 拦截）
            delete node;
        }
    }
    return in;
}	//链表输入重载结束

/////////////////////////////////////////////////
//函数功能：链表整体信息文件读写_输出
//函数参数：ostream& out，输出流引用
//         const List& list，单链表类常引用
//参数返回值：ostream&，输出流引用
ostream& operator<<(ostream& out, const List& list) {
    LinkNode* p = list.first->link;
    while (p != NULL) {
        out << p->data << endl;
        p = p->link;
    }
    return out;
}	//链表输出重载结束

bool List::saveToBinFile(const char* filename) const {
    ofstream fout(filename, ios::binary);
    if (!fout) return false;
    LinkNode* p = first->link;
    while (p) {
        fout.write(reinterpret_cast<const char*>(&p->data), sizeof(Student));
        p = p->link;
    }
    fout.close();
    return true;
}

bool List::loadFromBinFile(const char* filename) {
    ifstream fin(filename, ios::binary);
    if (!fin) return false;
    makeEmpty();
    Student stu;
    while (fin.read(reinterpret_cast<char*>(&stu), sizeof(Student))) {
        addStudent(new LinkNode(stu));
    }
    fin.close();
    return true;
}