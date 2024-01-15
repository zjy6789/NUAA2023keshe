#include<iostream>
#include<vector>
using namespace std;

typedef struct Prim_aux
{
    int vexcode;  // ��¼�뵱ǰ�������ӵ���СȨֵ�Ķ���ı��
    int lowcost;  // ��¼�뵱ǰ�������ӵ���СȨֵ
    bool tag;     // ��ǵ�ǰ�����Ƿ��Ѽ�����С������
} prim_aux;

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

// ����С�������ĺ�ѡ�����У��ҵ�Ȩֵ��С�ı�
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

// Prim�㷨������С������
int prim(Graph g, vector<prim_aux> &aux)
{
    vex *p = g.vexs[1].next;//��һ�Žڵ㿪ʼ
    for (int i = g.vexnum; i >= 1; i--)//��ʼ����������
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
        int k = min(aux, g.vexnum);//�ҵ�Ȩֵ��С�ı��������Ķ�����
        if (k != 0)
        {
            aux[k].tag = true;//�����������
            vex *p = g.vexs[k].next;
            while (p != nullptr)//����δ�������ĵ����СȨֵ�ı�
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

    int sum = 0;//ͳ�Ʋ�������С��������Ȩ��
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

//ͼ���ݶ�ȡ
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
    cout<<endl<<"Prim�㷨��"<<endl;
    cout<<"���ñߣ�"<<endl;
    for(int i=2;i<aux.size();i++)
    {
        cout<<i<<"-"<<aux[i].vexcode<<" Ȩֵ��"<<aux[i].lowcost<<endl;
    }
    cout<<"��С������Ȩ�أ�"<<sum<<endl;
    
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