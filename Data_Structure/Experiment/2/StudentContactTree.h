//********** coding: GBK **********/
//程序名: StudentContact.h
/*
*版权信息: 该文件为数据结构实验作业，仅供完成数据结构实验作业以及学习交流使用
* 文件名: StudentContactTree.h
* 摘要: 定义学生信息的结构体，二叉链表节点的存储类以及实验文档要求的函数的声明
* @Version: 2.0
* @author: Cairenbin
* 完成日期: 2025.11.15
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include "queue"
using namespace std;

///////////////////////////////////////////////////

/********************************* 结构体Student类定义 *********************************/
//存储学生信息
struct Student {
	string name;    //姓名
	string id;    //学号，后续用于查找、修改信息
    int birthYear; //出生年份
    int birthMonth; //出生月份
    int birthDay; //出生日期
	string sex;    //性别
    string phone;   //电话号码
	string address;    //通讯录地址信息
	double x;    //地址x轴坐标
	double y;    //地址y轴坐标
	//double z;		//地址z轴坐标，应该不会使用这么多？
};    //学生信息结构体定义结束

///////////////////////////////////////////////////

/********************************** 二叉链表节点结构体定义 **********************************/
//存储学生信息的链表节点
struct BinTreeNode {
	Student data;    //学生信息数据域
	BinTreeNode *leftChild, *rightChild;    //左右子节点
    BinTreeNode(): leftChild(nullptr), rightChild(nullptr) {}
	BinTreeNode(const Student& stu, BinTreeNode* lc = nullptr, BinTreeNode* lr = nullptr)
        : data(stu), leftChild(lc), rightChild(lr) {}
};    //链表节点结构体定义结束

///////////////////////////////////////////////////

/********************************** 二叉链表类定义 **********************************/
//实现学生通讯录的各种操作
class BinTree {
protected:
	BinTreeNode* root;    //二叉链表根指针，根指针指向根节点
public:
	BinTree(): root(nullptr) {}    //默认构造函数，头结点直接置空
	BinTree(const Student& x) {    //构造函数
		root = new BinTreeNode(x);    //建立头结点
	}
	~BinTree() { destroy(root); }    //析构函数
    BinTreeNode* getRoot() { return root;} //返回根节点
	void destroy(BinTreeNode* subTree);    //将链表置空
    void makeEmpty() { destroy(root); root = nullptr; }    //置空链表
	bool isEmpty() {    //判断链表是否为空
		return root == nullptr ? true : false;
	}
	int Amount() const;    //学生人数计算
    int getStudentNumber(BinTreeNode* subTree) const;     //遍历统计学生
    bool addStudent(BinTreeNode * newStu);    //添加学生
	//bool addStuInfo(BinTreeNode* newStu, int pos);	//按位置号向通讯录插入新学生信息
    //  这一个按位置插入函数还需要吗？二叉树实现按位置插入不是一个好的插入办法？
	BinTreeNode* existsId(const string& id);//判断学号是否存在并返回学生信息
    BinTreeNode* existsName(const string& nam);   //判断姓名是否存在并返回学生信息
    BinTreeNode* existsPhone(const string& Ph);   //判断电话号码是否存在并返回学生信息
	bool deleStudent();    //删除学生
	void input();    //输入
    void output_smallestStu(); //输出年龄最小的学生信息
	void output_sameX(double xin); //输出学生地址位置横坐标相同的学生全部信息
    void output(BinTreeNode* subTree); //输出指定学生信息
	void output(BinTreeNode* subTree, ostream& out); //前序遍历输出所有学生信息
	friend istream& operator>>(istream& in, Student& stu);	//学生信息文件读写_输入
	friend ostream& operator<<(ostream& out, const Student& stu);	//学生信息文件读写_输出
	friend istream& operator>>(istream& in, BinTree& tree);	//链表整体信息文件读写_输入
	friend ostream& operator<<(ostream& out, const BinTree& tree);		//链表整体文件读写_输出
};

/////////////////////////////////////////////////

//函数功能: 二叉链表类成员函数实现, 将链表置空
//函数参数: BinTreeNode* subTree，指向子树根节点的指针
//参数返回值: 无
void BinTree::destroy(BinTreeNode* subTree) {
    if(!subTree) { return; }
    destroy(subTree->leftChild);
    destroy(subTree->rightChild);
    delete(subTree);
	//这个删除函数会保留根指针root，但不会保留根节点
}   //makEmpty函数结束

/////////////////////////////////////////////////

//函数功能: 计算学生人数
//函数参数: 无
//参数返回值: 学生人数int
int BinTree::Amount() const {
    return getStudentNumber(root);
}	//Amount const函数结束

/////////////////////////////////////////////////

//函数功能: 遍历统计学生人数
//函数参数: BinTreeNode* subTree，指向子树根节点的指针
//参数返回值: 学生人数int
int BinTree::getStudentNumber(BinTreeNode* subTree) const {
    if(!subTree) {return 0;}
    int sum_leftChild = getStudentNumber(subTree->leftChild);
    int sum_rightChild = getStudentNumber(subTree->rightChild);
    return 1 + sum_leftChild + sum_rightChild;
}	//Amount const函数结束

///////////////////////////////////////////////////

//函数功能: 插入学生信息到二叉树末尾
//函数参数: BinTreeNode* newstu，指向新学生节点的指针
//参数返回值: bool，添加成功返回true，失败返回false
bool BinTree::addStudent(BinTreeNode *newStu) {
    if(!newStu) return false;	//newstu为空指针则返回false
    if (existsId(newStu->data.id)) {
        // 拒绝重复id，调用方负责 delete newStu（若需要）
        return false;
    }
    // 确保新节点没有悬挂子指针
    newStu->leftChild = newStu->rightChild = nullptr;  //新插入节点左右孩子为空
    if(!root) {
        root = newStu;
        return true;
    }
    queue<BinTreeNode*> q;
    q.push(root);
    while(!q.empty()) { //层次化遍历插入
        BinTreeNode* cur = q.front();
        q.pop();
        // 先尝试插入左子节点
        if(!cur->leftChild) {
            cur->leftChild = newStu;
            return true;
        } else {
            q.push(cur->leftChild);
        }
        // 再尝试插入右子节点
        if(!cur->rightChild) {
            cur->rightChild = newStu;
            return true;
        } else {
            q.push(cur->rightChild);
        }
    }
    return false;
}    //addStudent函数结束

///////////////////////////////////////////////////

//函数功能: 按位置号向通讯录插入新学生信息
//函数参数: BinTreeNode* p，指向新学生节点的指针
//         int pos，插入位置号
//参数返回值: bool，插入成功返回true，失败返回false
/*
bool BinTree::addStuInfo(BinTreeNode* newStu, int pos) {
    if (!newStu || pos < 1) return false;
	if (existsId(newStu->data.id)) {
        return false;
    }
    BinTreeNode* cur = root; // 前驱指针，从头结点开始
    int i = 1;
    // 移动到第 pos-1 个数据节点（即插入位置的前驱），但不要越过尾部
    while (i < pos && cur->link != nullptr) {
        cur = cur->link;
        ++i;
    }
    // 插入
    newStu->link = cur->link;
    cur->link = newStu;
    return true;
}	//addStuInfo函数结束
*/

/////////////////////////////////////////////////

//函数功能: 判断学号是否存在
//函数参数: const string& id，表示学生学号的常引用
//参数返回值: BinTreeNode* foundStu, 指向找到对应学生指针，不存在则返回空指针nullptr
BinTreeNode* BinTree::existsId(const string& id) {
    if (!root) return nullptr;    //空子树直接返回false
    queue<BinTreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        BinTreeNode* curr = q.front();   // 取出二叉链表头结点
        q.pop();
        if (curr->data.id == id) {
            BinTreeNode* foundStu = curr;
            return foundStu;
        }
        if (curr->leftChild) q.push(curr->leftChild);     // 左子节点入队
        if (curr->rightChild) q.push(curr->rightChild);   // 右子节点入队
    }
    return nullptr;
}

///////////////////////////////////////////////////

//函数功能: 判断姓名是否存在
//函数参数: const string& nam，表示学生姓名的常引用
//参数返回值: BinTreeNode* foundStu, 指向找到对应学生指针，不存在则返回空指针nullptr
BinTreeNode* BinTree::existsName(const string& nam) {
    if(!root) return nullptr; //空根节点直接返回
    queue<BinTreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        BinTreeNode* curr = q.front();
        q.pop();
        if(curr->data.name == nam) {
            BinTreeNode *foundStu = curr;
            return foundStu;
        }
        if(curr->leftChild) q.push(curr->leftChild);
        if(curr->rightChild) q.push(curr->rightChild);
    }
    return nullptr;
}

///////////////////////////////////////////////////

//函数功能: 判断电话号码是否存在
//函数参数: const string& phon，表示学生姓名的常引用
//参数返回值: BinTreeNode* foundStu, 指向找到对应学生指针，不存在则返回空指针nullptr
BinTreeNode* BinTree::existsPhone(const string& phon) {
    if(!root) return nullptr; //空根节点直接返回
    queue<BinTreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        BinTreeNode* curr = q.front();
        q.pop();
        if(curr->data.phone== phon) {
            BinTreeNode *foundStu = curr;
            return foundStu;
        }
        if(curr->leftChild) q.push(curr->leftChild);
        if(curr->rightChild) q.push(curr->rightChild);
    }
    return nullptr;
}

///////////////////////////////////////////////////

//函数功能: 删除指定学生（支持按学号 / 姓名 / 电话删除）
//函数参数: 无
//参数返回值: bool，删除成功返回true，失败返回false
bool BinTree::deleStudent() {
    if (!root) {
        cout << "通讯录为空，无法删除!" << endl;
        return false;
    }

    int judge;
    cout << "1.学号, 2.姓名, 3.电话号码" << endl;
    cout << "输入什么信息来定位删除学生? ";
    cin >> judge;

    string key;
    switch (judge) {
    case 1:
        cout << "请输入要删除学生的学号: ";
        cin >> key;
        break;
    case 2:
        cout << "请输入要删除学生的姓名: ";
        cin >> key;
        break;
    case 3:
        cout << "请输入要删除学生的电话号码: ";
        cin >> key;
        break;
    default:
        cout << "无效选项!" << endl;
        return false;
    }

    //记录每个节点的父节点，找到目标节点和最后一个节点替换当前节点
    queue<pair<BinTreeNode*, BinTreeNode*>> q;
    q.push({root, nullptr});
    //二元组(当前节点指针, 父节点指针)

    BinTreeNode* target = nullptr; //指向要删除的目标节点，初始为nullptr
    //BinTreeNode* targetParent = nullptr;
    BinTreeNode* last = nullptr; //指向遍历过程中遇到的最后一个节点(最底层最右侧节点)
    BinTreeNode* lastParent = nullptr; //记录last节点的父节点

    while (!q.empty()) {
        auto pr = q.front(); q.pop();
        BinTreeNode* node = pr.first;
        BinTreeNode* parent = pr.second;
        // 更新最后访问到的节点（用于找到最底层最右节点）
        last = node;
        lastParent = parent;

        // 根据选择判断匹配
        bool match = false;
        if (judge == 1 && node->data.id == key) match = true;
        else if (judge == 2 && node->data.name == key) match = true;
        else if (judge == 3 && node->data.phone == key) match = true;

        if (match) {
            target = node;

        }

        if (node->leftChild) q.push({node->leftChild, node});
        if (node->rightChild) q.push({node->rightChild, node});
    }

    if (!target) {
        cout << "未找到匹配的学生，删除失败!" << endl << endl;
        return false;
    }

    cout << "找到的学生信息如下：" << endl;
    output(target);
    cout << "确定要删除该学生吗？(Y/N): ";
    char confirm;
    cin >> confirm;
    if (confirm != 'Y' && confirm != 'y') {
        cout << "已取消删除操作。" << endl;
        return false;
    }
    
    // 如果最后节点就是目标节点，直接删除该节点
    if (last == target) {
        if (lastParent == nullptr) { // last == root 且树只有这一个节点, 如果是根节点
            delete root;
            root = nullptr;
        } else {
            if (lastParent->leftChild == last) lastParent->leftChild = nullptr;
            else if (lastParent->rightChild == last) lastParent->rightChild = nullptr;
            delete last;
        }
        cout << "删除成功!" << endl;
        return true;
    }

    // 否则，用最后节点的数据覆盖目标节点的数据，然后删除最后节点
    target->data = last->data;
    if (lastParent) {
        if (lastParent->leftChild == last) lastParent->leftChild = nullptr;
        else if (lastParent->rightChild == last) lastParent->rightChild = nullptr;
    } else {
        // 理论上不会到这里
        //（如果 lastParent == nullptr 则 last==root，以前已处理）
    }
    delete last;
    cout << "删除成功!" << endl;
    return true;
}	//deleStudent函数结束

///////////////////////////////////////////////////

//函数功能: 输入学生信息
//函数参数: 无；
//参数返回值: 无；
void BinTree::input() {
    int n;
    cout << "请输入学生人数: ";
    cin >> n;
	if(n <= 0) return;
    destroy(root);
    for (int i = 0; i < n; ++i) {
        Student stu;
        cout << "输入第" << i + 1 << "个学生信息"<< endl 
             << "(姓名 学号 出生年 月 日 性别 电话 地址名 x坐标 y坐标): " << endl;;
        cin >> stu.name >> stu.id >>  stu.birthYear >> stu.birthMonth
            >> stu.birthDay >> stu.sex >> stu.phone >> stu.address >> stu.x >> stu.y;
        addStudent(new BinTreeNode(stu));
    }
}	//input函数结束

////////////////////////////////////////////////////

//函数功能: 找到并输出年龄最小的学生信息
//函数参数: 无
//参数返回值: 无
void BinTree::output_smallestStu() {
    if(!root) {
        cout << "通讯录为空, 查找失败!" << endl;
        return;
    }
    BinTreeNode* smallestStu = root;
    queue<BinTreeNode*> minStu;
    minStu.push(root);
    while(!minStu.empty()) {
        BinTreeNode* curr = minStu.front(); //curr指针指向minStu队列首个元素
        minStu.pop();
        if(
            (curr->data.birthYear > smallestStu->data.birthYear) ||
            ((curr->data.birthYear == smallestStu->data.birthYear) &&
            (curr->data.birthMonth > smallestStu->data.birthMonth)) ||
            ((curr->data.birthYear == smallestStu->data.birthYear) && 
            (curr->data.birthMonth == smallestStu->data.birthMonth) &&
            (curr->data.birthDay > smallestStu->data.birthDay))
        ) { smallestStu = curr; }
        if(curr->leftChild) {minStu.push(curr->leftChild);}
        if(curr->rightChild) {minStu.push(curr->rightChild);}
    }
    cout << "年龄最小学生信息是:" << endl;
    output(smallestStu);
}	//output_smallestStu函数结束

/////////////////////////////////////////////////

//函数功能: 找到并输出地址位置横坐标相同的学生信息
//函数参数: 无
//参数返回值: 无
void BinTree::output_sameX(double xin) {
    if(!root) {
        cout << "通讯录为空, 无法查找!" << endl;
        return;
    }
    queue<BinTreeNode*> q;
    q.push(root);
    bool found = false;
    while(!q.empty()) {
        BinTreeNode* curr = q.front(); //curr指针指向queue的首个元素
        q.pop();
        if(curr->data.x == xin) {
            output(curr);
            found = true;
        }
        if(curr->leftChild) q.push(curr->leftChild);
        if(curr->rightChild) q.push(curr->rightChild);
    }
    if(!found) cout << "没有找到横坐标为: " << xin << "的学生" << endl;
}	//output_sameX函数结束

/////////////////////////////////////////////////

/***********************************************************/
/*************** 单个学生信息输入输出流重载 ******************/
/***********************************************************/


//函数功能: 学生信息文件读写_输入
//函数参数: istream& in，输入流引用
//         Student& stu，学生信息结构体引用
//参数返回值: istream&，输入流引用
istream& operator>>(istream& in, Student& stu) {
    in >> stu.name >> stu.id >> stu.birthYear >> stu.birthMonth
        >> stu.birthDay >> stu.sex >> stu.phone >> stu.address >> stu.x >> stu.y;
    return in;
}	//学生输入重载结束

////////////////////////////////////////////////////

//函数功能: 输出指定学生信息
//函数参数: 无
//参数返回值: 无
void BinTree::output(BinTreeNode* subTree) {
    if (!subTree) return; // 空子树直接返回
    // 访问根节点（前序：根 -> 左 -> 右）
    cout << "姓名: " << subTree->data.name << endl;
    cout << "学号: " << subTree->data.id << endl;
    cout << "出生日期: "  << subTree->data.birthYear << "-"
                        << subTree->data.birthMonth << "-"
                        << subTree->data.birthDay << endl;
    cout << "性别: " << subTree->data.sex << endl;
    cout << "电话号码: " << subTree->data.phone << endl;
    cout << "地址: " << subTree->data.address << endl;
    cout << "X坐标: " << subTree->data.x << ", Y坐标: " << subTree->data.y << endl;
    cout << endl;
}   //output函数结束

///////////////////////////////////////////////

//函数功能: 前序遍历输出所有学生信息
//函数参数: 无
//参数返回值: 无
void BinTree::output(BinTreeNode* subTree, ostream& out) {
    if (!subTree) return; // 空子树直接返回
    // 访问根节点（前序：根 -> 左 -> 右）
    out << "姓名: " << subTree->data.name << endl;
    out << "学号: " << subTree->data.id << endl;
    out << "出生日期: "  << subTree->data.birthYear << "-"
                        << subTree->data.birthMonth << "-"
                        << subTree->data.birthDay << endl;
    out << "性别: " << subTree->data.sex << endl;
    out << "电话号码: " << subTree->data.phone << endl;
    out << "地址: " << subTree->data.address << endl;
    out << "X坐标: " << subTree->data.x << ", Y坐标: " << subTree->data.y << endl;
    out << endl;

    // 递归遍历左、右子树
    output(subTree->leftChild, out);
    output(subTree->rightChild, out);
}   //output函数结束

///////////////////////////////////////////////

//函数功能: 学生信息文件读写_输出
//函数参数: ostream& out，输出流引用
//         const Student& stu，学生信息结构体常引用
//参数返回值: ostream&，输出流引用
ostream& operator<<(ostream& out, const Student& stu) {
    out << stu.name << " " << stu.id << " " << stu.birthYear << " " 
        << stu.birthMonth << " " << stu.birthDay << " " << stu.sex << " " 
        << stu.phone << " " << stu.address << " " << stu.x << " " << stu.y;
    return out;
}	//学生输出重载结束

/***************** 二叉链表整体输入输出流重载 ******************/

/////////////////////////////////////////////////

//函数功能: 链表整体信息文件读写_输入
//函数参数: istream& in，输入流引用
//         BinTree& tree，二叉链表类引用
//参数返回值: istream&，输入流引用
istream& operator>>(istream& in, BinTree& tree) {
    tree.destroy(tree.root);
    Student stu;
    while (in >> stu) {
		if (tree.existsId(stu.id)) {
            // 跳过重复记录 //默认所有学生信息都不一样？
            continue;
        }
        BinTreeNode* node = new BinTreeNode(stu);
		if (!tree.addStudent(node)) { // 若 addStudent 失败（理论上已被 existsId 拦截?）
            delete node;
        }
    }
    return in;
}	//链表输入重载结束

/////////////////////////////////////////////////

//函数功能: 链表整体信息文件读写_输出
//函数参数: ostream& out，输出流引用
//         const BinTree& tree，二叉链表类常引用
//参数返回值: ostream&，输出流引用
ostream& operator<<(ostream& out, const BinTree& tree) {
    if (!tree.root) return out;
    // reuse the existing traversal output; remove constness temporarily
    const_cast<BinTree&>(tree).output(tree.root, out);
    return out;
}	//链表输出重载结束
