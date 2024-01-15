#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct vex
{
    int code;      // 顶点编号
    int cost = 0;  // 与相邻顶点之间的边的权值
    vex* next = nullptr;  // 指向下一个相邻顶点的指针
} vex;

typedef struct Graph
{
    int vexnum;     // 顶点数
    int arcnum;     // 边数
    vex vexs[1001]; // 顶点数组，下标从1开始
} Graph;

// 定义边的结构体
struct Edge {
    int start;
    int end;
    int cost;

    // 按照边的权值进行排序
    bool operator<(const Edge& other) const {
        return cost < other.cost;
    }
};

// 定义并查集（用于判断两个顶点是否在同一个连通分量中）
struct UnionFind {
    vector<int> parent;

    UnionFind(int size) {
        parent.resize(size);
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }

    // 查找根节点
    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    // 合并两个集合
    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootX] = rootY;
        }
    }
};

// 克鲁斯卡尔算法求最小生成树
void kruskal(Graph& g) {
    // 将所有边存储在一个数组中
    vector<Edge> edges;
    for (int i = 1; i <= g.vexnum; ++i) {
        for (vex* p = g.vexs[i].next; p != nullptr; p = p->next) {
            if (i < p->code) { // 避免重复添加边
                edges.push_back({i, p->code, p->cost});
            }
        }
    }

    // 对边按权值进行排序
    sort(edges.begin(), edges.end());

    // 初始化并查集
    UnionFind uf(g.vexnum + 1);

    // 输出最小生成树的边
    int sum=0;
    cout<<"Kruscal算法："<<endl;
    for (const Edge& edge : edges) {
        int rootStart = uf.find(edge.start);
        int rootEnd = uf.find(edge.end);
        if (rootStart != rootEnd) {
            cout << edge.start << "-" << edge.end << " 权值：" << edge.cost << endl;
            sum+=edge.cost;
            uf.unionSets(edge.start, edge.end);
        }
    }
    cout<<"最小生成树权重："<<sum<<endl;
}

int main() {
    Graph g;
    // 读取图数据
    cin >> g.vexnum >> g.arcnum;
    for (int i = 1; i <= g.arcnum; i++) {
        int j, k, w;
        vex* p;

        cin >> j >> k >> w;

        p = new vex;
        p->code = k;
        p->cost = w;
        p->next = g.vexs[j].next;
        g.vexs[j].next = p;

        p = new vex;
        p->code = j;
        p->cost = w;
        p->next = g.vexs[k].next;
        g.vexs[k].next = p;
    }

    // 使用克鲁斯卡尔算法求最小生成树
    kruskal(g);

    system("pause");
    return 0;
}
