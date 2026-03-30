//         For homework 5.2
//*****    be care for using GBK coding    *****//
//*****    @author Cairenbin
//*****    Date: 2025.11.25 Tuesday
//5.2.输入邻接表为图(不带权的有向图或无向图)的存储结构，输出广度优先和深度优先遍历序列
#include <iostream>
#include <queue>
using namespace std;

const int DefaultVertices = 100;

template <class T>
struct Edge {
    int dest; //边的另一节点定义, 指向编号为dest的节点
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
class Graphlnk {
private:
    int numVertices;
    Vertex<T>* NodeTable; //顶点表
    bool *visited; //是否访问标记
public:
    Graphlnk(int sz = DefaultVertices);
    ~Graphlnk();
    bool input();
    void reflashVisited();
    void BFSBase(int start); //广度优先实现
    void BFS(int start); //广度优先入口
    void DFSRecursive(int start); //深度优先实现
    void DFS(int start); //深度优先入口
};

template<class T>
Graphlnk<T>::Graphlnk(int sz) {
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
Graphlnk<T>::~Graphlnk() {
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
bool Graphlnk<T>::input() {
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

template <class T>
void Graphlnk<T>::reflashVisited() {
    for(int i = 0; i < numVertices; ++i) {
        visited[i] = false;
    }
}

template <class T>
void Graphlnk<T>::BFSBase(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while(!q.empty()) {
        int point = q.front();
        q.pop();
        cout << point << " ";
        Edge<T>* p = NodeTable[point].adj;
        while(p != nullptr) {
            if(!visited[p->dest]) { //发现未访问邻接节点
                q.push(p->dest); //入队
                visited[p->dest] = true; //标记已访问
            }
            p = p->link;
        }
    }
};

template <class T>
void Graphlnk<T>::BFS(int start) {
    if(start < 0 || start >= numVertices) {
        cout << "非法起始节点!" << endl;
        return;
    }
    reflashVisited();
    cout << "广度优先搜索序列:" << endl;
    BFSBase(start);
    cout << endl;
};

//深度优先递归实现
template <class T>
void Graphlnk<T>::DFSRecursive(int start) {
    visited[start] = true;
    cout << start << " ";
    Edge<T>* p = NodeTable[start].adj;
    while(p != nullptr) {
        if(!visited[p->dest]) {
            DFSRecursive(p->dest);
        }
        p = p->link; //继续检查下一个邻接节点
    }
};                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    


template <class T>
void Graphlnk<T>::DFS(int start) {
    if(start < 0 || start >= numVertices) {
        cout << "非法起始节点!" << endl;
        return;
    }
    reflashVisited();
    cout << "深度优先搜索序列:" << endl;
    DFSRecursive(start);
    cout << endl;
};

int main() {
    int i = 0;
    Graphlnk<int> MyGraph;
    while(1)
    {
        cout << "第" << ++i << "次:" << endl;
        MyGraph.input();
        int startPoint;
        cout << "输入出发点: ";
        cin >> startPoint;
        MyGraph.BFS(startPoint);
        MyGraph.DFS(startPoint);
        cout << endl;
    }
    return 0;
}