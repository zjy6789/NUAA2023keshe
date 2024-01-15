#include<stdio.h>
#include<stdlib.h>
typedef struct MGraph
{
	//����ͼ���ڽӾ�����ʽ 
	int arcs[500][500];  //����ͼ���ڽӾ��� 
	int vexnum,arcnum;   //����ͼ�Ķ���ͱߵĸ��� 
}MGraph;
void GraphCreate(MGraph &G)  //����ͼ 
{
	int vex1,vex2;  
	scanf("%d %d",&G.vexnum,&G.arcnum);
	//��ʼ���ڽӾ��󣬽�������Ԫ�ظ�ֵΪ-1��ʾ�����ɴ� 
	for(int i=1;i<=G.vexnum;i++)
	{
		for(int j=1;j<=G.vexnum;j++)
		{
			G.arcs[i][j]=-1;
		}
	}
	for(int i=0;i<G.arcnum;i++)
	{
		 //���������vex1,vex2Ϊһ���ߵ���������ı�� 
		scanf("%d %d",&vex1,&vex2);
		G.arcs[vex1][vex2]=1; //Ϊ�ڽӾ������ӦԪ�ظ�ֵ��1��ʾ����ɴ� 
		G.arcs[vex2][vex1]=1;  //��Ŀ��Ϊ����ͼ������Ϊ����ͼ�е�һ���ԳƵı߸�ֵ 
	}
}
float Dijkstra(MGraph G,int s) //��������Ŀ�еĹ�ʽ��õ�Ccֵ 
{
	//��������Ķ��㣬��Dijkstra�㷨��øö��㵽�������ж��㾭���ıߵĸ��� 
	//����dist���飬dist[i]��ʾ��s�Ŷ��㵽����i����̾���
	//����path���飬path[i]=j��ʾ��s�Ŷ��㵽�ﶥ��i�ᾭ������j
	//����flag���飬flag[i]��ʾ����i��ѡ��״̬��1��ʾѡ�У�0��ʾδѡ�� 
	int dist[G.vexnum+1];
	int path[G.vexnum+1];
	int flag[G.vexnum+1];
	dist[s]=0; //����ʼ�����dist��Ϊ0 
	for(int i=1;i<=G.vexnum;i++)  //�����ڽӾ��󣬽������������ÿ��������г�ʼ�� 
	{
		if(i!=s) dist[i]=G.arcs[s][i]; //����ö��㲻����ʼ�㱾�����õ�ľ��븳ֵ��dist����(����1��-1) 
		if(dist[i]!=-1) path[i]=s;     //���distֵΪ1����ʾ��ʼ��ɴ�����㣬��ô��path��ֵ��Ϊ��ʼ�� 
		else path[i]=-1;  //���򣬱�ʾ��ʼ�㲻�ɴ������ ����ô��path��ֵ��Ϊ-1 
		flag[i]=0;    //�������ж����ѡ��״̬��Ϊ0 
	}
	flag[s]=1; //����ʼ������Ϊ��ѡ��״̬ 
	int min,pos_note; //����min�����ҵ�dist�����е���Сֵ��pos_note�����ҵ���Сminֵ��Ӧ�Ķ����� 
	for(int j=1;j<=G.vexnum;j++) 
	{
		min=1000;  //1000��ʾΪ����Զ 
		for(int i=1;i<=G.vexnum;i++) //��flagֵΪ0��distֵΪ����Ԫ�����ҵ�һ����Сֵ 
		{
			if(dist[i]!=-1&&flag[i]==0&&min>dist[i])
			{
				min=dist[i];
				pos_note=i;
			}
		}
		flag[pos_note]=1;  //���ҵ���min��С�Ķ���ķ���״̬����Ϊ1
		for(int k=1;k<=G.vexnum;k++) //���ҵ���������������������ж��Ƿ��޸����� 
		{
			if(flag[k]==0) //�ö���δ�����ʹ� 
			{
				if(dist[k]==-1&&G.arcs[pos_note][k]!=-1) //�ҵ�һ�����㣬ԭ�����ɵ�����ڿɵ��� 
				{
					dist[k]=dist[pos_note]+G.arcs[pos_note][k];
					path[k]=pos_note;
				}
				if(dist[k]!=-1&&G.arcs[pos_note][k]==-1) continue;  //�ҵ�һ�����㣬ԭ���ɵ�����ڲ��ɵ���
				if(dist[pos_note]+G.arcs[pos_note][k]<dist[k]) //�ҵ�һ�����㣬ԭ���ɵ������Ҳ�ɵ������֮ǰ�ľ������ 
				{
					dist[k]=dist[pos_note]+G.arcs[pos_note][k];
					path[k]=pos_note;
				 } 
			}
		}
	}
	float sum=0; //�������ĳ�����㵽�������нڵ����̾��� 
	for(int i=1;i<=G.vexnum;i++)
	sum=sum+dist[i];
	float Cc=(G.vexnum-1)/sum; //���ݹ�ʽ���Ccֵ 
	return Cc;
}
int main()
{
	MGraph G;  //����ͼ 
	GraphCreate(G);   //����ͼ 
	int num,node;   //Ҫ���������Ҫ������ܶ������ԵĽ��������Լ�ÿ�����ı�� 
	scanf("%d",&num);
	int arr1[num];  //���ڴ洢ÿ����Ҫ����Ľ���� 
	float arr2[num];  //���ڴ洢ÿ����Ҫ����Ľ���Ccֵ 
	for(int i=0;i<num;i++) //�������ţ��洢��arr1�����ڣ�������Dijkstra��������õĽ���洢��arr2������ 
	{
		scanf("%d",&node);
		arr1[i]=node;
		arr2[i]=Dijkstra(G,node);
	}
	for(int i=0;i<num;i++)  //��Ҫ�������� 
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