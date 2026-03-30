//         For homework 1.1, 1.2;
//*****    be care for using GBK coding    *****//
//*****    @author Cairenbin
//*****    Date: 2025.10.1 Wednesday
//1.1有序线性表(数组)插入一元素同时保持有序性
#include <iostream>
using namespace std;

const int defaultSize = 11;    //maxSize of 

template <class T>
class SeqList {
    protected:
        T *data;    //数据域
        int maxSize;
        int last;
    public:
        SeqList(int sz = defaultSize);    //构造函数
        ~SeqList() {delete []data;}    //析构函数
        int Size() const {return maxSize;}    //maxSize
        int Length() const {return (last + 1);}    //length
        bool addNum(T x);    //添加
        bool deleSmallist();    //删除最小值
        void input();    //输入
        void output();    //输出
};  //SeqList 类声明结束

template <class T>
SeqList<T>::SeqList(int sz) {
    if (sz > 0)
    {
        maxSize = sz; last = -1;
        data = new T[maxSize];
        if (data == NULL)
        {cerr << "存储分配错误!" << endl; exit(1);}
    }
}   //SeqList 构造函数结束

template <class T>
bool SeqList<T>::addNum(T x) {
    int point = 0;    //指示元素应存储位置
    while (point <= last && data[point] < x) {point++;}
    if (last == maxSize - 1)
    {
        cout << "顺序表已满，无法插入!" << endl;
        return false;
    }
    for (int j = last; j >= point; j--)
    {
        data[j + 1] = data[j];
    }
    data[point] = x;
    last++;
    return true;
}   //addNum 函数结束

template <class T>
bool SeqList<T>::deleSmallist() {
    if (last == -1)
    {
        cout << "顺序表为空，无法删除!" << endl;
        return false;
    }
    // 找到最小值
    T minVal = data[0];
    for (int i = 1; i <= last; i++)
    {
        if (data[i] < minVal)
        {
            minVal = data[i];
        }
    }
    // 删除所有等于最小值的元素
    int newLast = -1;
    for (int i = 0; i <= last; i++)
    {
        if (data[i] != minVal)
        {
            data[++newLast] = data[i];
        }
    }
    last = newLast;
    return true;
}   //deleSmallist 函数结束

template <class T>
void SeqList<T>::input() {
    //  input data number from ketborad to bulid SeqList
    int arrSize;
    //cout << "输入数组中元素个数:";
    while(true) {
        cin >> arrSize;
        if(arrSize == -1) {cout << "程序结束"; exit(0);}
        if (arrSize >= 0 && arrSize <= maxSize -1) break;
        cout << "元素个数输入有误，范围 0 ~ " << maxSize << " :";
    }
    for (int i = 0; i < arrSize; i++)
    {
        cin >> data[i];
    }
    last = arrSize - 1;
}   //input 函数结束

template <class T>
void SeqList<T>::output() {
    //cout << "顺序表当前元素个数为: " << last << endl;
    if (last == -1)
    {
        cout << "顺序表为空!";
    }
    else
    for(int i = 0; i <= last; i++) {
        cout << data[i] << "  ";
    }
    cout << endl;
}   //output 函数结束

int main() {
    int i = 0;
    cout << "这个程序实现了第一次作业的第1小题的在有序顺序表中添加1个元素并保持顺序表有序的功能" << endl;
    while(1){
        SeqList<int> seqlist;
        seqlist.input();
        int x;
        cin >> x;
        cout << "第" << ++i << "组:" << endl;
        cout << "插入前的数组数据: ";
        seqlist.output();
        seqlist.addNum(x);
        cout << "插入后的数组数据: ";
        //seqlist.deleSmallist();
        //cout << "删除后的数组数据: ";
        seqlist.output();
    }
    return 0;
}