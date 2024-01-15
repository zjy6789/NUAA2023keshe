#include<stdio.h>
#include<stdlib.h>
typedef struct MGraph
{
	//定义图的邻接矩阵形式 
	int arcs[500][500];  //定义图的邻接矩阵 
	int vexnum,arcnum;   //定义图的顶点和边的个数 
}MGraph;
void GraphCreate(MGraph &G)  //创建图 
{
	int vex1,vex2;  
	scanf("%d %d",&G.vexnum,&G.arcnum);
	//初始化邻接矩阵，将其所有元素赋值为-1表示互不可达 
	for(int i=1;i<=G.vexnum;i++)
	{
		for(int j=1;j<=G.vexnum;j++)
		{
			G.arcs[i][j]=-1;
		}
	}
	for(int i=0;i<G.arcnum;i++)
	{
		 //根据输入的vex1,vex2为一条边的两个顶点的编号 
		scanf("%d %d",&vex1,&vex2);
		G.arcs[vex1][vex2]=1; //为邻接矩阵的相应元素赋值，1表示互相可达 
		G.arcs[vex2][vex1]=1;  //题目中为无向图，所以为无向图中的一条对称的边赋值 
	}
}
float Dijkstra(MGraph G,int s) //返回由题目中的公式求得的Cc值 
{
	//根据输入的顶点，用Dijkstra算法求得该顶点到其他所有顶点经过的边的个数 
	//定义dist数组，dist[i]表示从s号顶点到顶点i的最短距离
	//定义path数组，path[i]=j表示从s号顶点到达顶点i会经过顶点j
	//定义flag数组，flag[i]表示顶点i的选中状态，1表示选中，0表示未选中 
	int dist[G.vexnum+1];
	int path[G.vexnum+1];
	int flag[G.vexnum+1];
	dist[s]=0; //将起始顶点的dist设为0 
	for(int i=1;i<=G.vexnum;i++)  //根据邻接矩阵，将三个数组根据每个顶点进行初始化 
	{
		if(i!=s) dist[i]=G.arcs[s][i]; //如果该顶点不是起始点本身，将该点的距离赋值给dist函数(包括1和-1) 
		if(dist[i]!=-1) path[i]=s;     //如果dist值为1，表示起始点可达这个点，那么将path的值设为起始点 
		else path[i]=-1;  //否则，表示起始点不可达这个点 ，那么将path的值设为-1 
		flag[i]=0;    //并将所有顶点的选中状态设为0 
	}
	flag[s]=1; //将起始点设置为被选中状态 
	int min,pos_note; //定义min用于找到dist数组中的最小值，pos_note用于找到最小min值对应的顶点编号 
	for(int j=1;j<=G.vexnum;j++) 
	{
		min=1000;  //1000表示为无限远 
		for(int i=1;i<=G.vexnum;i++) //在flag值为0且dist值为正的元素中找到一个最小值 
		{
			if(dist[i]!=-1&&flag[i]==0&&min>dist[i])
			{
				min=dist[i];
				pos_note=i;
			}
		}
		flag[pos_note]=1;  //将找到的min最小的顶点的访问状态更改为1
		for(int k=1;k<=G.vexnum;k++) //将找到的这个顶点与其他顶点判断是否修改数组 
		{
			if(flag[k]==0) //该顶点未被访问过 
			{
				if(dist[k]==-1&&G.arcs[pos_note][k]!=-1) //找到一个顶点，原来不可到达，现在可到达 
				{
					dist[k]=dist[pos_note]+G.arcs[pos_note][k];
					path[k]=pos_note;
				}
				if(dist[k]!=-1&&G.arcs[pos_note][k]==-1) continue;  //找到一个顶点，原来可到达，现在不可到达
				if(dist[pos_note]+G.arcs[pos_note][k]<dist[k]) //找到一个顶点，原来可到达，现在也可到达，但比之前的距离更近 
				{
					dist[k]=dist[pos_note]+G.arcs[pos_note][k];
					path[k]=pos_note;
				 } 
			}
		}
	}
	float sum=0; //用于求得某个顶点到其余所有节点的最短距离 
	for(int i=1;i<=G.vexnum;i++)
	sum=sum+dist[i];
	float Cc=(G.vexnum-1)/sum; //根据公式求得Cc值 
	return Cc;
}
int main()
{
	MGraph G;  //定义图 
	GraphCreate(G);   //创建图 
	int num,node;   //要求输入的需要计算紧密度中心性的结点个数，以及每个结点的编号 
	scanf("%d",&num);
	int arr1[num];  //用于存储每个需要计算的结点编号 
	float arr2[num];  //用于存储每个需要计算的结点的Cc值 
	for(int i=0;i<num;i++) //输入结点编号，存储在arr1数组内，并调用Dijkstra函数将求得的结果存储在arr2数组内 
	{
		scanf("%d",&node);
		arr1[i]=node;
		arr2[i]=Dijkstra(G,node);
	}
	for(int i=0;i<num;i++)  //按要求输出结果 
	printf("Cc(%d) = %.2f\n",arr1[i],arr2[i]);
	system("pause");
	return 0;
}

/*
5 8
1 2
1 3
1 4
2 3
3 4
4 5
2 5
3 5
2 4 3

Cc(4) = 0.80  
Cc(3) = 1.00
*/