#include<stdio.h>
#include<stdlib.h>
int main()
{
	int n,m; //������ĿҪ��������̵������� 
	scanf("%d %d",&n,&m);//�������̵������� 
	int arr1[n][m]; //���������̣����ڽ����������ɫ��� 
	int arr2[n][m];  //���帱���̣���������ĳ��λ����Ҫ����ʱ�������̶�Ӧλ��Ϊ1������Ϊ0 
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			scanf("%d",&arr1[i][j]);  //���������ɫ���������� 
			arr2[i][j]=0;  //�������̵�Ԫ��ȫ����ʼ��Ϊ0����ʾ������ȫ������Ҫ���� 
		}
	}
	printf("\n");
	int color_num; //�����ж�ĳһ��λ�õ���Ԫ�ػ�����Ԫ�����λ�õ���ɫ�Ƿ���ͬ
	//�����ж�ĳ����ͬ����ɫ�ӿ�ʼ��ͬ��j���굽�����ͬ��j����  
	int start_j=0;
	int end_j=0;
	for(int i=0;i<n;i++)  //����Ϊ��λ�������ж�ÿһ�� 
	{
		color_num=arr1[i][0]; //�Ƚ��ж���ɫ����Ϊĳһ�еĵ�һ����ɫ 
		//������ʼ�ͽ�����λ������ȫ����Ϊ0 
		start_j=0; 
		end_j=0;
		for(int j=1;j<m;j++) //�����ж�ÿһ�� 
		{
			if(arr1[i][j]==color_num)  //���ĳ��λ�õ���ɫ�����λ�õ���ɫ��ͬ 
				end_j=j; //�ͽ�����λ�ú��� 
			else //���ĳ��λ�õ���ɫ�����λ�õ���ɫ��ͬ 
			{
				if(end_j-start_j>=2) //�ж�֮ǰ�ۻ���ͬ����ɫ�Ƿ���ڵ���3����������ڵĻ����ͽ�����ȫ������ 
				{
					for(int k=start_j;k<=end_j;k++) //��start_j��ʼ��end_j�����������е��⼸��Ԫ���ڸ���������Ϊ1����ʾɾ�� 
					arr2[i][k]=1;	
				}
				color_num=arr1[i][j]; //���С�ڵĻ��������¿�ʼ����������ɫ�ж�����Ϊ��ǰ����ɫ 
				start_j=j; //��ʼλ��Ҳ�ӵ�ǰ��ʼ���� 
			}
		}
		if(end_j==m-1&&end_j-start_j>=2) //��������ĳ��ĩβʱ���жϴ�ĳһλ�õ�����ĩβ����ͬһԪ���ҳ��ȴ��ڵ���3 
		{
			for(int k=start_j;k<=end_j;k++)
				arr2[i][k]=1;	
		}
	}
	//����������Ϊ��λ�������ж�ÿһ�У��㷨ʵ�ֻ���һ�� 
	int start_i=0;
	int end_i=0;
	for(int j=0;j<m;j++)
	{
		color_num=arr1[0][j];
		start_i=0;
		end_i=0;
		for(int i=1;i<n;i++)
		{
			if(arr1[i][j]==color_num)
				end_i=i;
			else
			{
				if(end_i-start_i>=2)
				{
					for(int k=start_i;k<=end_i;k++)
					arr2[k][j]=1;	
				}
				color_num=arr1[i][j];
				start_i=i;
			}
		}
		if(end_i==n-1&&end_i-start_i>=2)
		{
			for(int k=start_i;k<=end_i;k++)
				arr2[k][j]=1;	
		}
	}
	//�����зֱ�Ϊ��λ����������ʼ����������
	//���ڸ������У����ĳһλ�õ�Ԫ��Ϊ0˵����Ӧ������������������̶�Ӧλ�õ���ɫֵ
	//���ĳһλ�õ�Ԫ��Ϊ1˵��Ӧ�������������0 
	for(int i=0;i<n;i++)   
	{
		for(int j=0;j<m;j++)
		{
			if(arr2[i][j]!=1) printf("%d ",arr1[i][j]);
			else printf("0 ");
		}
		printf("\n");
	}

	system("pause");
	return 0;
}
