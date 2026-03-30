//         For homework 3.1
//*****    be care for using GBK coding    *****//
//*****    @author Cairenbin
//*****    Date: 2025.10.15 Wednesday
//3.1.编写非递归函数遍历完全二叉树并输出中序遍历序列
#include <iostream>
#include "stack"
using namespace std;

const int defaultMax = 100;
template <class T>
T data[defaultMax];
int n;
template <class T>
void inOrder(T data[], int n) {
    stack<T> s;
    int curr = 0;  //从0开始，直接从0开始使用整个数组，避免二叉树下表从一开始困扰
    while(curr < n || !s.empty()) {
        //遍历左节点
        while(curr < n) {
            s.push(curr);
            curr = 2 * curr + 1;  //左节点
        }
        if(!s.empty()) {
            curr = s.top();
            s.pop();    //弹出已经被node记录的当前叶子节点，便于下次输出该叶子的双亲节点
            cout << data[curr] << " ";  //数组的索引即表示二叉树索引
            curr = 2 * curr +2;     //右节点
        }
    }
}

int main() {
    while(1) {
    cout << "输入二叉树元素个数: ";
    int num;
    cin >> num;
    if(num == -1) {
        cout << "程序结束!" << endl;
        return 0;
    }
    cout << "输入二叉树节点数据: ";
    int data[num];
    for(int i = 0; i < num; i++) {
        cin >> data[i];
    }
    cout << "中序遍历序列:";
    inOrder(data, num);
    cout << endl;
    }
    return 0;
}
 