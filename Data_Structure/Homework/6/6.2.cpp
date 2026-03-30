//         For homework 6.2
//*****    be care for using GBK coding    *****//
//*****    @author Cairenbin
//*****    Date: 2025.11.25 Tuesday
//6.2.以邻接表为有向不带权图的存储结构，实现求拓扑序列的程序。
#include <iostream>
#include <queue>
using namespace std;

const int DefaultVertices = 100;

template <class T>
struct Edge {
    int dest; //边的另一节点定义
    Edge<T>* link; //下边链指针
    Edge() {}   //构造函数
    Edge(int num) : //构造函数
        dest(num), link(nullptr) {}
};

template <class T>
struct Vertex {
    Edge<T>* adj; //边链表头指针
};

template <class T>
class Graph {
private:
    int numVertices;
    Vertex<T>* NodeTable; //顶点表
    bool *visited; //是否访问标记
public:
    Graph(int sz = DefaultVertices);
    ~Graph();
    bool input();
    void toPologicalSort();
};

template<class T>
Graph<T>::Graph(int sz) {
    numVertices = 0;
    NodeTable = new Vertex<T>[sz];
    if(!NodeTable) {
        cerr << "存储分配失败!" << endl;
        exit(1);
    }
    visited = new bool[sz];
    if(!visited) {
        cerr << "访问记录数组存储分配失败!" << endl;
        exit(1);
    }
    for(int i = 0; i < sz; ++i) {
        NodeTable[i].adj = nullptr;
        visited[i] = false;
    }
};

template <class T>
Graph<T>::~Graph() {
    for(int i = 0; i < numVertices; ++i) {
        Edge<T>* p = NodeTable[i].adj;
        while(p) {
            Edge<T>* tmp = p;
            p = p->link;
            delete tmp;
        }
        NodeTable[i].adj = nullptr;
    }
    delete []NodeTable;
    delete []visited;
};

template <class T>
bool Graph<T>::input() {
    cout << "输入图节点个数: ";
    cin >> numVertices;
    if(numVertices == -1) {
        cout << "程序结束!" << endl;
        exit(0);
    }
    if(numVertices < 0) {return false;}
    for(int i = 0; i < numVertices; ++i) {
        NodeTable[i].adj = nullptr;
    }
    cout << "输入图的邻接表:" << endl;
    for(int i = 0; i < numVertices; ++i) {
        cout << "节点" << i << "的邻接节点: ";
        int number;
        Edge<T>* tail = nullptr;
        while(cin >> number && number != -1) {
            Edge<T>* newEdge = new Edge<T>(number);
            if(NodeTable[i].adj == nullptr) {
                NodeTable[i].adj = newEdge;
                tail = newEdge;
            } else {
                tail->link = newEdge;
                tail = newEdge;
            }
        }
    }
    return true;
};

// 拓扑排序：有回路输出“该图存在回路”，否则输出拓扑序列
template <class T>
void Graph<T>::toPologicalSort() {
    int* indegree = new int[numVertices]; // 入度数组
    for(int i = 0; i < numVertices; ++i) {
        indegree[i] = 0; //初始化节点入读0
    }

    // 统计每个节点的入度
    for(int i = 0; i < numVertices; ++i) {
        for(Edge<T>* e = NodeTable[i].adj; e; e = e->link) {
            indegree[e->dest]++; //遍历邻接表检查每点入度
        }
    }
    queue<int> q;
    // 入度为0的点入队
    for(int i = 0; i < numVertices; ++i) {
        if(indegree[i] == 0) q.push(i); //入度为0的节点入队，作为拓扑排序的起点
    }

    int hasOutput = 0; //统计已经输出节点数量
    cout << "拓扑序列: ";
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";
        hasOutput++;
        for(Edge<T>* e = NodeTable[u].adj; e; e = e->link) {
            indegree[e->dest]--;
            if(indegree[e->dest] == 0) q.push(e->dest);
        }
    }
    cout << endl;
    if(hasOutput < numVertices) { //最后输出的结点数小于总结点数，存在入度不为0节点(环)
        cout << "该图存在回路" << endl;
    }
    delete[] indegree;
}

int main() {
    int i = 0;
    Graph<int> MyGraph;
    while(1)
    {
        cout << "第" << ++i << "次:" << endl;
        MyGraph.input();
        MyGraph.toPologicalSort();
        cout << endl;
    }
    return 0;
}

/*
2.写出以邻接表为有向不带权图的存储结构，实现求拓扑序列的程序。
输入：
（1）图的结点总数，以输入 -1 来结束整个程序的运行。
（2）分别输入每个结点所邻接到的邻接结点序号，以-1作结束
输出：
 （1）如果图不存在回路，则输出拓扑序列结果
 （2）如果图存在回路，则输出“该图存在回路”
*/