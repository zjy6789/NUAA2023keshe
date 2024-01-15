#include<stdio.h>
#include<stdlib.h>
#define MAX_LENGTH 100001
typedef struct SqList  //定义顺序表 
{ 
	int r[MAX_LENGTH];  //0号单元闲置 
	int length;  //顺序表长度 
}SqList;
void SelectSort(SqList &L)  //简单选择排序算法 
{
	//对顺序表L进行简单选择排序 
	for(int i=1;i<L.length;i++)
	{
		//共n-1趟，选择最大的记录，并交换到位
		int min=L.r[i];
		int k=i;    //假设起始记录关键字为最大者 
		for(int j=i+1;j<=L.length;j++)  //与后面的记录比较，选择最大的记录 
		{
			if(L.r[j]>min)  //发现更大者并存储 
			{
				min=L.r[j];
				k=j;
			}
		} 
		int temp=L.r[i];L.r[i]=L.r[k];L.r[k]=temp;  //找到最大者并交换 
	}
}
int Positive_Number(SqList &L,SqList &S,int L_note,int S_note) //计算优惠券和商品价值都为正数时的回报 
{
	//L_note表示优惠券价值为正数的最大下标
	//S_note表示商品价值为正数的最大下标 
	int sum=0;  //定义总回报值 
	if(L_note==0||S_note==0) return sum;  //如果优惠券或者商品价值至少有一种全为负数的话，直接返回0 
	else  //否则 
	{
		int L_p=1,S_p=1;  //将L_p,S_p指向两个数组的起始位置 
		while(L_p<=L_note&&S_p<=S_note)  //只要在边界范围内 
		{ 
			sum=sum+L.r[L_p]*S.r[S_p];  //让优惠券的大值与商品的大值相乘，并加到sum上 
			//两个数组依次后移 
			L_p++;
			S_p++;
		}
	}
	return sum;   //返回优惠券和商品价值都为正数时的回报 
}
int Negative_Number(SqList &L,SqList &S,int L_note,int S_note)  //计算优惠券和商品价值都为负数时的回报 
{
	//L_note表示优惠券价值为正数的最大下标
	//S_note表示商品价值为正数的最大下标 
	int sum=0;  //定义总回报值 
	if(L_note==L.length||S_note==S.length) return sum;  //如果优惠券或者商品价值至少有一种全为正数的话，直接返回0 
	else //否则 
	{
		int L_p=L.length,S_p=S.length;  //将L_p,S_p指向两个数组的起始位置 
		while(L_p>L_note&&S_p>S_note)  //只要在边界范围内 
		{
			sum=sum+L.r[L_p]*S.r[S_p];  //让优惠券的小值(绝对值更大)与商品的小值(绝对值更大)相乘，并加到sum上
			//两个数组依次前移 
			L_p--;
			S_p--;
		}
	}
	return sum;  //返回优惠券和商品价值都为负数时的回报 
}
void CreateList(SqList &L,SqList &S)
{
	//按照题目要求输入优惠券和商品的个数及价值 
	scanf("%d",&L.length); 
	for(int i=1;i<=L.length;i++)
	scanf("%d",&L.r[i]);
	scanf("%d",&S.length);
	for(int i=1;i<=S.length;i++)
	scanf("%d",&S.r[i]);
	//创建两个顺序表，表示优惠券和商品的价值 
	SelectSort(L);
	SelectSort(S);
	int L_note,S_note; //定义L_note，S_note表示优惠券和商品的价值为正数的最大下标 
	//下面两个for循环是找到下标，赋值给L_note,S_note，若全为整数，则赋值为表长 
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
	int p_sum=Positive_Number(L,S,L_note,S_note);  //计算优惠券和商品价值都为正数时的回报 
	int n_sum=Negative_Number(L,S,L_note,S_note);  //计算优惠券和商品价值都为负数时的回报 
	printf("%d",p_sum+n_sum); //按照要求输出最大回报 
}
int main()
{
	SqList L,S; //定义两个线性表 
	CreateList(L,S);  //创建这两个线性表并完成题目要求 
	system("pause");
	return 0;
}

/*
4 1 2 4 -1
4 7 6 -2 -3

43

4 3 2 6 1 
      3 2 6 3
输出：49


7 3 36 -1 73 2 3 6
       6 -1 -1 -1 -1 -1 -1
输出： 1

*/