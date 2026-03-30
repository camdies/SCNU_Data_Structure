//         For homework 3.2
//*****    be care for using GBK coding    *****//
//*****    @author Cairenbin
//*****    Date: 2025.10.15 Wednesday
//3.2将多个二叉树的所有叶子结点从左向右链接成一个单链表的算法。
#include <iostream>
#include "stack"
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
    bool addNum(T x);    //添加
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
bool List<T>::addNum(T x) {
    LinkNode<T> *p = first;   // p 指向当前节点的前一个节点
    while (p->link != NULL) {
        p = p->link;         // 找到最后一个位置
    }
    // 创建新节点，并插入到 p 和 p->link 之间
    LinkNode<T> *newNode = new LinkNode<T>(x, p->link);
    if (newNode == NULL) return false; // 内存分配失败
    p->link = newNode;
    return true;
}    //addNum函数结束



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

template <class T>
struct BinTreeNode {
    T data;     //数据域
    BinTreeNode<T> *leftChild, *rightChild;     //左右子节点访问指针
    BinTreeNode() : leftChild(NULL), rightChild(NULL) {};      //默认构造函数，构建空二叉树
    BinTreeNode(T x, BinTreeNode<T> *lptr = NULL, BinTreeNode<T> *rptr = NULL)
        : data(x), leftChild(lptr), rightChild(rptr) {}     //构造函数
};  //二叉树节点结构体结束

template <class T>
class BinnaryTree {
protected:
    BinTreeNode<T> *root;
    T RefValue;    //引用值
    void destroy(BinTreeNode<T> *& subTree);     //删除树
public:
    BinnaryTree(): root(NULL) {}    //构造函数
    BinnaryTree(T value) : RefValue(value), root(NULL) {}      //构造函数
    ~BinnaryTree() {destroy(root);}     //析构函数
    void setRoot(BinTreeNode<T>* newRoot) { root = newRoot; }
    BinTreeNode<T> *getRoot() {return root;}     //返回根节点
    bool isEmpty() {return (root == NULL) ? true : false;}      //判空树
    BinTreeNode<T>* createTree();     //创建二叉树
    void collectLeaves(BinTreeNode<T> *root, List<T> &list);    //收集单个叶子节点
};  //BinnaryTree类声明结束

template <class T>
void BinnaryTree<T>::destroy(BinTreeNode<T> *& subTree) {
    if(!subTree) return;
    destroy(subTree -> leftChild);
    destroy(subTree -> rightChild);
    delete subTree;
    subTree = NULL;     //避免subTree悬空
}   //destroy函数结束

template <class T>
BinTreeNode<T>* BinnaryTree<T>::createTree() {
    T x;
    cin >> x;
    if(x == 0) return NULL;     //返回空，说明这个是空节点
    BinTreeNode<T> *root = new BinTreeNode<T>(x);
    root -> leftChild = createTree();    //递归继续调用当前左节点继续建立左右孩子
    root -> rightChild = createTree();   //递归继续调用当前右节点继续建立左右孩子
    return root;    //返回最终根节点
}   //createTree函数结束

template <class T>
void BinnaryTree<T>::collectLeaves(BinTreeNode<T> *root, List<T> &list) {
    if(!root) return;
    if(root -> leftChild == NULL && root -> rightChild == NULL) {
        list.addNum(root -> data) ;   //如果是叶子节点就加入链表
    }
    collectLeaves(root -> leftChild, list);   //递归遍历左子树
    collectLeaves(root -> rightChild, list);  //递归遍历右子树
}   //collectLeaves函数结束
//这个实现了单个二叉树的叶子节点的收集

template <class T>
void collect_all_leaves(BinnaryTree<T> trees[], int n, List<T> &list) {
    for(int i = 0; i < n; i++) {
        trees[i].collectLeaves(trees[i].getRoot(), list);   //收集每个二叉树的叶子节点
    }
}   //collect_all_leaves函数结束

int main() {
    int i = 0;
    while(1) {
    int num;
    cout << "输入二叉树的数量:";
    cin >> num;
    if(num == -1) return 0;
    BinnaryTree<int> *MyTrees = new BinnaryTree<int>[num];
    for(int i = 0; i < num; i++) {
        //cout << "输入" << i + 1 << "号二叉树的前序遍历序列:";
        MyTrees[i].setRoot(MyTrees[i].createTree());   //创建二叉树
    }
    List<int> leaveslist;
    collect_all_leaves(MyTrees, num, leaveslist);   //收集所有二叉树的叶子节点
    cout << "第" << ++i << "组单链表:";
    leaveslist.output();   //输出最终叶子链表
    delete[] MyTrees;
    }
    return 0;
}   //main函数结束
//程序结束