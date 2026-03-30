//         For homework 4.1
//*****    be care for using GBK coding    *****//
//*****    @author Cairenbin
//*****    Date: 2025.11.3 Monday
//4.1.输入扩充的二叉树前序遍历序列（整数值序列），判断该一棵二叉树是否为二叉查找树,输入多颗，-1停机，0空树，输出是(不是)二叉查找树
#include <iostream>
#include <limits>
#include <climits>

const int MIN = INT_MIN;
const int MAX = INT_MAX;
template<class T>
struct BSTNode {
    T data; //数据域
    BSTNode<T> *leftChild, *rightChild;  //左右子女
    BSTNode(): leftChild(NULL), rightChild(NULL) {} //构造函数
    BSTNode(T d, BSTNode<T> *lc = NULL, BSTNode<T> *rc = NULL)  //构造函数
        : data(d), leftChild(lc), rightChild(rc) {}
    ~BSTNode() {}   //析构函数
    T getData() {return data;}  //数据提取
};

template<class T>
class BST {
private:
    BSTNode<T> *root;  //根节点
    void destroy(BSTNode<T> *& subTree);
    bool Insert(const T& e1, BSTNode<T> *&ptr);
    bool Remove(const T& k1, BSTNode<T> *&ptr);
public:
    BST(): root(NULL) {}    //构造函数
    ~BST() {makeEmpty();}   //析构函数
    bool isEmpty() {return (root == NULL) ? true : false;}  //判断是否为空
    void makeEmpty() {destroy(root);}   //置空树
    BSTNode<T>* &getRoot() { return root; }
    bool buildFromPre(BSTNode<T>* &subTree);
    bool isBST(BSTNode<T>* subTree, T min, T max);
};

template <class T>
void BST<T>::destroy(BSTNode<T> * &subTree) {
    if(!subTree) return;
    destroy(subTree -> leftChild);
    destroy(subTree -> rightChild);
    delete subTree;
    subTree = NULL;     //避免subTree悬空
}   //destroy函数结束

template<class T>
bool BST<T>::buildFromPre(BSTNode<T>* &subTree) {
    T x;
    std::cin >> x;
    if(x == 0) {
        subTree = NULL;   //构建空子树
    } else {
        subTree = new BSTNode<T>(x);
        subTree->data = x;
        buildFromPre(subTree->leftChild);
        buildFromPre(subTree->rightChild);
    }
    return true;
}

template<class T>
bool BST<T>::isBST(BSTNode<T>* node, T min, T max) {
    if(node == NULL) { return true; }
    if(node->data >= max || node->data <= min) { return false; }
    return (isBST(node->leftChild, min, node->data) && isBST(node->rightChild, node->data, max));
}

int main() {
    int treeNum;
    std::cout << "输入要测试的扩充二叉树个数: ";
    while(std::cin >> treeNum) {
        if(treeNum == -1) {
            std::cout << "输入-1程序结束!" << std::endl;
            exit(0);
        }
        for(int i =0; i < treeNum; i++) {
            std::cout << "输入第" << i + 1 << "棵扩充二叉树: ";
            BST<int> MyTree;
            MyTree.buildFromPre(MyTree.getRoot());
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if(MyTree.isBST(MyTree.getRoot(), MIN, MAX)) {
                std::cout << "是二叉查找树。" << std::endl;
            } else {
                std::cout << "不是二叉查找树。" << std::endl;
            }
        }
        std::cout << "输入要测试的扩充二叉树个数: ";
    }
    return 0;
}