#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 1001  //作为输入数字的最大界限 
int main()
{
	int n,num; //定义n作为输入的数字个数，num作为输入的数字 
	scanf("%d",&n);
	int arr[MAX_SIZE];  //定义存放数字出现次数的数组 
	int max,note;   //定义max寻找出数字现次数最多的次数,note定位其下标 
	int count=0; //作为判断是否退出循环的条件 
	for(int i=0;i<MAX_SIZE;i++) arr[i]=0;  //初始化数组 
	for(int i=0;i<n;i++)  //输入数字并统计数字出现的次数 
	{
		scanf("%d",&num);
		arr[num]++;
	}
	for(int k=1;k<n;k++)
	{
		max=arr[0];  //将max设为初始值0 
		for(int i=1;i<MAX_SIZE;i++) //从下标1到下标1000内寻找出现次数最多的数字 
		{
			if(max<arr[i]) //如果当前max小于某个数字出现的次数，就将该数字出现的次数赋值给max并记录其数字 
			{
				max=arr[i];
				note=i;
			}
		}
		printf("%d %d\n",note,arr[note]);  //将出现最多的数字及次数输出出来 
		arr[note]=0; //并将该数字的出现次数设为0 
		for(int j=0;j<MAX_SIZE;j++)  //判断是否所有数字全部取完 
		{
			if(arr[j]==0) count++;
		}
		if(count==MAX_SIZE)	break;  //数组内所有数字均已取完，则退出循环 
		else count=0; //数组内仍有数字为取完，继续下一轮循环 
	}
	system("pause");
	return 0;
}

/*
12
5 2 3 3 1 3 4 2 5 2 3 5

3 4
2 3
5 3
1 1
4 1

*/
