//         For homework 3.4
//*****    be care for using GBK coding    *****//
//*****    @author Cairenbin
//*****    Date: 2025.10.15 Wednesday
//3.4出二叉树中所有左右子树高度差的绝对值为2的结点
/*
4.编写一个输出二叉树中所有左右子树高度差的绝对值为2的结点。二叉树的存储结构为二叉链式结构。
  输入
   （1）输入有多少棵二叉树要进行测试（以-1结束整个程序的运行）：
   （2）分别输入扩充的二叉树前序遍历序列（整数值序列），0表示空子树。
  输出：
      输出左右子树高度差的绝对值为2的结点。
*/
#include <iostream>
#include <algorithm>
#include <cmath>
#include "stack"
using namespace std;

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
    T *LRV;     //储存后序遍历
    T *LVR;     //储存中序遍历
    BinnaryTree(): root(NULL) {}    //构造函数
    BinnaryTree(T value) : RefValue(value), root(NULL) {}      //构造函数
    ~BinnaryTree() {destroy(root);}     //析构函数
    void setRoot(BinTreeNode<T>* newRoot) { root = newRoot; }
    BinTreeNode<T> *getRoot() {return root;}     //返回根节点
    bool isEmpty() {return (root == NULL) ? true : false;}      //判空树
    BinTreeNode<T>* createTree();   //前序递归建立二叉树
    int print_2_nodes(BinTreeNode<T> *curr);    //递归输出左右子树高度相差2的节点
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
    BinTreeNode<T> *curr = new BinTreeNode<T>(x);
    curr -> leftChild = createTree();    //递归继续调用当前左节点继续建立左右孩子
    curr -> rightChild = createTree();   //递归继续调用当前右节点继续建立左右孩子
    return curr;    //返回最终根节点
}   //createTree函数结束

template <class T>
int BinnaryTree<T>::print_2_nodes(BinTreeNode<T> *curr) {
    if(!curr) return 0;     //空返回0直接结束
    int leftHeight = print_2_nodes(curr -> leftChild);
    int rightHeight = print_2_nodes(curr -> rightChild);
    if(abs(leftHeight - rightHeight) == 2) {
        cout << curr -> data << " ";
    }
    return max(leftHeight, rightHeight) + 1;   //返回当前节点的高度
}


int main() {
    while(1) {
    cout << "输入要测试二叉树的数量:";
    int num;
    cin >> num;
    if(num == -1) return 0;     //输入为-1时退出整个程序
    for(int i = 0; i < num; i++) {
        cout << "输入二叉树的前序遍历序列:";
        BinnaryTree<int> tree;
        // main函数中构建树的部分修改为：
    BinTreeNode<int>* rootNode = tree.createTree();  // 接收返回的根节点
    tree.setRoot(rootNode);  // 将根节点赋值给tree的root成员
        cout << "二叉树左右子树高度差的绝对值为2的结点: ";
        tree.print_2_nodes(tree.getRoot());     //输出高度差为2的节点
        cout << endl;
    }
    }
    return 0;
}