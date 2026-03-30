//         For homework 4.2
//*****    be care for using GBK coding    *****//
//*****    @author Cairenbin
//*****    Date: 2025.11.3 Monday
//4.2.二叉查找树的建立、查找、插入和删除操作。假设二叉树采用二叉链式结构存储
#include <iostream>

template<class E, class K>
struct BSTNode {
    E data; //数据域
    BSTNode<E, K> *leftChild, *rightChild;  //左右子女
    BSTNode(): leftChild(NULL), rightChild(NULL) {} //构造函数
    BSTNode(E d, BSTNode<E, K> *l = NULL, BSTNode<E, K> *r = NULL)  //构造函数
        : data(d), leftChild(l), rightChild(r) {}
    ~BSTNode() {}   //析构函数
    E getData() {return data;}  //数据提取
};

template<class E, class K>
class BST {
private:
    BSTNode<E, K> *root;  //根节点
    void destroy(BSTNode<E, K> *& subTree); //subTree以下置空树
    bool Insert(const E& e1, BSTNode<E,K> *&ptr);
    bool Remove(const K x, BSTNode<E, K> *&ptr);
public:
    BST(): root(NULL) {}    //构造函数
    ~BST() {makeEmpty();}   //析构函数
    bool isEmpty() {return (root == NULL) ? true : false;}  //判断是否为空
    void makeEmpty() {destroy(root);}   //置空树
    bool bulidFromPre();
    bool InsertNum(const E& e1) { return Insert(e1, root); }  //添加元素
    bool RemoveNum(const K x) { return Remove(x, root); } //删除元素
    bool searchNum(E x);    //查找元素
    void output(BSTNode<E, K> *ptr); //输出树
    BSTNode<E, K>* getRoot() { return root; } //获取根节点
};

template <class E, class K>
void BST<E, K>::destroy(BSTNode<E, K> *& subTree) {
    if(!subTree) return;
    destroy(subTree -> leftChild);
    destroy(subTree -> rightChild);
    delete subTree;
    subTree = NULL;     //避免subTree悬空
}   //destroy(BSTNode *& subTree)函数结束

template<class E, class K>
bool BST<E,K>::Insert(const E &e1, BSTNode<E, K> *&ptr) {
    if(searchNum(e1)) return false; //已存在该元素，插入失败
    if(ptr == NULL) {
        ptr = new BSTNode<E, K>(e1);    //作为新的叶子结点插入树
        if(ptr == NULL) {std::cerr << "存储分配失败!" << std::endl; exit(1);}
        return true;
    }
    else if (e1 < ptr->data) return Insert(e1, ptr->leftChild); //左子树插入
    else if(e1 > ptr->data) return Insert(e1, ptr->rightChild);  //右子树插入
    else return false;
}   //Insert(E &e1, BSTNode *&ptr)函数结束

template<class E, class K>
bool BST<E, K>::Remove(const K x, BSTNode<E, K> *&ptr) {
    BSTNode<E, K> *temp;    //存储找到的删除节点
    if(ptr != NULL) {
        if(x < ptr->data) return Remove(x, ptr->leftChild);
        else if(x > ptr->data) return Remove(x, ptr->rightChild);
        else {
        if(ptr->leftChild && ptr->rightChild) {  //找到当前要删节点，开始删除环节，此时该节点有两个子女
            temp = ptr->rightChild; //右子树中找一个替代值
            while(temp->leftChild) { temp = temp->leftChild; }
            ptr->data = temp->data; //  temp数据代替ptr指向数据，后续删除temp即可
            return Remove(ptr->data, ptr->rightChild);     //ptr被赋值temp后，向ptr右子树删除temp的节点(不论temp子树多少都是正常删)
        } else {
            temp = ptr;
            if(!ptr->leftChild) { ptr = ptr->rightChild; }
            else {ptr = ptr->leftChild;}
            delete temp;    //空间temp回收
            return true;
        }
        }
    }
    return false;   //上方结构没提前退出，删除失败
}

template <class E, class K>
bool BST<E, K>::bulidFromPre() {
    int count;
    std::cout << "输入二叉树节点个数: ";
    std::cin >> count;
    if(count == -1) {
        std::cout << "程序结束!" << std::endl;
        exit(0);
    }
    if(count <= 0 && count != -1) return false;
    E value;
    for (int i = 0; i < count; i++)
    {
        std::cin >> value;
        InsertNum(value);
    }
    return true;
}

template <class E, class K>
bool BST<E, K>::searchNum(E x) {
    BSTNode<E, K> *curr = root;
    while(curr) {
        if(x == curr->data) return true;
        else if(x < curr->data) curr = curr->leftChild;
        else curr = curr->rightChild;
    }
    return false;
}

template <class E, class K>
void BST<E, K>::output(BSTNode<E, K> *ptr) {
    if(ptr != NULL) {
        std::cout << ptr->data << " ";
        output(ptr->leftChild);
        output(ptr->rightChild);
    }
}

int main() {
        while(true) {
        BST<int, int> MyTree;
        MyTree.bulidFromPre();
        int number;
/*
        MyTree.output(MyTree.getRoot());    //输出树
        std::cout << std::endl;
*/
        std::cout << "输入要插入的数字: ";
        std::cin >> number;
        if(MyTree.searchNum(number)) {
            std::cout << "数字已存在, 禁止插入!" << std::endl << std::endl;
        } else {
            MyTree.InsertNum(number);   //插入树
            if(MyTree.searchNum(number)) {
            std::cout << "插入成功!" << std::endl << std::endl;
        }
        }
        //插入后查找

        if(MyTree.searchNum(number)) {
            std::cout << "查找成功!" << std::endl;
        }
/*
        MyTree.output(MyTree.getRoot());    //输出插入后树
        std::cout << std::endl;
*/
        MyTree.RemoveNum(number);
        //删除后查找
        if(MyTree.searchNum(number)) {
            std::cout << "查找成功!" << std::endl;
        } else {
            std::cout << "查找失败!" << std::endl;
        }
/*
        MyTree.output(MyTree.getRoot());    //输出删除后树
        std::cout << std::endl;
*/
    }
    return 0;
}