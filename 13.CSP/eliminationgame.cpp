#include<stdio.h>
#include<stdlib.h>
int main()
{
	int n,m; //根据题目要求定义的棋盘的行列数 
	scanf("%d %d",&n,&m);//输入棋盘的行列数 
	int arr1[n][m]; //定义主棋盘，用于接受输入的颜色编号 
	int arr2[n][m];  //定义副棋盘，当主棋盘某个位置需要消除时，副棋盘对应位置为1，否则为0 
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			scanf("%d",&arr1[i][j]);  //将输入的颜色存入主棋盘 
			arr2[i][j]=0;  //将副棋盘的元素全部初始化为0，表示主棋盘全部不需要消除 
		}
	}
	printf("\n");
	int color_num; //用于判断某一个位置的左元素或者上元素与该位置的颜色是否相同
	//用于判断某个相同的颜色从开始相同的j坐标到最后相同的j坐标  
	int start_j=0;
	int end_j=0;
	for(int i=0;i<n;i++)  //以行为单位，依次判断每一行 
	{
		color_num=arr1[i][0]; //先将判定颜色设置为某一行的第一个颜色 
		//并将开始和结束的位置坐标全部设为0 
		start_j=0; 
		end_j=0;
		for(int j=1;j<m;j++) //依次判断每一行 
		{
			if(arr1[i][j]==color_num)  //如果某个位置的颜色和左边位置的颜色相同 
				end_j=j; //就将结束位置后移 
			else //如果某个位置的颜色和左边位置的颜色不同 
			{
				if(end_j-start_j>=2) //判断之前累积相同的颜色是否大于等于3个，如果大于的话，就将它们全部消除 
				{
					for(int k=start_j;k<=end_j;k++) //从start_j开始到end_j结束，将该行的这几个元素在副棋盘中设为1，表示删除 
					arr2[i][k]=1;	
				}
				color_num=arr1[i][j]; //如果小于的话，就重新开始计数，把颜色判定设置为当前新颜色 
				start_j=j; //开始位置也从当前开始计数 
			}
		}
		if(end_j==m-1&&end_j-start_j>=2) //当遍历到某行末尾时，判断从某一位置到改行末尾都是同一元素且长度大于等于3 
		{
			for(int k=start_j;k<=end_j;k++)
				arr2[i][k]=1;	
		}
	}
	//下面是以列为单位，依次判断每一列，算法实现基本一致 
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
	//以行列分别为单位检查结束，开始遍历副棋盘
	//对于副棋盘中，如果某一位置的元素为0说明不应该消除，就输出主棋盘对应位置的颜色值
	//如果某一位置的元素为1说明应该消除，就输出0 
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
