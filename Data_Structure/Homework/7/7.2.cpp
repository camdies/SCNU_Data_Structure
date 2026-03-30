//         For homework 7.2
//*****    be care for using GBK coding    *****//
//*****    @author Cairenbin
//*****    Date: 2025.11.25 Tuesday
//7.2.分别用快速排序递归算法和非递归算法进行排序功能, 0结束数据输入, -1结束程序运行
//    不同行分别输出快速递归/快速非递归排序前后的序列
#include <iostream>
#include "stack"
using namespace std;

struct LinkNode {
    int data;
    LinkNode* link;
    LinkNode(LinkNode* ptr = nullptr) : link(ptr) {}
    LinkNode(int value, LinkNode* ptr = nullptr): data(value), link(ptr) {}
};

class List {
protected:
    LinkNode* first;
public:
    List() { //构造函数
        first = new LinkNode();
    };

    List(const int& x) { //附加头结点建立链表构造函数
        first = new LinkNode();
        first->link = new LinkNode(x);
    };

    List(const List& other) {
        first = new LinkNode();
        LinkNode* src = other.first->link;
        LinkNode* dst = first;
        while(src) {
            dst->link = new LinkNode(src->data);
            dst = dst->link;
            src = src->link;
        }
    }

    ~List() {makeEmpty();}

    bool isEmpty() {
        return first->link == nullptr ? true : false;
    };

    void makeEmpty(); //清空链表
    int Length(); //链表长度计算
    bool addNum(int x);
    void input();
    void output();
    LinkNode* Partition(LinkNode* low, LinkNode* high);
    void QuickSort_recursive(LinkNode* low, LinkNode* high);
    void Quicksort(); //快速排序递归入口
    void Quicksort_non_recursive();
    List& operator=(const List& other) {
        if(this == &other) return *this;
        makeEmpty();
        LinkNode* src = other.first->link;
        LinkNode* dst = first;
        while(src) {
            dst->link = new LinkNode(src->data);
            dst = dst->link;
            src = src->link;
        }
        return *this;
    }
};

void List::makeEmpty() {
    LinkNode* q;
    while(first->link) {
        q = first->link;
        first->link = q->link;
        delete q; //依次摘下first节点后面第一个节点删除
    }
};

int List::Length() {
    LinkNode* p = first->link;
    int count = 0; //节点个数计数
    while(p) {
        p = p->link;
        count++;
    }
    return count;
};

bool List::addNum(int x) {
    LinkNode* p = first;
    while(p->link) {
        p = p->link; //找到末尾位置插入
    }
    LinkNode* newNode = new LinkNode(x, p->link);
    if(!newNode) return false;
    p->link = newNode;
    return true;
};

void List::input() {
// filepath: d:\C++\Grade 2.1\Data Structure\Homework\7\7.1.cpp
    int number;
    LinkNode* tail = first;
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
}

void List::output() {
    LinkNode* p = first->link;
    if(!p) {
        cout << "链表为空!" << endl;
        return;
    }
    while(p) {
        cout << p->data << " ";
        p =p->link;
    }
    cout << endl;
};

LinkNode* List::Partition(LinkNode* low, LinkNode* high) {
    int pivot = low->data;
    LinkNode* p = low; //p指向小于基准节点的最后一个节点
    LinkNode* q = low->link; //q用于遍历节点
    while(q != high->link) { //遍历到high节点
        if(q->data < pivot) {
            p = p->link;
            swap(p->data, q->data); //交换数据域
        }
        q = q->link;
    }
    swap(low->data, p->data);
    return p;
};

void List::QuickSort_recursive(LinkNode* low, LinkNode* high) {
    if(low != high) {
        LinkNode* pivot = Partition(low, high);
        if(pivot != low) { //基准节点左侧子表非空
            QuickSort_recursive(low, pivot); //递归排序基准节点左侧子表
        }
        if(pivot != high) { //基准节点右侧子表非空
            QuickSort_recursive(pivot->link, high);
        }
    }
};

//快速排序递归算法实现
void List::Quicksort() {
    if(isEmpty()) {
        cout << "链表为空!" << endl;
        return;
    }
    LinkNode* high = first->link;
    while(high && high->link) high = high->link; //high指向链表尾节点
    QuickSort_recursive(first->link, high);
};

//快速排序非递归算法实现
void List::Quicksort_non_recursive() {
    if(isEmpty()) {
        cout << "链表为空!" << endl;
        return;
    }
    LinkNode* high = first->link; //用来存储链表尾部节点
    while(high && high->link) { high = high->link; } //找到链表尾节点
    stack<pair<LinkNode*, LinkNode*>> s; //栈中存储待排序子表的起止节点指针对
    s.push(make_pair(first->link, high)); //初始时入栈整个链表
    while(!s.empty()) {
        pair<LinkNode*, LinkNode*> range = s.top(); //取栈顶元素
        s.pop();
        LinkNode* low = range.first;
        LinkNode* high = range.second;
        if(low != high) {
            LinkNode* pivot = Partition(low, high);
            if(pivot != low) { //基准节点左侧子表非空
                s.push(make_pair(low, pivot)); //基准节点左侧子表入栈
            }
            if(pivot != high) { //基准节点右侧子表非空
                s.push(make_pair(pivot->link, high)); //基准节点右侧子表入栈
            }
        }
    }
};

int main() {
    int i = 0;
    while(true) {
        List MyList1, MyList2;
        cout << "第" << ++i << "次" << endl;
        cout << "请输入需要排序的整数序列(以0结束输入, -1结束程序):" << endl;
        MyList1.input();
        MyList2 = MyList1;
        cout << "快速排序递归算法排序前序列为:" << endl;
        MyList1.output();
        MyList1.Quicksort();
        cout << "快速排序递归算法排序后序列为:" << endl;
        MyList1.output();
        cout << endl;
        cout << "快速排序非递归算法排序前序列为:" << endl;
        MyList2.output();
        MyList2.Quicksort_non_recursive();
        cout << "快速排序非递归算法排序后序列为:" << endl;
        MyList2.output();
        cout << endl;
    }
    return 0;
}