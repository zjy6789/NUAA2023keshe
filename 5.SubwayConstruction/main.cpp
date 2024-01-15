#include<iostream>
#include<vector>

using namespace std;

#define MAX_V 20// ��󶥵���Ŀ

typedef struct Graph
{
    int vexnum,arcnum; // ͼ�����Ķ�������ߵĸ���
    int arcs[MAX_V][ MAX_V]; // �ڽӾ���
}Graph;

void Init_undiNet(Graph&G)//����������
{
    for(int i=1; i<=G.vexnum; i++ )
        for(int j=1; j<=G.vexnum; j++ )
            G.arcs[i][j]=INT_MAX; // �ڽӾ����ʼ��������Ԫ�س�ʼֵΪ����ֵ
    int i,j,w;
    for(int k=0; k<G.arcnum; k++ )
    {
        cin>>i>>j>>w; // ����һ���ߣ�i��j ��ʾ�ߵ���������ı�źͱߵ�Ȩֵ
        G.arcs[i][j]=w; // Ϊ�ڽӾ������ӦԪ�ظ�ֵ
        G.arcs[j][i]=w; // ����ͼ�д���һ���ԳƵı�Ҳ��ֵ
    }
}

int FirstAdjVex(Graph G,int v)//��ȡͼ�е�v�ĵ�һ���ڽӵ�
{
    int i=1;
    for(i;i<=G.vexnum;i++)
    {
        if(G.arcs[v][i]<INT_MAX)
        {
            return i;
        }
    }
    return 0;
}

int NextAdjVex(Graph G,int v,int w)//��ȡv�����w����һ���ڽӵ�
{
    int i=w+1;
    for(i;i<=G.vexnum;i++)
    {
        if(G.arcs[v][i]<INT_MAX)
        {
            return i;
        }
    }
    return 0;
}

//�ӵ�ǰ�㿪ʼ��������������пɴ�n���·��
void dfs_index(Graph G,int index,bool *is_visited,int &min_day,vector<int> &path_cost)
{
    if(index==G.vexnum)//���ѵ����n����Ŧ����������·������������
    {
        int max_t=0;
        for(int i:path_cost)
        {
            if(i>max_t) max_t=i;
        }
        //����·�������������ȴ�ǰ����·���������������٣�������������
        if(min_day>max_t) 
            min_day=max_t;//����·�������������ȴ�ǰ����·���������������٣�������������
        return;
    }

    int next=FirstAdjVex(G,index);
    while(next!=0)
    {
        // ������ʼ��������ڽӵ㣬���ڽӵ��Ѿ������ʹ�����ô p ������������
        // �����Ե�ǰ�ڽӵ�Ϊ�µ���ʼ��ݹ����������ȱ���
        if(is_visited[next]==false)
        {
            is_visited[next]=true;//����ѷ��ʵĵ�
            path_cost.push_back(G.arcs[index][next]);//�������ߵ�Ȩֵ��ջ
            dfs_index(G,next,is_visited,min_day,path_cost);
            is_visited[next]=false;//�ָ��õ�δ����
            path_cost.pop_back();//���ñ߳�ջ����������һ����
            
        }
        next=NextAdjVex(G,index,next);
    }
}

int Find_dfs(Graph G)//�����������������Ѱ�������������ٵ�·��
{
    int min_day=INT_MAX;
    bool is_visited[G.vexnum+1]={false};//��ǵ��Ƿ���ʹ�
    vector<int> path_cost;//��¼·����ÿ������������

    is_visited[1]=1;
    dfs_index(G,1,is_visited,min_day,path_cost);//�����������Ѱ����������
    return min_day;
}



int main()
{

    Graph g;
    int n,m;
    cin>>n>>m;
    g.vexnum=n;
    g.arcnum=m;
    Init_undiNet(g);
    int min=Find_dfs(g);
    cout<<min<<endl;
    system("pause");
    return 0;
}