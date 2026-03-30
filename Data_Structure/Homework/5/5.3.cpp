//         For homework 5.3
//*****    be care for using GBK coding    *****//
//*****    @author Cairenbin
//*****    Date: 2025.11.25 Tuesday
//5.3.邻接矩阵为无向带权图的存储结构，分别实现卡鲁斯卡尔和普里姆求最小生成树
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

    void Kruskal() {
        struct Edge {
            int u, v, w; // u边的起点, v边的终点, w边的权值
        } edges[MAX_SIZE * MAX_SIZE];

        int edgeCount = 0;
        for(int i = 0; i < n; ++i) { //枚举上三角 j>i 矩阵的边
            for(int j = i+1; j < n; ++j) {
                if(graph[i][j] > 0) {
                    edges[edgeCount++] = {i, j, graph[i][j]}; // 记录边
                }
            }
        }

        // 按权值从小到大排序边
        for(int i = 0; i < edgeCount; ++i) {
            int minIdx = i;
            for(int j = i+1; j < edgeCount; ++j) {
                if(edges[j].w < edges[minIdx].w) {
                    minIdx = j;
                }
            }
            if(minIdx != i) {
                Edge temp = edges[i];
                edges[i] = edges[minIdx];
                edges[minIdx] = temp;
            }
        }

        int parent[MAX_SIZE]; // 并查集数组
        for(int i = 0; i < n; ++i) {
            parent[i] = i; // 初始化每个节点自成一个集合
        }
        auto find = [&](int x) { // 查找集合祖先
            while(parent[x] != x) x = parent[x];
            return x;
        };
        cout << "卡鲁斯卡尔求最小生成树的边序列" << endl;
        int cnt = 0, sum = 0; // cnt记录已加入的边数, sum记录总权值
        bool inTree[MAX_SIZE] = {false}; // 记录点是否已加入生成树
        int pointSeq[MAX_SIZE], seqCnt = 0;
        for (int i = 0; i < edgeCount; ++i) {
            int fu = find(edges[i].u), fv = find(edges[i].v); // 找到边的两个端点的集合代表
            if(fu != fv)  {
                cout << "(" << edges[i].u << "," << edges[i].v << ") 权值:" << edges[i].w << endl;
                sum += edges[i].w;
                parent[fu] = fv;
                cnt++;
                // 记录点序列（避免重复）
                if(!inTree[edges[i].u]) {
                    pointSeq[seqCnt++] = edges[i].u;
                    inTree[edges[i].u] = true;
                }
                if(!inTree[edges[i].v]) {
                    pointSeq[seqCnt++] = edges[i].v;
                    inTree[edges[i].v] = true;
                }
                if(cnt == n-1) break;
            }
        }
        cout << "最小生成树的总权值为: " << sum << endl;
        cout << "最小生成树点序列: ";
        for(int i = 0; i < seqCnt; ++i) {
            cout << pointSeq[i] << (i == seqCnt-1 ? "\n" : " ");
        }
    };

    void Prim() {
        int lowcost[MAX_SIZE], pre[MAX_SIZE];
        bool visit[MAX_SIZE] = {false};
        int pointSeq[MAX_SIZE], seqCnt = 0; // 用于记录点序列
        for(int i = 0; i < n; ++i) {
            lowcost[i] = (i == 0) ? 0 : (graph[0][i] > 0 ? graph[0][i] : 1000000000);
            pre[i] = 0;
        }
        visit[0] = true;
        pointSeq[seqCnt++] = 0; // 起点入序列
        int sum = 0;
        cout << "普里姆求最小生成树的边序列" << endl;
        for(int i = 1; i < n; ++i) {
            int minValue = 1000000000;
            int p = -1;
            for(int j = 0; j < n; ++j) {
                if(!visit[j] && lowcost[j] < minValue) {
                    minValue = lowcost[j];
                    p = j;
                }
            }
            if(p == -1) break;
            visit[p] = true;
            pointSeq[seqCnt++] = p; // 新点入序列
            cout << "(" << pre[p] << "," << p << ") 权值:" << lowcost[p] << endl;
            sum += lowcost[p];
            for(int j = 0; j < n; ++j) {
                if(!visit[j] && graph[p][j] > 0 && graph[p][j] < lowcost[j]) {
                    lowcost[j] = graph[p][j];
                    pre[j] = p;
                }
            }
        }
        cout << "最小生成树总权值: " << sum << endl;
        cout << "最小生成树点序列: ";
        for(int i = 0; i < seqCnt; ++i) {
            cout << pointSeq[i] << (i == seqCnt-1 ? "\n" : " ");
        }
    }
};

int main() {
    int i = 0;
    Graph MyGraph;
    while(1)
    {
        cout << "第" << ++i << "次:" << endl;
        MyGraph.input();
        MyGraph.Kruskal();
        MyGraph.Prim();
        cout << endl;
    }
    return 0;
}