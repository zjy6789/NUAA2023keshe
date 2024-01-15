#include<iostream>
#include<vector>
using namespace std;

typedef struct Prim_aux
{
    int vexcode;  // 记录与当前顶点连接的最小权值的顶点的编号
    int lowcost;  // 记录与当前顶点连接的最小权值
    bool tag;     // 标记当前顶点是否已加入最小生成树
} prim_aux;

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

// 在最小生成树的候选集合中，找到权值最小的边
int min(vector<prim_aux> &aux, int num)
{
    int m = 0;
    for (int i = 2; i <= num; i++)
    {
        if (aux[i].tag == true)
            continue;
        else if (m == 0)
            m = i;
        else if (aux[m].lowcost > aux[i].lowcost)
        {
            m = i;
        }
    }
    return m;
}

// Prim算法构建最小生成树
int prim(Graph g, vector<prim_aux> &aux)
{
    vex *p = g.vexs[1].next;//从一号节点开始
    for (int i = g.vexnum; i >= 1; i--)//初始化辅助数组
    {
        aux[i].vexcode = 1;

        if (p != nullptr && i == p->code)
        {
            aux[i].lowcost = p->cost;
            p = p->next;
        }
        else
            aux[i].lowcost = INT_MAX;

        if (i == 1)
            aux[i].tag = true;
        else
            aux[i].tag = false;
    }
    for (int t = 2; t <= g.vexnum; t++)
    {
        int k = min(aux, g.vexnum);//找到权值最小的边所关联的定点编号
        if (k != 0)
        {
            aux[k].tag = true;//将点加入树中
            vex *p = g.vexs[k].next;
            while (p != nullptr)//更新未加入树的点的最小权值的边
            {
                if (aux[p->code].tag == false && p->cost < aux[p->code].lowcost)
                {
                    aux[p->code].lowcost = p->cost;
                    aux[p->code].vexcode = k;
                }
                p = p->next;
            }
        }
    }

    int sum = 0;//统计并返回最小生成树的权重
    for (int i = 2; i <= g.vexnum; i++)
    {
        sum += aux[i].lowcost;
    }
    return sum;
}



int main()
{
    Graph g;
    cin >> g.vexnum >> g.arcnum;
    vex *p = nullptr, *q = nullptr;
    int j, k, w;

//图数据读取
    for (int i = 1; i <= g.arcnum; i++)
    {
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
    vector<prim_aux> aux(g.vexnum + 1);
    int sum=prim(g, aux);
    cout<<endl<<"Prim算法："<<endl;
    cout<<"所用边："<<endl;
    for(int i=2;i<aux.size();i++)
    {
        cout<<i<<"-"<<aux[i].vexcode<<" 权值："<<aux[i].lowcost<<endl;
    }
    cout<<"最小生成树权重："<<sum<<endl;
    
    system("pause");
    return 0;
}


/*
7 10
1 2 8
1 3 2
1 4 5
2 5 2
2 6 6
3 4 7
4 7 9
5 6 3
5 7 5
6 7 4
*/   //24