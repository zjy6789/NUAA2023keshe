#include <iostream>
#include <fstream>
#include <string.h>
#define MAX_R 800
#define MAX_V 7000
using namespace std;
typedef struct Route //һ��������· 
{
	int station[MAX_V];		// ÿ��·��վ������ 
	int sum;				// վ������ 
	Route():sum(0){}
}Route;

typedef struct Station //һ��վ�� 
{
	int Route[MAX_R];		// ÿ��վ��������·��
	int sum;				// ·������ 
	Station():sum(0){}
}Station;

typedef struct ArcNode 
{
	int adjvex;				// �ñߵ��յ���
	int path;				// �ñ�������·��
	int weight;				// �ñߵ�Ȩֵ
	ArcNode* next;			// ָ����һ���ߵ�Ȩֵ 
}ArcNode;

typedef struct VexNode 
{
	ArcNode* firstarc;		// ָ���һ����ö����йصıߵ�ָ�� 
}VexNode;

typedef struct 
{
	VexNode vexlist[MAX_V];		// �����ڽӱ� 
	int vexnum, arcnum;			// ͼ�����Ķ������ͱߵĸ��� 
	int type;					// ͼ�������� 
}Graph;

//�洢�������ݵ�ȫ�ֱ���
Route R[MAX_R];			// ·�� 
Station S[MAX_V];			// վ������ 
Graph G;//������· 

void Show()//չʾ������· 
{ 
	for (int i = 0; i < MAX_R; i++) 
	{
		if (R[i].sum == 0) continue;
		cout << "��" << i << "����·:";
		for (int j = 0; j < R[i].sum; j++) 
		{
			if (j != R[i].sum - 1)	cout << R[i].station[j] << "->";
			else cout << R[i].station[j] << endl;
		}
	}
}

//����·�ߺ�վ��������ͼ������Ѱ�Ҿ�������ת��������·�� 
// �����ڽӱ�洢ͼ������Ѱ�Ҿ�������վ���·��  
void CreateGraph()
{
	fstream file;
	file.open("3_�Ͼ��й�����·_17270��.txt", ios::in);
	while (!file.is_open()) 
	{
		cout << "�ļ���ʧ��!\n";
		exit(0);
	}
	int n;								// nΪ�ļ����������� 
	int total = 0;						// totalΪ·�ߵ����ֵ 

	int pre_Route = -1;				// ǰһ������·��
	int pre_id;							// ǰһ���ı��
	int max_vex = 0;					// ���������� 
	int max_arc = 0;					// �ߵĸ��� 
	for (int i = 0; i < MAX_V; i++) 
	{	// ��ʼ���ڽӱ� 
		G.vexlist[i].firstarc = NULL;
	}
	G.type = 1;							// ͼ������Ϊ����ͼ

	file >> n;
	for (int i = 1; i <= n; i++) 
	{
		int r ,num  ,id ; 
		file >> r >> num >> id;
		if (r != total) 
		{
			total++;
		}
                //��·����վ��Ĵ���		
				//����Ϣ�洢��·���� 
		R[r].station[num] = id;
		R[r].sum++;
		// ����Ϣ�洢��վ���� 
		int k = S[id].sum;
		S[id].Route[k] = r;
		S[id].sum++;
		//////////////////���ڽӱ�Ĵ��� 
				// �������վ��ı�� 
		if (max_vex < id)
			max_vex = id;

		if (pre_Route == r) {				// ���������һ��վ��������·���뵱ǰվ��һ������˵������վ���б� 
			//			max_arc++;
			max_arc += 2;					// �洢�ı���+2 
			ArcNode* p = new ArcNode;
			p->adjvex = id;
			p->path = r;
			p->next = G.vexlist[pre_id].firstarc;
			G.vexlist[pre_id].firstarc = p;
			// ����ͼ�Գƻ� 
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
	//	int line;		// ��ǰ����·
	int pre_line;	// ��һ����·
	int id;			// ��ǰ��·���Ķ���ʼ������id 
	//	int start;
	//	int end;
	//	int direction; 
}RNode;
RNode back[MAX_R];		// ����Сת�˽���Ļ��� 


// �������ȶ��� 
typedef struct ElemType {
	int data;			// ��Ϣ 
	int height;			// ��� 
}ElemType;

typedef struct Node {
	ElemType data;
	Node* next;
}Node; // ���нڵ�

class Queue { // һ��������
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
	void EnQueue(ElemType e) // ���, ���С������ǰ�� 
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
	ElemType DeQueue() // ����
	{
		if (front == rear) 
		{
			cout << "�����ѿ�!\n";
			exit(0);
		}
		Node* p = front->next;
		ElemType e = p->data;
		front->next = p->next;
		if (p == rear) rear = front;
		delete p;
		return e;
	}
	ElemType GetHead() // ��ȡ��ͷԪ��
	{
		if (front == rear) 
		{
			cout << "�����ѿ�!\n";
			exit(0);
		}
		else return front->next->data;
	}
	bool Empty() // �ж϶��Ƿ�Ϊ��
	{
		if (front == rear) return true;
		else return false;
	}
};

void LeastBuses(int start, int end)
{// ����Сת�˵�·�� 
	int visited[MAX_R] = { 0 };					// ��¼��·����û�б����ʹ� 
	int result = -1;								// �洢������Ŀ 
	Queue Q;
	// ��ʼ������ 
	for (int i = 0; i < S[end].sum; i++) 
	{		// ���յ�������·��ȫ����� 
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
		visited[cur] = 1;						// ��¼��ǰ��· 
		int sum1 = R[cur].sum;
		for (int i = 0; i < sum1; i++) 
		{		// ��ʼ������ǰ��·��ÿ��վ�� 
			int j = R[cur].station[i];			// jΪվ�� 

			//cout << "**" << cur << " " << j << endl;

			if (j == start) 
			{					// ��Ϊ�յ㣬���ݱ��������·�� 
				int privok = back[cur].id;		// �����������ֵ 
				int pre_line = back[cur].pre_line;				// ��һ��·�� 
				int begin = start;								// beginΪ��ʼ�������ֵ 
				int p_seq = 0;									// ��������ı��	
				int b_seq = 0;									// ��ʼ����ı�� 
				// �ӿ�ʼ�����������ǰ·�ߣ���������󣬷�����һ��·�ߣ�������� 
				while (cur != -1) 
				{
					// �ȱ���һ���·�ߣ��ҵ���ֵ��Ӧ�ı��		
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
					// ���·�� 
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
					if (pre_line != -1) cout << "��" << cur << "���˵�" << pre_line << endl;
					// ������һ��·�� 
					begin = privok;
					cur = pre_line;
					privok = back[cur].id;
					pre_line = back[cur].pre_line;
					result++; 
				}
				cout<<"������"<<result<<"��"<<endl;
				return;
			}

			int sum2 = S[j].sum;				// ������վ����������· 
			for (int k = 0; k < sum2; k++) 
			{
				int r = S[j].Route[k];			// rΪ��· 
				ElemType temp;
				temp.data = r;
				temp.height = now.height + 1;
				if (visited[r] == 0) 
				{
					int ii = 1;
				}
				if (visited[r] == 0 && back[r].id == 0) 
				{
					back[r].pre_line = cur;		// r������·����һ����·Ϊ����·cur 
					back[r].id = j;				// ���ҹ�������������·����վ��j
					Q.EnQueue(temp);				// �´α���r������·				
				}
			}


		}
	}
}

//����㾭������վ�㵽���յ� 
typedef struct Result {
	//	int seq;	// �ڸ�·���еı��
	int id;		// ���
	int way;	// ����·��
	int height; // �߶�
	int pre;	// ��һ��
}Result;

Result back2[MAX_V];						//���浱��������������ݵ��յ� 
int visited[MAX_V];							// ��¼��վ���Ƿ���ʹ� 

void LeastStations(int start, int end)
{// ���վ���վ�����ٽ�������
	int finished = 0;
	Queue Q2;
	// ���յ���Ϣ������������ 
	back2[end].height = 1;
	back2[end].id = end;
	back2[end].way = S[end].Route[0];
	back2[end].pre = -1;
	// ���յ���� 
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
		{											// �������� 
			finished = 1;
			break;
		}
		ArcNode* p = G.vexlist[cur.data].firstarc;							// ������ǰվ�����ڵ�վ�� 
		while (p) 
		{
			int in = p->adjvex;												// ���������ھӽڵ�
			if (visited[in] != 1) 
			{											// �ھӽڵ�δ�������� 
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
		cout<<"��������"<<result<<"��վ��"<<endl;
	}
	else 
	{
		cout << "��·��!"<<endl ;
	}
}
int main()
{
	CreateGraph();
	cout << "�Ƿ���Ҫ�������·��ͼ��YES or NO"<<endl ;
	string choice ;
	cin >> choice ;
	if(choice == "YES")  Show();
	while (1) 
	{
		cout << "���������վ(����-100����):" ;
		int start, end;
		cin >> start;
		if (start == -100) break; 
		if(start > 6584 || start <= 0)
		{
			cout << "���޴�վ��" << endl ; 
			break ;
		 } 
		cout << "�������յ�վ(����-100����):";
		cin >> end;
		if (end == -100) break; 
		if(end > 6584 || end <= 0)
		{
			cout << "���޴�վ��" << endl ; 
			break ;
		 } 
		cout << "----------------------ת���������ٵĳ˳�·��-----------------------\n";
		LeastBuses(start, end);
		cout << "----------------------����վ�����ٵĳ˳�·��-------------------\n";
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