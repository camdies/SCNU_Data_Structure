//         For homework 6.1
//*****    be care for using GBK coding    *****//
//*****    @author Cairenbin
//*****    Date: 2025.11.25 Tuesday
//6.1.以邻接矩阵(非负整数)为有向带权图的存储结构，实现求从一源点到其他各个结点的最短路径
#include <iostream>
#include <queue>

using namespace std;

#define MAX_SIZE 100
const int INF = 1000000000;
class Graph {
protected:
    int n;  //节点个数
    int graph[MAX_SIZE][MAX_SIZE];
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

    void Dijkstra(int start) {
        int dist[MAX_SIZE];
        bool visit[MAX_SIZE] = {false};
        for(int i = 0; i < n; ++i) {
            if(i == start) { dist[i] = 0; }
            else if (graph[start][i] > 0) { dist[i] = graph[start][i]; }
            else dist[i] = INF;
        }
        visit[start] = true;
        for(int j = 1; j < n; ++j) { //起点已经访问，直接从1开始--邻接矩阵
            int minDist = INF;
            int u = -1; // 找到未访问节点中距离起点最近的节点
            for(int i = 0; i < n; ++i) {
                if(!visit[i] && dist[i] < minDist) {
                    minDist = dist[i];
                    u = i;
                }
            }
            if(u == -1) break; //剩下的节点都不可到达
            visit[u] = true;
            for(int v = 0; v < n; ++v) {
                if(!visit[v] && graph[u][v] > 0 && dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v]; //检查距离是否小于基准距离，否则用基准距离代替
                }
            }
        }
        cout << "从起点" << start << "到各个节点的最短路径值:" << endl;
        for(int i = 0; i < n; ++i) {
            if(i == start) continue; //跳过起点自己
            if(dist[i] < INF) {
                cout << "到 " << i << " 的最短路径值: " << dist[i] << endl;
            } else {
                cout << "结点" << i << "不可到达" << endl;
            }
        }
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
        MyGraph.Dijkstra(startPoint);
        cout << endl;
    }
    return 0;
}
/*
1.写出以邻接矩阵为有向带权图的存储结构，实现求从一源点到其他各个结点的最短路径。
输入：
（1）图的结点总数，以输入 -1 来结束整个程序的运行。
（2）邻接矩阵的每行数据（非负整数）
（3）输入源点对应的结点序号
输出：
 （1）从源点到其他各个结点的最短路径值

*/