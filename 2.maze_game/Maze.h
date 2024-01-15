#ifndef _MAZE_H_
#define _MAZE_H_

#include<iostream>
#include<vector>
#include<fstream>
#include<cstdlib>
#include<ctime>

using namespace std;

#define L 30

class Maze
{
private:
    int map[L][L]={0};//地图矩阵
public:
    pair<int,int> start,end;//迷宫的起点和终点
    Maze();
    void Save_to_file();
};




Maze::Maze()//构造函数将自动生成一个新迷宫
{
    //基于Prim算法生成的随机迷宫
    //最外围设置为路，可以有效的保护里面一层墙体，并防止出界
    for (int i = 0; i < L; i++)
    {
        map[i][0] = 1;
        map[0][i] = 1;
        map[L - 1][i] = 1;
        map[i][L - 1] = 1;
    }

    //墙队列，包括X , Y
    vector<int> X;
    vector<int> Y;

    //任取初始值
    X.push_back(2);
    Y.push_back(2);
    //初始化随机数种子
    srand(time(0));

    //当墙队列为空时结束循环
    while (X.size())
    {
        //在墙队列中随机取一点
        int r = rand() % X.size();
        int x = X[r];
        int y = Y[r];

        //判读上下左右四个方向是否为路
        int count = 0;
        for (int i = x - 1; i < x + 2; i++)
        {
            for (int j = y - 1; j < y + 2; j++)
            {
                if (abs(x - i) + abs(y - j) == 1 && map[i][j] > 0)
                    ++count;
            }
        }

        if (count <= 1)
        {
            map[x][y] = 1;
            //在墙队列中插入新的墙
            for (int i = x - 1; i < x + 2; i++)
            {
                for (int j = y - 1; j < y + 2; j++)
                {
                    if (abs(x - i) + abs(y - j) == 1 && map[i][j] == 0)
                    {
                        X.push_back(i);
                        Y.push_back(j);
                    }
                }
            }
        }

        //删除当前墙
        X.erase(X.begin() + r);
        Y.erase(Y.begin() + r);
    }

    //设置迷宫进出口
    map[2][1] = 3;
    for (int i = L - 3; i >= 0; i--)
    {
        if (map[i][L - 3] == 1)
        {
            map[i][L - 2] = 4;
            end={i,L-2};
            break;
        }
    }
    start={2,1};

    Save_to_file();//将迷宫保存至文本文件中
}

void Maze::Save_to_file()
{
    ofstream ofile("mazemap.txt");
    for(int i=0;i<L;i++)
    {
        for(int j=0;j<L;j++)
        {
            ofile<<map[i][j]<<" ";
        }
        ofile<<endl;
    }
    ofile<<start.first<<" "<<start.second<<" "<<end.first<<" "<<end.second;
    ofile.close();
}


#endif