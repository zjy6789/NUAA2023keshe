#include<stdio.h>
#include<stdlib.h>
#define MAX_LENGTH 100001
typedef struct SqList  //����˳��� 
{ 
	int r[MAX_LENGTH];  //0�ŵ�Ԫ���� 
	int length;  //˳����� 
}SqList;
void SelectSort(SqList &L)  //��ѡ�������㷨 
{
	//��˳���L���м�ѡ������ 
	for(int i=1;i<L.length;i++)
	{
		//��n-1�ˣ�ѡ�����ļ�¼����������λ
		int min=L.r[i];
		int k=i;    //������ʼ��¼�ؼ���Ϊ����� 
		for(int j=i+1;j<=L.length;j++)  //�����ļ�¼�Ƚϣ�ѡ�����ļ�¼ 
		{
			if(L.r[j]>min)  //���ָ����߲��洢 
			{
				min=L.r[j];
				k=j;
			}
		} 
		int temp=L.r[i];L.r[i]=L.r[k];L.r[k]=temp;  //�ҵ�����߲����� 
	}
}
int Positive_Number(SqList &L,SqList &S,int L_note,int S_note) //�����Ż�ȯ����Ʒ��ֵ��Ϊ����ʱ�Ļر� 
{
	//L_note��ʾ�Ż�ȯ��ֵΪ����������±�
	//S_note��ʾ��Ʒ��ֵΪ����������±� 
	int sum=0;  //�����ܻر�ֵ 
	if(L_note==0||S_note==0) return sum;  //����Ż�ȯ������Ʒ��ֵ������һ��ȫΪ�����Ļ���ֱ�ӷ���0 
	else  //���� 
	{
		int L_p=1,S_p=1;  //��L_p,S_pָ�������������ʼλ�� 
		while(L_p<=L_note&&S_p<=S_note)  //ֻҪ�ڱ߽緶Χ�� 
		{ 
			sum=sum+L.r[L_p]*S.r[S_p];  //���Ż�ȯ�Ĵ�ֵ����Ʒ�Ĵ�ֵ��ˣ����ӵ�sum�� 
			//�����������κ��� 
			L_p++;
			S_p++;
		}
	}
	return sum;   //�����Ż�ȯ����Ʒ��ֵ��Ϊ����ʱ�Ļر� 
}
int Negative_Number(SqList &L,SqList &S,int L_note,int S_note)  //�����Ż�ȯ����Ʒ��ֵ��Ϊ����ʱ�Ļر� 
{
	//L_note��ʾ�Ż�ȯ��ֵΪ����������±�
	//S_note��ʾ��Ʒ��ֵΪ����������±� 
	int sum=0;  //�����ܻر�ֵ 
	if(L_note==L.length||S_note==S.length) return sum;  //����Ż�ȯ������Ʒ��ֵ������һ��ȫΪ�����Ļ���ֱ�ӷ���0 
	else //���� 
	{
		int L_p=L.length,S_p=S.length;  //��L_p,S_pָ�������������ʼλ�� 
		while(L_p>L_note&&S_p>S_note)  //ֻҪ�ڱ߽緶Χ�� 
		{
			sum=sum+L.r[L_p]*S.r[S_p];  //���Ż�ȯ��Сֵ(����ֵ����)����Ʒ��Сֵ(����ֵ����)��ˣ����ӵ�sum��
			//������������ǰ�� 
			L_p--;
			S_p--;
		}
	}
	return sum;  //�����Ż�ȯ����Ʒ��ֵ��Ϊ����ʱ�Ļر� 
}
void CreateList(SqList &L,SqList &S)
{
	//������ĿҪ�������Ż�ȯ����Ʒ�ĸ�������ֵ 
	scanf("%d",&L.length); 
	for(int i=1;i<=L.length;i++)
	scanf("%d",&L.r[i]);
	scanf("%d",&S.length);
	for(int i=1;i<=S.length;i++)
	scanf("%d",&S.r[i]);
	//��������˳�����ʾ�Ż�ȯ����Ʒ�ļ�ֵ 
	SelectSort(L);
	SelectSort(S);
	int L_note,S_note; //����L_note��S_note��ʾ�Ż�ȯ����Ʒ�ļ�ֵΪ����������±� 
	//��������forѭ�����ҵ��±꣬��ֵ��L_note,S_note����ȫΪ��������ֵΪ�� 
	for(int i=1;i<=L.length;i++){
		if(L.r[i]<0){
			L_note=i-1;
			break;
		}
		if(L.r[L.length]>0)
		{
			L_note=L.length;
		}
	}
	for(int i=1;i<=S.length;i++){
		if(S.r[i]<0){
			S_note=i-1;
			break;
		}
		if(S.r[S.length]>0){
			S_note=S.length;
		}
	}
	int p_sum=Positive_Number(L,S,L_note,S_note);  //�����Ż�ȯ����Ʒ��ֵ��Ϊ����ʱ�Ļر� 
	int n_sum=Negative_Number(L,S,L_note,S_note);  //�����Ż�ȯ����Ʒ��ֵ��Ϊ����ʱ�Ļر� 
	printf("%d",p_sum+n_sum); //����Ҫ��������ر� 
}
int main()
{
	SqList L,S; //�����������Ա� 
	CreateList(L,S);  //�������������Ա������ĿҪ�� 
	system("pause");
	return 0;
}

/*
4 1 2 4 -1
4 7 6 -2 -3

43

4 3 2 6 1 
      3 2 6 3
�����49


7 3 36 -1 73 2 3 6
       6 -1 -1 -1 -1 -1 -1
����� 1

*/