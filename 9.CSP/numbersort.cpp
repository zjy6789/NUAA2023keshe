#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 1001  //��Ϊ�������ֵ������� 
int main()
{
	int n,num; //����n��Ϊ��������ָ�����num��Ϊ��������� 
	scanf("%d",&n);
	int arr[MAX_SIZE];  //���������ֳ��ִ��������� 
	int max,note;   //����maxѰ�ҳ������ִ������Ĵ���,note��λ���±� 
	int count=0; //��Ϊ�ж��Ƿ��˳�ѭ�������� 
	for(int i=0;i<MAX_SIZE;i++) arr[i]=0;  //��ʼ������ 
	for(int i=0;i<n;i++)  //�������ֲ�ͳ�����ֳ��ֵĴ��� 
	{
		scanf("%d",&num);
		arr[num]++;
	}
	for(int k=1;k<n;k++)
	{
		max=arr[0];  //��max��Ϊ��ʼֵ0 
		for(int i=1;i<MAX_SIZE;i++) //���±�1���±�1000��Ѱ�ҳ��ִ����������� 
		{
			if(max<arr[i]) //�����ǰmaxС��ĳ�����ֳ��ֵĴ������ͽ������ֳ��ֵĴ�����ֵ��max����¼������ 
			{
				max=arr[i];
				note=i;
			}
		}
		printf("%d %d\n",note,arr[note]);  //�������������ּ������������ 
		arr[note]=0; //���������ֵĳ��ִ�����Ϊ0 
		for(int j=0;j<MAX_SIZE;j++)  //�ж��Ƿ���������ȫ��ȡ�� 
		{
			if(arr[j]==0) count++;
		}
		if(count==MAX_SIZE)	break;  //�������������־���ȡ�꣬���˳�ѭ�� 
		else count=0; //��������������Ϊȡ�꣬������һ��ѭ�� 
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
