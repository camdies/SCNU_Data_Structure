//         For homework 7.1
//*****    be care for using GBK coding    *****//
//*****    @author Cairenbin
//*****    Date: 2025.11.25 Tuesday
//7.1.递归冒泡排序实现单链表排序功能, 0结束单链表输入, -1结束程序运行
//    不同行分别输出递归冒泡排序前后的序列
#include <iostream>
using namespace std;

struct LinkNode {
    int data;
    LinkNode* link;
    LinkNode(LinkNode* ptr = nullptr) {link =ptr;}
    LinkNode(const int& item, LinkNode* ptr = nullptr)
        {data = item; link = ptr;}
}; //LinkNode 单链表节点类定义结束

class List {
protected:
    LinkNode* first; //链表头指针
public:
    List() {first = new LinkNode();} //构造函数
    List(const int& x) { //附加头结点建立链表构造函数
        first = new LinkNode();
        first->link = new LinkNode(x);
    }
    ~List() {makeEmpty();} //析构函数
    void makeEmpty() {
        LinkNode* q;
        while(first->link) {
            q = first->link;
            first->link = q->link;
            delete q; //依次摘下first节点后面第一个节点删除
        }
    }
    bool isEmpty() //判空链表
        {return first->link == nullptr ? true : false;}
    int Length(); //链表长度计算
    bool addNum(int x);
    void input(); //输入创建链表
    void output(); //输出链表
    void bubble(LinkNode* curr, int n); //链表冒泡辅助
    void BubbleShort(); //链表递归冒泡排序
}; //List 类声明结束

int List::Length() {
    LinkNode* p = first->link;
    int count = 0; //节点个数
    while(p) {
        p = p->link;
        count++;
    }
    return count;
}; //int List::Length 函数结束

bool List::addNum(int x) {
    LinkNode* t = first;
    while(t->link) {
        t = t->link; //找到末尾位置插入
    }
    LinkNode* newNode = new LinkNode(x, t->link);
    if(newNode == nullptr) return false;
    t->link =newNode;
    return true; //节点尾插入成功
}; //bool List::addNum 函数结束

void List::input() {
// filepath: d:\C++\Grade 2.1\Data Structure\Homework\7\7.1.cpp
    int number;
    LinkNode* tail = first; //tail指向链表尾节点
    while(cin >> number) {
        if(number == -1) {
            cout << "程序结束!" << endl;
            exit(0);
        }
        if(number == 0) break; //最后一个0作为结束标志，不插入
        //插入数据（包括0，只要不是最后一个0）
        LinkNode* newNode = new LinkNode(number);
        tail->link = newNode;
        tail = newNode;
    }
}; //void List::input 函数结束

void List::output() {
    LinkNode* p = first->link;
    if(!p) {
        cout << "链表为空!" << endl;
        return;
    }
    while(p) {
        cout << p->data << " ";
        p = p->link;
    }
    cout << endl;
}; //void List::output 函数结束

void List::bubble(LinkNode* curr, int n) {
    if(n <= 1) return;
    LinkNode* p = curr->link;
    for (int i = 0; i < n - 1; i++)
    {
        if(p && p->link && p->data > p->link->data) { //先行判断p以及p->link非空, 避免出现访问空指针问题
            int temp = p->data;
            p->data = p->link->data;
            p->link->data = temp;
        }
        p = p->link;
    }
    bubble(curr, n - 1);
}; //void List::bubble 函数结束

void List::BubbleShort() {
    bubble(first, Length());
}; //void List::BubbleShort 函数结束

int main() {
    int i = 0;
    while(true) {
        List MyList;
        cout << "第" << ++i << "次" << endl;
        cout << "请输入单链表元素(0结束输入, -1结束程序): ";
        MyList.input();
        cout << "排序前链表序列: ";
        MyList.output();
        cout << "排序后链表序列: ";
        if(MyList.isEmpty()) {cout << "链表为空, 默认有序" << endl;}
        else {
            MyList.BubbleShort();
            MyList.output();
        }
        cout << endl;
    }
    return 0;
}