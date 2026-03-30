//         For homework 3.3
//*****    be care for using GBK coding    *****//
//*****    @author Cairenbin
//*****    Date: 2025.10.15 Wednesday
//3.3序遍历序列和中序遍历序列以生成二叉树二叉链式结构，并采用前序遍历序列输出该二叉树
/*
3.设计一个程序：输入后序遍历序列和中序遍历序列以生成二叉树二叉链式结构，并采用前序遍历序列输出该二叉树。
  输入：
   （1）输入有多少棵二叉树要进行测试（以-1结束整个程序的运行）：
   （2）输入二叉树的后序遍历序列（以0结束序列的输入）
   （3）输入二叉树中序遍历序列（以0结束序列的输入）
  输出：
     二叉树的前序遍历序列
*/
#include <iostream>
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
    BinTreeNode<T>* buildFromPostIn(T post[], int postL, int postR, T in[], int inL, int inR);      //按照后序遍历和中序遍历建立二叉树
    void createTree(T post[], int postLen, T in[], int len);
    void preOrder(BinTreeNode<T> *t);
    void preOrder();
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
BinTreeNode<T>*  BinnaryTree<T>::buildFromPostIn(T post[], int postL, int postR, T in[], int inL, int inR) {
    if(postL > postR) return NULL;  //空二叉树和不规范的不建立
    T rootVal = post[postR];    //后序遍历性质，最后为头
    BinTreeNode<T> *node = new BinTreeNode<T>(rootVal);      //建立头
    int k = inL;
    while(k <= inR && in[k] != rootVal) ++k;
    int leftLen = k - inL;
    node->leftChild = buildFromPostIn(post, postL, postL + leftLen - 1, in, inL, k - 1);
    node->rightChild = buildFromPostIn(post, postL + leftLen, postR - 1, in, k + 1, inR);
    return node;
}   //*buildFromPostIn函数结束

template <class T>
void BinnaryTree<T>::createTree(T post[], int postLen, T in[], int inLen) {
    root = buildFromPostIn(post, 0, postLen - 1, in, 0, inLen - 1);
}

template <class T>
void BinnaryTree<T>::preOrder(BinTreeNode<T> *t) {
    if(!t) return ;
    cout << t->data << " ";
    preOrder(t->leftChild);
    preOrder(t->rightChild);
}   //preOrder泛用前序遍历二叉树函数结束

template <class T>
void BinnaryTree<T>::preOrder() {
    preOrder(root);
}   //preOrder指定当前二叉树函数结束

int main() {
    while(1) {
    cout << "输入要测试二叉树的数量:";
    int num;
    cin >> num;
    if(num == -1) return 0;     //输入为-1时退出整个程序
    for(int i = 0; i < num; i++) {
        int post[100], in[100], x, postLen = 0, inLen = 0;
        cout << "输入二叉树的后序遍历序列:";
        while(cin >> x && x != 0) post[postLen++] = x;      //输入后序遍历
        cout << "输入二叉树的中序遍历序列:";
        while(cin >> x && x != 0) in[inLen++] = x;      //输入中序遍历
        BinnaryTree<int> MyTree;
        MyTree.createTree(post, postLen, in, inLen);    //构建二叉树
        cout << "二叉树的前序遍历: ";
        MyTree.preOrder();
        cout << endl;
    }
    }
    return 0;
}