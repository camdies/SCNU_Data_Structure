//         For homework 1.4;
//*****    be care for using GBK coding    *****//
//*****    @author Cairenbin
//*****    Date: 2025.10.1 Wednesday
//1.4线性表(循环链表)找出一最小值并删除
#include <iostream>
using namespace std;

template <class T>
struct CircleLinkNode {
    T data;    //数据域
    CircleLinkNode<T> *link;    //链表指针
    CircleLinkNode(CircleLinkNode<T> *ptr = NULL) {link = ptr;}
    CircleLinkNode(const T& item, CircleLinkNode<T> *ptr = NULL)
        {data = item; link = ptr;}
};    //链表节点类定义结束

//循环链表???
template <class T>
class CircleList {
protected:
    CircleLinkNode<T> *first, *last;
public:
    CircleList()    //空表的last的next应该指向first
        {first = new CircleLinkNode<T>; last = first; last -> link = first;}    //构造函数
    CircleList(const T& x){    //构造函数
        first = new CircleLinkNode<T>();
        last = new CircleLinkNode<T>(x);
        first -> link = last;
        last -> link = first;
    }
    ~CircleList() {makeEmpty();}     //析构函数
    void makeEmpty();    //置空链
    bool isEmpty()    //判空链
        {return first -> link == first ? true : false;}
    int Length() const ;    //计算长度
    bool addNum(T x);    //添加
    bool deleSmallist();    //删除最小值
    void input();    //输入
    void output();    //输出
};  //list类声明结束

template <class T>
void CircleList<T>::makeEmpty() {
    CircleLinkNode<T> *q;
    while(first -> link != first)
    {
        q = first -> link;
        first -> link = q -> link;
        delete q;    //依次摘下first的下一节点并删除
    }
    last = first;  // 重置 last 指针
}   //makEmpty函数结束

template <class T>
int CircleList<T>::Length() const {
    CircleLinkNode<T> *p = first -> link;
    int count = 0;
    while(p != first)
    {
        p = p -> link; count++;
    }
    return count;
}   //Length函数结束

template <class T>
bool CircleList<T>::addNum(T x) {
    CircleLinkNode<T> *p = first;   // p 指向当前节点的前一个节点
    while (p->link != first && p->link->data <= x) {
        p = p->link;         // 找到第一个大于 x 的节点的前一个位置
    }
    // 创建新节点，并插入到 p 和 p->link 之间
    CircleLinkNode<T>* newNode = new CircleLinkNode<T>(x, p->link);
    p->link = newNode;
    // 如果新节点插入在最后，更新 last 指针
    if (newNode->link == first) {    //插入到链尾的情况，last指向链尾节点
        last = newNode;
    }
    return true;
}   //addNum函数结束

template <class T>
bool CircleList<T>::deleSmallist() {
    if(isEmpty()) {
        cout << "循环链表为空, 无法删除!" << endl;
        return false;
    }
    CircleLinkNode<T> *p = first -> link;
    T min = p -> data;
    // 找到最小值
    while(p != first)
    {
        if(p -> data < min)
            min = p -> data;
        p = p -> link;
    }
    // 删除所有等于最小值的节点
    CircleLinkNode<T> *current = first;
    while (current -> link != first) {
        if (current -> link -> data == min) {
            CircleLinkNode<T>* temp = current -> link;
            current -> link = temp -> link;
            if (temp == last) { // 如果删除的是最后一个节点，更新 last 指针
                last = current;
            }
            delete temp;
        } 
        else {
            current = current->link;
        }
    }
    return true;
}   //deleSmallist函数结束

template <class T>
void CircleList<T>::input() {
    int size;
    //cout << "输入循环链表节点个数: ";
    while (true)
    {
        cin >> size;
        if(size == -1) {cout << "程序结束"; exit(0);}
        if(size >= 0) break;
        cout << "节点个数输入有误: ";
    }
    //cout << "输入循环链表节点值: ";
    T value;
    for (int i = 0; i < size; i++) {
        cin >> value;
        addNum(value);
    }
}   //input函数结束

template <class T>
void CircleList<T>::output() {
    CircleLinkNode<T> *p = first -> link;
    if (isEmpty()) {
        cout << "循环链表为空!" << endl;
        return;
    }
    while(p != first)
    {
        cout << p -> data << " ";
        p = p -> link;
    }
    cout << endl;
}   //output函数结束

int main() {
    int i = 0;
    cout << "这个程序实现了第一次作业的第4小题的删除循环列表中最小值的功能" << endl;
    while(1) {
        CircleList<int> list;
        list.input();
        cout << "第" << ++i << "组:" << endl;
        cout << "删除前的循环链表数据: ";
        list.output();
        list.deleSmallist();
        cout << "删除后的循环链表数据: ";
        list.output();
    }
    return 0;
}