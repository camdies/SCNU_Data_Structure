#include <iostream>
using namespace std;
template <class T>
struct LinkNode{
    T data;
    LinkNode<T> *link;
    LinkNode(LinkNode<T> *ptr = null) {link = ptr}//初始化指针成员
    LinkNode(const T& item, LinkNode<T> *ptr = NULL) {data = item;link = ptr;}  //初始化数据、指针成员
};
template <class T>
class List{
public:
    List() {first = new LinkNode<T>;}   //构造
    List(const T& x,){first = new LinkNode<T>(x);}  //构造
    ~List() {makeEmpty();}  //析构
    void makeEmpty();   //置空表 。
    void input();   //输入
    void output();  //输出
protected:
    LinkNode<T> *first;
};

template <class T>
void List<T>::makeEmpty() {
    LinkNode<T> *q;
    while (first->link != NULL)
    {
        q = first -> link;
        first -> link = q -> link;
        delete q;
    }
};

template <class T>
void List<T>::input() {

};

template<class T>
void List<T>::output() {};