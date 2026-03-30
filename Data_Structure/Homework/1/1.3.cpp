//         For homework 1.3;
//*****    be care for using GBK coding    *****//
//*****    @author Cairenbin
//*****    Date: 2025.10.1 Wednesday
//1.3有序线性表(单链表)插入一元素同时保持有序性
#include <iostream>
using namespace std;

template <class T>
struct LinkNode {
    T data;    //数据域
    LinkNode<T> *link;    //链表指针
    LinkNode(LinkNode<T> *ptr = NULL) {link = ptr;}
    LinkNode(const T& item, LinkNode<T> *ptr = NULL)
        {data = item; link = ptr;}
};    //链表节点类定义结束

template <class T>
class List {
protected:
    LinkNode<T> *first;    //链表头指针
public:
    List() {first = new LinkNode<T>();}    //构造函数
    List(const T& x) {
        first = new LinkNode<T>();
        first -> link = new LinkNode<T>(x);
    }   //构造函数
    ~List() {makeEmpty();}    //析构函数
    void makeEmpty();   //置空表
    bool isEmpty() const    //判空表
        {return first -> link == NULL ? true: false;}
    int Length() const;    //长度计算
    bool addNum(T x);    //添加
    void input();    //输入
    void output();    //输出
};  //List类声明结束

template <class T>
void List<T>::makeEmpty() {
    LinkNode<T> *q;
    while (first -> link != NULL)
    {
        q = first -> link;
        first -> link = q -> link;
        delete q;    //依次摘下first的下一节点并删除
    }
}   //makEmpty函数结束

template <class T>
int List<T>::Length() const {
    LinkNode<T> *p = first -> link;
    int count = 0;
    while (p != NULL)
    {
        p = p -> link; count++;
    }
    return count;
}

template <class T>
bool List<T>::addNum(T x) {
    LinkNode<T> *p = first;   // p 指向当前节点的前一个节点
    while (p->link != NULL && p->link->data <= x) {
        p = p->link;         // 找到第一个大于 x 的节点的前一个位置
    }
    // 创建新节点，并插入到 p 和 p->link 之间
    LinkNode<T> *newNode = new LinkNode<T>(x, p->link);
    if (newNode == NULL) return false; // 内存分配失败
    p->link = newNode;
    return true;
}    //addNum函数结束

template <class T>
void List<T>::input() {
    int size;
    //cout << "输入链表节点个数: ";
    while(true) {
        cin >> size;
        if(size == -1) {cout << "程序结束"; exit(0);}
        if(size >= 0) break;
        cout << "节点个数输入有误: ";
    }
    //cout << "输入链表节点值: ";
    T value;
    for (int i = 0; i < size; i++) {
        cin >> value;
        addNum(value);
    }
}    //input函数结束

template <class T>
void List<T>::output() {
    LinkNode<T> *p = first -> link;
    if (p == NULL)
    {
        cout << "链表为空!" << endl;
        return;
    }
    //cout << "链表节点值为: ";
    while (p != NULL)
    {
        cout << p -> data << " ";
        p = p -> link;
    }
    cout << endl;
}   //output函数结束

int main() {
    int i = 0;
    cout << "这个程序实现了第一次作业的第3小题的在有序单链表中插入1个元素并保持链表有序的功能" << endl;
    while(1){
        List<int> list;
        list.input();
        int x;
        cin >> x;
        cout << "第" << ++i << "组:" << endl;
        cout << "插入前的链表数据: ";
        list.output();
        list.addNum(x);
        cout << "插入后的链表数据: ";
        list.output();
    }
    return 0;
}