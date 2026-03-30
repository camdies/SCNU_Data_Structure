//         For homework 5.1
//*****    be care for using GBK coding    *****//
//*****    @author Cairenbin
//*****    Date: 2025.11.25 Tuesday
//5.1.输入邻接矩阵(不带权的有向图或无向图)为图的存储结构，输出广度优先和深度优先遍历序列
#include <iostream>
#include <queue>

using namespace std;

#define MAX_SIZE 100
class Graph {
protected:
    int n;  //节点个数
    int graph[MAX_SIZE][MAX_SIZE];
    bool visited[MAX_SIZE];
public:
    Graph() {
        for (int i = 0; i < MAX_SIZE; i++)
        {
            for (int j = 0; j < MAX_SIZE; j++)
            {
                graph[i][j] = 0;
            }
        }
    };

    void input() {
        cout << "输入节点个数: ";
        cin >> n;
        if(n == -1) {
            cout << "程序结束!" << endl;
            exit(0);
        }
        if(n < 0) {return;}
        cout << "输入邻接矩阵每一行的数据: " << endl;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                cin >> graph[i][j];
            }
        }
    };

    void reflashVisited() {
        for(int i = 0; i < n; ++i) {
            visited[i] = false;
        }
    };

    //广度优先搜索遍历输出, 第一行默认0号节点
    void BFSBase(int start) {
        queue<int> q;
        q.push(start);
        visited[start] = true; //标记起始节点已访问
        while(!q.empty()) {
            int point = q.front();
            q.pop();
            cout << point << " ";
            for(int i = 0; i < n; ++i) {
                if(graph[point][i] == 1 && !visited[i]) { //找到未访问邻接节点
                    q.push(i); //入队
                    visited[i] = true;
                }
            }
        }
    };
    void BFS(int start) {
    if(start < 0 || start >= n) {
        cout << "非法起始节点!" << endl;
        return;
    }
    reflashVisited();
    cout << "广度优先遍历序列:" << endl;
    BFSBase(start);
    cout << endl;
    };

    //深度优先搜索遍历输出, 第一行默认0号节点
    void DFSRecursive(int start) {
        cout << start << " ";
        visited[start] = true;
        for (int i = 0; i < n; i++)
        {
            if(graph[start][i] == 1 && !visited[i]) {
                DFSRecursive(i);
            }
        }
    };
    void DFS(int start) {
        if(start < 0 || start >= n) {
            cout << "非法起始节点! " << endl;
            return;
        }
        reflashVisited();
        cout << "深度优先搜索序列:" << endl;
        DFSRecursive(start);
        cout << endl;
    };
};

int main() {
    int count = 0;
    Graph MyGraph;
    while(1)
    {
        cout << "第" << ++count << "次:" << endl;
        MyGraph.input();
        int startPoint;
        cout << "输入出发点:";
        cin >> startPoint;
        MyGraph.BFS(startPoint); //广度优先
        MyGraph.DFS(startPoint); //深度优先
        cout << endl;
    }
    return 0;
}