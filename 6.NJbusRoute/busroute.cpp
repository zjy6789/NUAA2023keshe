#include <iostream>
#include <fstream>
#include <string.h>
#define MAX_R 800
#define MAX_V 7000
using namespace std;
typedef struct Route //一条公交线路 
{
	int station[MAX_V];		// 每条路线站点数组 
	int sum;				// 站点总数 
	Route():sum(0){}
}Route;

typedef struct Station //一个站点 
{
	int Route[MAX_R];		// 每个站点所属的路线
	int sum;				// 路线总数 
	Station():sum(0){}
}Station;

typedef struct ArcNode 
{
	int adjvex;				// 该边的终点编号
	int path;				// 该边所属的路线
	int weight;				// 该边的权值
	ArcNode* next;			// 指向下一条边的权值 
}ArcNode;

typedef struct VexNode 
{
	ArcNode* firstarc;		// 指向第一条与该顶点有关的边的指针 
}VexNode;

typedef struct 
{
	VexNode vexlist[MAX_V];		// 定义邻接表 
	int vexnum, arcnum;			// 图包含的顶点数和边的个数 
	int type;					// 图的种类标记 
}Graph;

//存储所有数据的全局变量
Route R[MAX_R];			// 路线 
Station S[MAX_V];			// 站点总数 
Graph G;//公交线路 

void Show()//展示所有线路 
{ 
	for (int i = 0; i < MAX_R; i++) 
	{
		if (R[i].sum == 0) continue;
		cout << "第" << i << "条线路:";
		for (int j = 0; j < R[i].sum; j++) 
		{
			if (j != R[i].sum - 1)	cout << R[i].station[j] << "->";
			else cout << R[i].station[j] << endl;
		}
	}
}

//按照路线和站点来创建图，方便寻找经过最少转车次数的路径 
// 按照邻接表存储图，方便寻找经过最少站点的路径  
void CreateGraph()
{
	fstream file;
	file.open("3_南京市公交线路_17270条.txt", ios::in);
	while (!file.is_open()) 
	{
		cout << "文件打开失败!\n";
		exit(0);
	}
	int n;								// n为文件中数据总数 
	int total = 0;						// total为路线的最大值 

	int pre_Route = -1;				// 前一个所属路线
	int pre_id;							// 前一个的编号
	int max_vex = 0;					// 顶点的最大编号 
	int max_arc = 0;					// 边的个数 
	for (int i = 0; i < MAX_V; i++) 
	{	// 初始化邻接表 
		G.vexlist[i].firstarc = NULL;
	}
	G.type = 1;							// 图的类型为无向图

	file >> n;
	for (int i = 1; i <= n; i++) 
	{
		int r ,num  ,id ; 
		file >> r >> num >> id;
		if (r != total) 
		{
			total++;
		}
                //对路线与站点的处理		
				//将信息存储到路线中 
		R[r].station[num] = id;
		R[r].sum++;
		// 将信息存储到站点中 
		int k = S[id].sum;
		S[id].Route[k] = r;
		S[id].sum++;
		//////////////////对邻接表的处理 
				// 更新最大站点的编号 
		if (max_vex < id)
			max_vex = id;

		if (pre_Route == r) {				// 如果它的上一个站点所属的路线与当前站点一样，则说明两个站点有边 
			//			max_arc++;
			max_arc += 2;					// 存储的边数+2 
			ArcNode* p = new ArcNode;
			p->adjvex = id;
			p->path = r;
			p->next = G.vexlist[pre_id].firstarc;
			G.vexlist[pre_id].firstarc = p;
			// 无向图对称化 
			ArcNode* q = new ArcNode;
			q->adjvex = pre_id;
			q->path = r;
			q->next = G.vexlist[id].firstarc;
			G.vexlist[id].firstarc = q;
		}
		pre_Route = r;
		pre_id = id;
	}
	file.close();
	G.vexnum = max_vex;
	G.arcnum = max_arc;
}
typedef struct RNode {
	//	int line;		// 当前的线路
	int pre_line;	// 上一条线路
	int id;			// 当前线路从哪儿开始遍历的id 
	//	int start;
	//	int end;
	//	int direction; 
}RNode;
RNode back[MAX_R];		// 对最小转乘结果的回溯 


// 创建优先队列 
typedef struct ElemType {
	int data;			// 信息 
	int height;			// 深度 
}ElemType;

typedef struct Node {
	ElemType data;
	Node* next;
}Node; // 队列节点

class Queue { // 一个队列类
	Node* front;
	Node* rear;
public:
	Queue()
	{
		front = rear = new Node;
		front->next = NULL;
	}
	~Queue()
	{
		Node* p = front;
		while (p) {
			front = p->next;
			delete p;
			p = front;
		}
		front = rear = NULL;
	}
	void EnQueue(ElemType e) // 入队, 深度小的排在前面 
	{
		Node* s = new Node;
		s->data = e;
		/*		s->next = NULL;
				rear->next = s;
				rear = s;
		*/
		Node* pre = front;
		Node* p = front->next;
		while (p) 
		{
			if (p->data.height > s->data.height) {
				break;
			}
			else 
			{
				pre = p;
				p = p->next;
			}
		}
		pre->next = s;
		s->next = p;
		if (p == NULL) rear = s;
	}
	ElemType DeQueue() // 出队
	{
		if (front == rear) 
		{
			cout << "队列已空!\n";
			exit(0);
		}
		Node* p = front->next;
		ElemType e = p->data;
		front->next = p->next;
		if (p == rear) rear = front;
		delete p;
		return e;
	}
	ElemType GetHead() // 获取队头元素
	{
		if (front == rear) 
		{
			cout << "队列已空!\n";
			exit(0);
		}
		else return front->next->data;
	}
	bool Empty() // 判断队是否为空
	{
		if (front == rear) return true;
		else return false;
	}
};

void LeastBuses(int start, int end)
{// 找最小转乘的路线 
	int visited[MAX_R] = { 0 };					// 记录该路线有没有被访问过 
	int result = -1;								// 存储换乘数目 
	Queue Q;
	// 初始化操作 
	for (int i = 0; i < S[end].sum; i++) 
	{		// 将终点所属的路线全部入队 
		int j = S[end].Route[i];
		Q.EnQueue({ j, 1 });
		back[j].id = end;
		back[j].pre_line = -1;
	}
	while (!Q.Empty()) 
	{
		ElemType now = Q.DeQueue();
		int cur = now.data;
		if (visited[cur] == 1) continue;
		//cout <<" &&&&&&&&&&" << cur <<" %%%%%%%%%%" <<now.height<< endl;
		visited[cur] = 1;						// 记录当前线路 
		int sum1 = R[cur].sum;
		for (int i = 0; i < sum1; i++) 
		{		// 开始遍历当前线路的每个站点 
			int j = R[cur].station[i];			// j为站点 

			//cout << "**" << cur << " " << j << endl;

			if (j == start) 
			{					// 若为终点，回溯遍历输出该路线 
				int privok = back[cur].id;		// 结束输出的数值 
				int pre_line = back[cur].pre_line;				// 上一个路线 
				int begin = start;								// begin为开始输出的数值 
				int p_seq = 0;									// 结束输出的编号	
				int b_seq = 0;									// 开始输出的编号 
				// 从开始到结束输出当前路线，输出结束后，返回上一条路线，继续输出 
				while (cur != -1) 
				{
					// 先遍历一遍该路线，找到数值对应的编号		
					for (int l = 0; l < R[cur].sum; l++) 
					{
						if (R[cur].station[l] == privok) 
						{
							p_seq = l;
						}
						if (R[cur].station[l] == begin) 
						{
							b_seq = l;
						}
					}
					// 输出路线 
					if (b_seq < p_seq) 
					{
						for (int l = b_seq; l <= p_seq; l++) 
						{
							cout << cur << " " << l << " " << R[cur].station[l] << endl;
						}
					}
					else 
					{
						for (int l = b_seq; l >= p_seq; l--) 
						{
							cout << cur << " " << l << " " << R[cur].station[l] << endl;
						}
					}
					if (pre_line != -1) cout << "从" << cur << "换乘到" << pre_line << endl;
					// 返回上一条路线 
					begin = privok;
					cur = pre_line;
					privok = back[cur].id;
					pre_line = back[cur].pre_line;
					result++; 
				}
				cout<<"共换乘"<<result<<"次"<<endl;
				return;
			}

			int sum2 = S[j].sum;				// 遍历该站点所属的线路 
			for (int k = 0; k < sum2; k++) 
			{
				int r = S[j].Route[k];			// r为线路 
				ElemType temp;
				temp.data = r;
				temp.height = now.height + 1;
				if (visited[r] == 0) 
				{
					int ii = 1;
				}
				if (visited[r] == 0 && back[r].id == 0) 
				{
					back[r].pre_line = cur;		// r这条线路的上一条线路为本线路cur 
					back[r].id = j;				// 并且关联起这两条线路的是站点j
					Q.EnQueue(temp);				// 下次遍历r这条线路				
				}
			}


		}
	}
}

//从起点经过最少站点到达终点 
typedef struct Result {
	//	int seq;	// 在该路线中的编号
	int id;		// 编号
	int way;	// 所属路线
	int height; // 高度
	int pre;	// 上一个
}Result;

Result back2[MAX_V];						//保存当初结果，从起点回溯到终点 
int visited[MAX_V];							// 记录该站点是否访问过 

void LeastStations(int start, int end)
{// 按照经过站点最少进行排序
	int finished = 0;
	Queue Q2;
	// 将终点信息赋给回溯数组 
	back2[end].height = 1;
	back2[end].id = end;
	back2[end].way = S[end].Route[0];
	back2[end].pre = -1;
	// 将终点入队 
	ElemType cur;
	cur.data = end;
	cur.height = 1;
	int result = 1;
	Q2.EnQueue(cur);
	visited[cur.data] = 1;
	while (!Q2.Empty() && !finished) 
	{
		cur = Q2.DeQueue();

		if (cur.data == start) 
		{											// 遍历结束 
			finished = 1;
			break;
		}
		ArcNode* p = G.vexlist[cur.data].firstarc;							// 遍历当前站点相邻的站点 
		while (p) 
		{
			int in = p->adjvex;												// 处理它的邻居节点
			if (visited[in] != 1) 
			{											// 邻居节点未被遍历过 
				back2[in].way = p->path;
				back2[in].height = back2[cur.data].height + 1;
				back2[in].id = in;
				back2[in].pre = cur.data;
				Q2.EnQueue({ in, cur.height + 1 });
				visited[in] = 1;
			}
			p = p->next;
		}
	}
	if (finished) 
	{
		Result c = back2[start];
		int f = back2[start].pre;
		while (f != -1) 
		{
			cout << c.way << " " << c.id << endl;
			c = back2[f];
			f = c.pre;
			result++;
		}
		cout << c.way << " " << c.id << endl;
		cout<<"共经过了"<<result<<"个站点"<<endl;
	}
	else 
	{
		cout << "无路径!"<<endl ;
	}
}
int main()
{
	CreateGraph();
	cout << "是否需要输出所有路线图：YES or NO"<<endl ;
	string choice ;
	cin >> choice ;
	if(choice == "YES")  Show();
	while (1) 
	{
		cout << "请输入起点站(输入-100结束):" ;
		int start, end;
		cin >> start;
		if (start == -100) break; 
		if(start > 6584 || start <= 0)
		{
			cout << "查无此站！" << endl ; 
			break ;
		 } 
		cout << "请输入终点站(输入-100结束):";
		cin >> end;
		if (end == -100) break; 
		if(end > 6584 || end <= 0)
		{
			cout << "查无此站！" << endl ; 
			break ;
		 } 
		cout << "----------------------转车次数最少的乘车路线-----------------------\n";
		LeastBuses(start, end);
		cout << "----------------------经过站点最少的乘车路线-------------------\n";
		LeastStations(start, end);
		for (int i = 0; i < MAX_R; i++)  
		{
			back[i].id = back[i].pre_line = 0;

		}
		for (int i = 0; i < MAX_V; i++) 
		{
			back2[i].height = back2[i].id = back2[i].pre = back2[i].way = 0;
			visited[i] = 0;
		}
	}
	system("pause");
	return 0;
}