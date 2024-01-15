#include<vector>
#include<iostream>
#include<fstream>
#include<cctype>
#include<io.h>
#include"Maze.h"
using namespace std;

// ANSI ת����궨��
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

void createmaze(int map[][L],pair<int,int> &start,pair<int,int> &end)//����Maze�������Թ���ֱ�Ӷ�ȡ���е��Թ��ļ�
{
    cout<<"�Ƿ��������Թ���(Y/N):";
    char ch;
    cin>>ch;
    if(toupper(ch)=='Y')
    {
        Maze maze;
        cout<<endl<<"���Թ������ɣ�"<<endl;
        system("pause");
    }
    if(_access("mazemap.txt",0)==-1)
    {
        cout<<endl<<"���Թ��ļ������Զ������µ��Թ���"<<endl;
    }
    ifstream ifile("mazemap.txt");
    for(int i=0;i<L;i++)
    {
        for(int j=0;j<L;j++)
        {
            ifile>>map[i][j];
        }
    }
    ifile>>start.first>>start.second>>end.first>>end.second;
    ifile.close();
}

bool is_visited[L][L]={false};
void solution_dfs(vector<pair<int,int>> &path,int map[][L],pair<int,int> end)//���������������Ѱ���Թ�����
{
    if(path.back()==end) 
        return;

    vector<pair<int,int>> way={{0,1},{1,0},{0,-1},{-1,0}};

    pair<int,int> cur=path.back();
    pair<int,int> next;
    for(pair<int,int> i:way)
    {
        next.first=cur.first+i.first;
        next.second=cur.second+i.second;
        //�ж���һ����λ���Ƿ���ߣ�
        if(next.first>0&&next.second>0&&next.first<L-1&&next.second<L-1&&map[next.first][next.second]!=0&&is_visited[next.first][next.second]==false)
        {
            path.push_back(next);
            is_visited[next.first][next.second]=true;
            solution_dfs(path,map,end);
            if(!path.empty()&&path.back()==end)
            {
                return;
            }
            else path.pop_back();
        }
    }


}

void show(int map[][L])
{
    system("cls");
    for(int i=1;i<L-1;i++)
    {
        for(int j=1;j<L-1;j++)
        {
            switch (map[i][j])
            {
            case 0:cout<<RED<<"����"<<RESET;break;
            case 1:cout<<"  ";break;
            case 2:cout<<GREEN<<"��"<<RESET;break;
            case 3:cout<<YELLOW<<"��"<<RESET;break;
            case 4:cout<<YELLOW<<"��"<<RESET;break;
            
            default:
                break;
            }
        }
        cout<<endl;
    }
    system("pause");
}

int main()
{
    pair<int,int> start,end;
    int map[L][L];

    //�����Թ�
    createmaze(map,start,end);
    show(map);

    //�Թ����
    vector<pair<int,int>> path;
    path.push_back(start);
    is_visited[start.first][start.second]=true;
    solution_dfs(path,map,end);

    //��·���ڵ�ͼ�ϱ�ǳ���
    for(auto i:path)
    {
        if(i!=path.front()&&i!=path.back())
            map[i.first][i.second]=2;
    }
    show(map);
    return 0;
}