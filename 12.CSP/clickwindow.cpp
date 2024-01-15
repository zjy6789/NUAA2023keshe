#include<stdio.h>
#include<stdlib.h>
typedef struct Coordinate //坐标值 
{
	int x;  //定义坐标值的横坐标 
	int y;  //定义坐标值的纵坐标 
}Coord;
typedef struct LNode
{
	int code;   //定义每个窗口的编号
	Coord Left_down;  //定义每个窗口的左下角的坐标 
	Coord Right_up;  //定义每个窗口的右上角的坐标
	struct LNode *next;   //用于连接下一个窗口 
}LNode,*LinkList;
typedef struct SListInfo 
{ 
	LinkList head;    //表头结点指针 
	LinkList tail;   //表尾结点指针 
	int length;   //单链表的长度(窗口个数) 
}SListInfo;
void CreateList(SListInfo &L)  //根据要求创建单链表并完成要求 
{
	L.head=(LNode *)malloc(sizeof(LNode)); //申请头结点存储空间 
	if(L.head==NULL) exit(-1);   //存储空间申请失败 
	L.head->next=NULL;   //头结点后无其他结点 
	L.tail=L.head;  //尾结点指针也指向头结点 
	
	int Clicks;  //表示鼠标的点击次数 
	scanf("%d %d",&L.length,&Clicks);  //根据题目要求输入窗口的个数以及鼠标的点击次数 
	LNode *p;  //用于创建窗口结点 
	for(int i=0;i<L.length;i++)  //创建窗口链表 
	{
		p=(LNode *)malloc(sizeof(LNode));  //申请节点存储空间 
		p->code=i+1;  //将窗口的编号赋值 
		scanf("%d %d %d %d",&p->Left_down.x,&p->Left_down.y,&p->Right_up.x,&p->Right_up.y);  //输入窗口的四个坐标 
		//将最新输入的窗口节点链接到头结点之后，从而保证后输入的窗口在靠近头结点处，以便遍历 
		p->next=L.head->next;  
		L.head->next=p;
		if(i==0)  //将尾指针赋值为第一次输入的窗口结点，这样在窗口链表创建完毕后，尾指针指向远离头结点处 
		L.tail=p; 
	}
	int click_x,click_y;  //定义鼠标点击的坐标 
	LNode *q=NULL; //定义结点指针q用于遍历链表 
	LNode *q_pre=NULL;  //定义结点指针q_pre定位到指针q的位置的前一个结点，方便将q结点的前后结点链接 
	int arr[Clicks];  //用于存储结果 
	int arr_length=0;  //存储结果数组的下标 
	int j;
	for(int i=0;i<Clicks;i++)  //根据输入的Clicks值，完成循环 
	{
		scanf("%d %d",&click_x,&click_y);  //输入鼠标点击的坐标值 
		q=L.head->next;  //将指针q指向第一个窗口结点 
		for(j=0;j<L.length;j++)  //遍历链表，从顶层往下找到鼠标点击的位置所在的窗口
		{
			if(click_x>=q->Left_down.x&&click_x<=q->Right_up.x&&click_y>=q->Left_down.y&&click_y<=q->Right_up.y)  //如果找到 
			{
				if(q==L.head->next)  //如果找到的窗口位于顶层窗口，那么只需将该窗口的编号存储在结果数组中，无需调整窗口间的优先关系 
				{
					arr[arr_length]=q->code;  //将找到的窗口的编号存储在结果数组中 
					arr_length++;  //下标自增1 
					break;  //找到符合要求的窗口，退出内层循环，进入下一次要求 
				}
				else  //如果找到的窗口不是顶层窗口，那么需要将该窗口结点移至最前面以调整窗口间的优先关系，并存储窗口编号 
				{
					arr[arr_length]=q->code;  //将找到的窗口的编号存储在结果数组中 
					arr_length++;  //下标自增1
					//下面调整窗口优先关系采取的方法是:
					//申请一个新的窗口结点，将找到的窗口的编号，以及顶点坐标复制到新的窗口结点
					//并将新申请的窗口结点链接到头结点之后，表示该窗口成为顶层窗口
					//同时由q_pre和q指针完成将q结点的前后结点链接 
					p=(LNode *)malloc(sizeof(LNode));
					p->code=q->code;
					p->Left_down.x=q->Left_down.x;
					p->Left_down.y=q->Left_down.y;
					p->Right_up.x=q->Right_up.x;
					p->Right_up.y=q->Right_up.y;
					p->next=L.head->next;
					L.head->next=p;
					q_pre->next=q->next;
					p=NULL;
					break;
				} 
			} 
			else  //如果前i个窗口没有找到，那么就继续向下遍历，更新q_pre和q的位置 
			{
				q_pre=q;
				q=q->next;
			}
		} //如果内层循环能够全部完成而中间没有退出的话，说明在遍历完所有窗口后，仍然没有找到符合鼠标点击座标的窗口，那么结果就为IGNORE 
		if(j==L.length){
			arr[arr_length]=0;
			arr_length++;
		}
	}  //根据上面循环将结果存储在数组内，最后按顺序输出数组内的结果，如果值为正，说明找到，直接输出该值，如果值为0，说明没有找到，直接输出IGNORE 
	for(int i=0;i<Clicks;i++)
	{
		if(arr[i]>0) printf("%d\n",arr[i]);
		if(arr[i]==0) printf("IGNORED\n");
	}
}
int main()
{
	SListInfo L; //创建窗口链表 
	CreateList(L);  //完成题目要求 
	system("pause");
	return 0;
}
