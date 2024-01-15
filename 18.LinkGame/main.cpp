#include<iostream>
#include<cstdlib>
#include<fstream>
#include<ctime>
#include<vector>
#include<iomanip>
#include<algorithm>
#include<random>
using namespace std;

//生成随机矩阵，且每个数据个数均为偶数
void generateMatrix() 
{
    int matrix[10][20]={0};
    // 初始化随机数种子
    srand(static_cast<unsigned int>(time(nullptr)));

    //没生成一个随机数就存两次，保证为偶数个
    int randomnumber;
    vector<int> number;
    for(int i=0;i<100;i++)
    {
        randomnumber=abs(rand())%10+1;
        number.push_back(randomnumber);
        number.push_back(randomnumber);
    }
    // 使用 C++11 之后的随机数引擎来初始化随机数生成器
    random_device rd;
    mt19937 g(rd());

    // 随机打乱 vector
    shuffle(number.begin(), number.end(), g);
    int *p=&matrix[0][0];
    for(int i=0;i<200;i++)
    {
        *p=number[i];
        p++;
    }
    //将矩阵写入文件
    ofstream file("data.txt");
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<20;j++)
        {
            file<<matrix[i][j]<<" ";
        }
        file<<endl;
    }
    file.close();

}



// 判断两个坐标是否在同一行
bool sameRow(int x1, int x2) {
    return x1 == x2;
}

// 判断两个坐标是否在同一列
bool sameCol(int y1, int y2) {
    return y1 == y2;
}

// 判断两个坐标之间是否存在直线路径
bool hasStraightPath(int x1, int y1, int x2, int y2, int matrix[][22]) {
    // 判断是否在同一行有直线路径
    if (sameRow(x1, x2)) {
        int minY = min(y1, y2);
        int maxY = max(y1, y2);
        for (int y = minY + 1; y < maxY; ++y) {
            if (matrix[x1][y] != 0) {
                return false;
            }
        }
        return true;
    }

    // 判断是否在同一列有直线路径
    if (sameCol(y1, y2)) {
        int minX = min(x1, x2);
        int maxX = max(x1, x2);
        for (int x = minX + 1; x < maxX; ++x) {
            if (matrix[x][y1] != 0) {
                return false;
            }
        }
        return true;
    }

    return false;
}

// 判断两个坐标之间是否存在一个拐点路径
bool hasOneTurnPath(int x1, int y1, int x2, int y2, int matrix[][22]) {
    int rows = 10;
    int cols = 20;

    // 水平方向（x轴）上的拐点
    for (int i = 1; i <= rows; ++i) 
    {
        if (i != x1  && matrix[i][y1] == 0&& hasStraightPath(x1, y1, i, y1, matrix)&&hasStraightPath(i,y1,x2,y2,matrix) )
        {
            return true;
        }
    }

    // 垂直方向（y轴）上的拐点

    for (int j = 1; j <= cols; ++j) 
    {
        if (j != y1  && matrix[x1][j] == 0  &&hasStraightPath(x1, y1, x1, j, matrix)&&hasStraightPath(x1,j,x2,y2,matrix))
        {
            return true;
        }
    }

    return false;
}

// 判断两个坐标之间是否存在两个拐点路径
bool hasTwoTurnsPath(int x1, int y1, int x2, int y2, int matrix[][22]) {
    int rows = 10;
    int cols = 20;

    // 在同一行上找第一个拐点
    for (int i = 0; i <= rows+1; ++i) 
    {
        if (i != x1  && matrix[i][y1] == 0 &&
            hasStraightPath(x1, y1, i, y1, matrix) && hasOneTurnPath(i, y1, x2, y2, matrix)) 
        {
            return true;
        }
    }

    // 在同一列上找第一个拐点
    for (int j = 0; j <= cols+1; ++j) 
    {
        if (j != y1  && matrix[x1][j] == 0 && 
            hasStraightPath(x1, y1, x1, j, matrix) && hasOneTurnPath(x1, j, x2, y2, matrix)) {
            return true;
        }
    }

    return false;
}

// 判断两个坐标之间是否能够消除
bool canEliminate(pair<int, int> dot1, pair<int, int> dot2, int matrix[][22]) {
    int x1 = dot1.first, y1 = dot1.second;
    int x2 = dot2.first, y2 = dot2.second;

    if (matrix[x1][y1] != matrix[x2][y2]) {
        return false;  // 不同数字的块无法消除
    }

    // 判断是否在同一行或同一列，或者通过一个拐点相连
    return hasStraightPath(x1,y1,x2,y2,matrix)|| hasOneTurnPath(x1, y1, x2, y2, matrix) || hasTwoTurnsPath(x1, y1, x2, y2, matrix);
}

int main()
{
    generateMatrix();
    int matrix[12][22]={0};
    //读数据
    ifstream file("data.txt");
    for(int i=1;i<=10;i++)
    {
        for(int j=1;j<=20;j++)
        {
            file>>matrix[i][j];
        }
    }
    file.close();
    //打印读取的图
    for(int i=1;i<=10;i++)
    {
        for(int j=1;j<=20;j++)
        {
            cout<<setw(3)<<left<<matrix[i][j];
        }
        cout<<endl;
    }
    pair<int,int> dot1,dot2;
    //游戏主循环
    while(1)
    {
        cout<<endl<<"输入两个点的x,y坐标：";
        cin>>dot1.first>>dot1.second>>dot2.first>>dot2.second;
        if(canEliminate(dot1,dot2,matrix)==true)
        {
            matrix[dot1.first][dot1.second]=0;
            matrix[dot2.first][dot2.second]=0;
        }
        //打印更新后的图;
        system("cls");
        for(int i=1;i<=10;i++)
        {
            for(int j=1;j<=20;j++)
            {
                if(matrix[i][j]!=0)
                    cout<<setw(3)<<left<<matrix[i][j];
                else cout<<"   ";
            }
            cout<<endl;
        }
        //建立退出循环条件
        bool flag=true;
        for(int i=1;i<=10;i++)
        {
            for(int j=1;j<=20;j++)
            {
                //若矩阵存在未消除的方块
                if(matrix[i][j]!=0)
                    flag=false;
            }
        }
        //方块全部消除，游戏结束
        if(flag) break;
    }
    system("pause");
    return 0;
}