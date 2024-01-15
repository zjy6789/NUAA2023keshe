#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct vex
{
    int code;      // ������
    int cost = 0;  // �����ڶ���֮��ıߵ�Ȩֵ
    vex* next = nullptr;  // ָ����һ�����ڶ����ָ��
} vex;

typedef struct Graph
{
    int vexnum;     // ������
    int arcnum;     // ����
    vex vexs[1001]; // �������飬�±��1��ʼ
} Graph;

// ����ߵĽṹ��
struct Edge {
    int start;
    int end;
    int cost;

    // ���ձߵ�Ȩֵ��������
    bool operator<(const Edge& other) const {
        return cost < other.cost;
    }
};

// ���岢�鼯�������ж����������Ƿ���ͬһ����ͨ�����У�
struct UnionFind {
    vector<int> parent;

    UnionFind(int size) {
        parent.resize(size);
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }

    // ���Ҹ��ڵ�
    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    // �ϲ���������
    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootX] = rootY;
        }
    }
};

// ��³˹�����㷨����С������
void kruskal(Graph& g) {
    // �����бߴ洢��һ��������
    vector<Edge> edges;
    for (int i = 1; i <= g.vexnum; ++i) {
        for (vex* p = g.vexs[i].next; p != nullptr; p = p->next) {
            if (i < p->code) { // �����ظ���ӱ�
                edges.push_back({i, p->code, p->cost});
            }
        }
    }

    // �Ա߰�Ȩֵ��������
    sort(edges.begin(), edges.end());

    // ��ʼ�����鼯
    UnionFind uf(g.vexnum + 1);

    // �����С�������ı�
    int sum=0;
    cout<<"Kruscal�㷨��"<<endl;
    for (const Edge& edge : edges) {
        int rootStart = uf.find(edge.start);
        int rootEnd = uf.find(edge.end);
        if (rootStart != rootEnd) {
            cout << edge.start << "-" << edge.end << " Ȩֵ��" << edge.cost << endl;
            sum+=edge.cost;
            uf.unionSets(edge.start, edge.end);
        }
    }
    cout<<"��С������Ȩ�أ�"<<sum<<endl;
}

int main() {
    Graph g;
    // ��ȡͼ����
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

    // ʹ�ÿ�³˹�����㷨����С������
    kruskal(g);

    system("pause");
    return 0;
}
