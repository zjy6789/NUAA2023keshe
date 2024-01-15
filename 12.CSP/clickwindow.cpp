#include<stdio.h>
#include<stdlib.h>
typedef struct Coordinate //����ֵ 
{
	int x;  //��������ֵ�ĺ����� 
	int y;  //��������ֵ�������� 
}Coord;
typedef struct LNode
{
	int code;   //����ÿ�����ڵı��
	Coord Left_down;  //����ÿ�����ڵ����½ǵ����� 
	Coord Right_up;  //����ÿ�����ڵ����Ͻǵ�����
	struct LNode *next;   //����������һ������ 
}LNode,*LinkList;
typedef struct SListInfo 
{ 
	LinkList head;    //��ͷ���ָ�� 
	LinkList tail;   //��β���ָ�� 
	int length;   //������ĳ���(���ڸ���) 
}SListInfo;
void CreateList(SListInfo &L)  //����Ҫ�󴴽����������Ҫ�� 
{
	L.head=(LNode *)malloc(sizeof(LNode)); //����ͷ���洢�ռ� 
	if(L.head==NULL) exit(-1);   //�洢�ռ�����ʧ�� 
	L.head->next=NULL;   //ͷ������������� 
	L.tail=L.head;  //β���ָ��Ҳָ��ͷ��� 
	
	int Clicks;  //��ʾ���ĵ������ 
	scanf("%d %d",&L.length,&Clicks);  //������ĿҪ�����봰�ڵĸ����Լ����ĵ������ 
	LNode *p;  //���ڴ������ڽ�� 
	for(int i=0;i<L.length;i++)  //������������ 
	{
		p=(LNode *)malloc(sizeof(LNode));  //����ڵ�洢�ռ� 
		p->code=i+1;  //�����ڵı�Ÿ�ֵ 
		scanf("%d %d %d %d",&p->Left_down.x,&p->Left_down.y,&p->Right_up.x,&p->Right_up.y);  //���봰�ڵ��ĸ����� 
		//����������Ĵ��ڽڵ����ӵ�ͷ���֮�󣬴Ӷ���֤������Ĵ����ڿ���ͷ��㴦���Ա���� 
		p->next=L.head->next;  
		L.head->next=p;
		if(i==0)  //��βָ�븳ֵΪ��һ������Ĵ��ڽ�㣬�����ڴ�����������Ϻ�βָ��ָ��Զ��ͷ��㴦 
		L.tail=p; 
	}
	int click_x,click_y;  //��������������� 
	LNode *q=NULL; //������ָ��q���ڱ������� 
	LNode *q_pre=NULL;  //������ָ��q_pre��λ��ָ��q��λ�õ�ǰһ����㣬���㽫q����ǰ�������� 
	int arr[Clicks];  //���ڴ洢��� 
	int arr_length=0;  //�洢���������±� 
	int j;
	for(int i=0;i<Clicks;i++)  //���������Clicksֵ�����ѭ�� 
	{
		scanf("%d %d",&click_x,&click_y);  //���������������ֵ 
		q=L.head->next;  //��ָ��qָ���һ�����ڽ�� 
		for(j=0;j<L.length;j++)  //���������Ӷ��������ҵ��������λ�����ڵĴ���
		{
			if(click_x>=q->Left_down.x&&click_x<=q->Right_up.x&&click_y>=q->Left_down.y&&click_y<=q->Right_up.y)  //����ҵ� 
			{
				if(q==L.head->next)  //����ҵ��Ĵ���λ�ڶ��㴰�ڣ���ôֻ�轫�ô��ڵı�Ŵ洢�ڽ�������У�����������ڼ�����ȹ�ϵ 
				{
					arr[arr_length]=q->code;  //���ҵ��Ĵ��ڵı�Ŵ洢�ڽ�������� 
					arr_length++;  //�±�����1 
					break;  //�ҵ�����Ҫ��Ĵ��ڣ��˳��ڲ�ѭ����������һ��Ҫ�� 
				}
				else  //����ҵ��Ĵ��ڲ��Ƕ��㴰�ڣ���ô��Ҫ���ô��ڽ��������ǰ���Ե������ڼ�����ȹ�ϵ�����洢���ڱ�� 
				{
					arr[arr_length]=q->code;  //���ҵ��Ĵ��ڵı�Ŵ洢�ڽ�������� 
					arr_length++;  //�±�����1
					//��������������ȹ�ϵ��ȡ�ķ�����:
					//����һ���µĴ��ڽ�㣬���ҵ��Ĵ��ڵı�ţ��Լ��������긴�Ƶ��µĴ��ڽ��
					//����������Ĵ��ڽ�����ӵ�ͷ���֮�󣬱�ʾ�ô��ڳ�Ϊ���㴰��
					//ͬʱ��q_pre��qָ����ɽ�q����ǰ�������� 
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
			else  //���ǰi������û���ҵ�����ô�ͼ������±���������q_pre��q��λ�� 
			{
				q_pre=q;
				q=q->next;
			}
		} //����ڲ�ѭ���ܹ�ȫ����ɶ��м�û���˳��Ļ���˵���ڱ��������д��ں���Ȼû���ҵ��������������Ĵ��ڣ���ô�����ΪIGNORE 
		if(j==L.length){
			arr[arr_length]=0;
			arr_length++;
		}
	}  //��������ѭ��������洢�������ڣ����˳����������ڵĽ�������ֵΪ����˵���ҵ���ֱ�������ֵ�����ֵΪ0��˵��û���ҵ���ֱ�����IGNORE 
	for(int i=0;i<Clicks;i++)
	{
		if(arr[i]>0) printf("%d\n",arr[i]);
		if(arr[i]==0) printf("IGNORED\n");
	}
}
int main()
{
	SListInfo L; //������������ 
	CreateList(L);  //�����ĿҪ�� 
	system("pause");
	return 0;
}
