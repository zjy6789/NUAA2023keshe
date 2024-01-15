#include<iostream>
#include<vector>

using namespace std;

#define MAX_V 20// 最大顶点数目

typedef struct Graph
{
    int vexnum,arcnum; // 图包含的顶点数与边的个数
    int arcs[MAX_V][ MAX_V]; // 邻接矩阵
}Graph;

void Init_undiNet(Graph&G)//无向网创建
{
    for(int i=1; i<=G.vexnum; i++ )
        for(int j=1; j<=G.vexnum; j++ )
            G.arcs[i][j]=INT_MAX; // 邻接矩阵初始化，所有元素初始值为极大值
    int i,j,w;
    for(int k=0; k<G.arcnum; k++ )
    {
        cin>>i>>j>>w; // 输入一条边，i、j 表示边的两个顶点的编号和边的权值
        G.arcs[i][j]=w; // 为邻接矩阵的相应元素赋值
        G.arcs[j][i]=w; // 无向图中存在一条对称的边也赋值
    }
}

int FirstAdjVex(Graph G,int v)//获取图中点v的第一个邻接点
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

int NextAdjVex(Graph G,int v,int w)//获取v相对于w的下一个邻接点
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

//从当前点开始深度优先搜索所有可达n点的路径
void dfs_index(Graph G,int index,bool *is_visited,int &min_day,vector<int> &path_cost)
{
    if(index==G.vexnum)//若已到达第n个枢纽，则计算此条路径的最少天数
    {
        int max_t=0;
        for(int i:path_cost)
        {
            if(i>max_t) max_t=i;
        }
        //若该路径的最少天数比此前所有路径的最少天数都少，更新最少天数
        if(min_day>max_t) 
            min_day=max_t;//若该路径的最少天数比此前所有路径的最少天数都少，更新最少天数
        return;
    }

    int next=FirstAdjVex(G,index);
    while(next!=0)
    {
        // 遍历起始点的所有邻接点，若邻接点已经被访问过，那么 p 继续向后遍历；
        // 否则以当前邻接点为新的起始点递归进行深度优先遍历
        if(is_visited[next]==false)
        {
            is_visited[next]=true;//标记已访问的点
            path_cost.push_back(G.arcs[index][next]);//将该条边的权值入栈
            dfs_index(G,next,is_visited,min_day,path_cost);
            is_visited[next]=false;//恢复该点未访问
            path_cost.pop_back();//将该边出栈，并访问下一个点
            
        }
        next=NextAdjVex(G,index,next);
    }
}

int Find_dfs(Graph G)//调用深度优先搜素来寻找所需天数最少的路径
{
    int min_day=INT_MAX;
    bool is_visited[G.vexnum+1]={false};//标记点是否访问过
    vector<int> path_cost;//记录路径的每条边所需天数

    is_visited[1]=1;
    dfs_index(G,1,is_visited,min_day,path_cost);//深度优先搜索寻找最少天数
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