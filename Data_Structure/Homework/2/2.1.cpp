//         For homework 2.(1)(2)(3);
//*****    be care for using GBK coding    *****//
//*****    @author Cairenbin
//*****    Date: 2025.10.1 Wednesday
//2.(1)递归建立单链表
//2.(2)递归输出单链表
//2.(3)递归逆置单链表
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
    List() {first = new LinkNode<T>;}    //构造函数
    List(const T& x) {
        first = new LinkNode<T>();
        first -> link = new LinkNode<T>(x);
    }   //构造函数
    ~List() {makeEmpty();}    //析构函数
    void makeEmpty();   //置空表
    bool isEmpty() const    //判空表
        {return first -> link == NULL ? true: false;}
    int Length() const;    //长度计算
    void recursiveNode(LinkNode<T> *&current);    //递归建立每个节点
    void recursiveOutput(LinkNode<T> *current);    //递归遍历输出每个节点
    LinkNode<T>* recursiveList(LinkNode<T> *current);    //递归遍历逆置每一个节点
    void input();    //建立链表
    void output();    //输出链表
    void Reload();    //逆置链表
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
}   //Length函数结束

template <class T>
void List<T>::recursiveNode(LinkNode<T> *&current) {
    T value;
    cin >> value;
    if(value == -1) {    //遇到-1时结束建立
        //cout << "链表建立结束!" << endl;
        current = NULL;return;
    }
    else if(first -> link == NULL) {
        cout << "程序结束!"; exit(0);
    }
    current = new LinkNode<T>(value);
    recursiveNode(current -> link);
}    //recursiveNode函数结束

template <class T>
void List<T>::recursiveOutput(LinkNode<T> *current) {
    if(current == NULL) {
        //cout << "链表输出结束!" << endl;
        return;
    }
    cout << current -> data << " ";
    recursiveOutput(current -> link);
}    //recursiveOutput函数结束

template <class T>
LinkNode<T>* List<T>::recursiveList(LinkNode<T> *current) {     //
    if (current == NULL || current -> link == NULL) {    //当前为空链表或者最后一个节点时退出递归
        return current;
    }
    LinkNode<T>* newHead = recursiveList(current -> link);
    current -> link -> link = current;    //将current节点的下一节点的link反指向current
    current -> link = NULL;    //将当前节点变为尾巴节点
    return newHead;    //返回新的头部结点
}    //recursiveList函数结束

template <class T>
void List<T>::Reload() {
    first -> link = recursiveList(first -> link);
}    //Reload函数结束

template <class T>
void List<T>::input() {
    makeEmpty();    //确保链表在建立前始终只有附加头结点first
    //cout << "输入链表数据: ";
    T value;
    cin >> value;
    if (value == -1) {    //检查第一次输入，如果第一次输入-1直接结束整个程序运行
        cout << "程序结束!"; exit(0);
    }
    first -> link = new LinkNode<T>(value);    //第一次正常时调用带参数构造函数建立第一个节点
    recursiveNode(first -> link -> link);    //从第一个节点的下一个开始依次递归建立
}    //input函数结束

template <class T>
void List<T>::output() {
    if(first -> link == NULL){
        cout << "链表为空!";
    }
    recursiveOutput(first -> link);    //从附加头结点first的下一位开始输出
    cout << endl;
}    //output函数结束

int main() {
    int i = 0;
    cout << "这个程序实现了第二次作业的递归建立单链表、输出单链表、逆置单链表的功能" << endl;
    while(1) {
        List<int> list;
        list.input();
        cout << "第" << ++i << "组:" << endl;
        cout << "输入的数据: ";
        list.output();
        list.Reload();
        cout << "逆置的数据: ";
        list.output();
    }
    return 0;
}