#include<cstdio>
#include<iomanip>
#include<windows.h>
#include<TLHELP32.h>
#include<cstring>
#include"Psapi.h"
#include<cstdlib>
#pragma comment(lib,"Psapi.lib")

typedef struct DLNode
{
    char name[100];  //进程名
    int duration;    //持续时间
    int memory;      //内存使用情况
    int pID;         //ID
    DLNode *next;    //指向后一个节点
}DLNode,*DLinkList;

typedef struct SLNode
{
    char name[100];  //进程名
    int duration;    //持续时间
    int endtime;     //结束时间
    int pID;         //ID
    SLNode *pre;     //指向前一个节点
    SLNode *next;    //指向后一个节点
}SLNode,*SLinkList;

int PrintMemoryInfo(DWORD); //获取内存
int CreateList(DLinkList &); //创建当前进程链表
int CreateEndedList(SLinkList &,DLinkList);//创建已结束进程链表
int SortDList(DLinkList &);   //按内存大小给进程排序
int SortSList(SLinkList &);    //按持续时间给进程排序
int UpdateTime(DLinkList &,DLinkList &,SLinkList&); //统计已结束进程
int UpdateProgram(DLinkList &,DLinkList ,SLinkList&);  //刷新后更新进程
SLinkList LocateOverList(SLinkList&,const int);   //根据PID，在储存结束时间的链表中查找该进程
void ShowArray_D(DLinkList,SLinkList);    //显示当前进程


int main()
{
    DLinkList L;   //L为总进程表，用于和当前进程表比较从而得到已结束进程表
    DLinkList CurrentL;//CurrentL为当前进程表
    SLinkList S;   //S为已结束进程表

    CreateList(L);  //创建总进程表
    CreateEndedList(S,L); //创建已结束进程表
    SortDList(L);
    ShowArray_D(L,S);
    while(1)
    {
        Sleep(1000);
        system("cls");
        CreateList(CurrentL);
        SortDList(CurrentL);
        UpdateTime(CurrentL,L,S);
        UpdateProgram(L,CurrentL,S);
        SortSList(S);
        ShowArray_D(CurrentL,S);
        //system("pause");
    }
    return 0;
}

int PrintMemoryInfo(DWORD processID)  //获取内存
{
    HANDLE hProcess;   //定义句柄
    PROCESS_MEMORY_COUNTERS pmc;  //用于获取进程的内存统计信息
    hProcess=OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,processID); //打开一个指定的进程。对其进行查询和读取
    if(hProcess==nullptr)
        return 0;
    if(GetProcessMemoryInfo(hProcess,&pmc,sizeof(pmc)))  //用于获取内存的使用情况
    {
        CloseHandle(hProcess);
        return pmc.WorkingSetSize;   //返回程序在当前代码出的内存使用量
    }
    return 0;
}

int CreateList(DLinkList &L) //创建一个当前进程链表
{
    L=(DLNode *)malloc(sizeof(DLNode));  //申请头结点
    if(L==nullptr) exit(-1);   //存储空间申请失败
    L->next=nullptr;
    DLinkList p=L,q;   //用于创建后续节点

    PROCESSENTRY32 temp;   //定义存放进程信息的结构体
    temp.dwSize=sizeof(temp);
    HANDLE hProcessSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);  //用于获取系统内的所有进程
    if(INVALID_HANDLE_VALUE==hProcessSnapshot)
    {
        printf("未获得进程！\n");
        return 0;
    }
    BOOL bMore=Process32First(hProcessSnapshot,&temp); //获取系统第一个进程
    while(bMore)    //当所有进程获取完毕后退出循环
    {
        int judge=PrintMemoryInfo(temp.th32ProcessID);  //获取当前进程的内存大小
        if(judge)
        {
            q=(DLNode *)malloc(sizeof(DLNode));   //申请新节点
            q->memory=judge/1024;     //获取新节点内存
            q->duration=0;     //获取新节点持续时间
            q->pID=temp.th32ProcessID;   //获取新节点ID
            strcpy(q->name,(char*)temp.szExeFile);  //获取新节点的进程名
            //将新节点q连接点当前结点q上
            q->next=nullptr;
            p->next=q;
            p=q;
        }
        bMore=Process32Next(hProcessSnapshot,&temp); //继续获取系统的下一个进程
    }
    CloseHandle(hProcessSnapshot);   //清除hProcess句柄
    return 1;
}

int CreateEndedList(SLinkList &S,DLinkList L) //创建已结束进程表
{
    S=(SLNode *)malloc(sizeof(SLNode));  //申请头节点
    if(S==nullptr) exit(-1);  //申请内存空间失败
    S->next=nullptr;
    S->duration=0;
    S->endtime=0;
    DLinkList p_L=L->next;    //用于将总进程的进程复制到已结束进程上
    SLinkList p_S=S,q_S=nullptr;  //用于创建已结束进程
    while(p_L!= nullptr)
    {
        q_S=(SLNode *)malloc(sizeof(SLNode));  //申请节点
        //用p_L初始化新节点
        q_S->duration=0;
        q_S->endtime=0;
        q_S->pID=p_L->pID;
        strcpy(q_S->name,p_L->name);
        //将新节点连接到当前结点p上
        p_S->next=q_S;
        q_S->pre=p_S;
        p_S=p_S->next;
        q_S->next=nullptr;
        p_L=p_L->next;
    }
    return 1;
}

int SortDList(DLinkList &L)   //按内存大小给进程排序
{
    int ElemNum=0;
    DLinkList p_L=L->next;
    while(p_L!= nullptr)  //获得进程L的进程总数量
    {
        ElemNum++;
        p_L=p_L->next;
    }
    p_L=L->next;
    DLinkList q_L=p_L->next;
    auto temp=(DLNode *)malloc(sizeof(DLNode));
    while(q_L!=nullptr)  //通过temp将总进程表按照内存大小排序
    {
        while(q_L!=nullptr)
        {
            if(p_L->memory<q_L->memory)
            {
                temp->memory=p_L->memory;
                strcpy(temp->name,p_L->name);
                temp->pID=p_L->pID;
                temp->duration=p_L->duration;

                p_L->memory=q_L->memory;
                strcpy(p_L->name,q_L->name);
                p_L->pID=q_L->pID;
                p_L->duration=q_L->duration;

                q_L->memory=temp->memory;
                strcpy(q_L->name,temp->name);
                q_L->pID=temp->pID;
                q_L->duration=temp->duration;
            }
            q_L=q_L->next;
        }
        p_L=p_L->next;
        q_L=p_L->next;
    }
    return 1;
}

int SortSList(SLinkList &S)    //按持续时间给进程大小排序
{
    int ElemNum=0;
    SLinkList p_S=S->next;
    while(p_S)  //获得进程L的进程总数量
    {
        ElemNum++;
        p_S=p_S->next;
    }
    p_S=S->next;
    SLinkList q_S=p_S->next;
    SLinkList temp=(SLNode *)malloc(sizeof(SLNode));
    while(q_S!=nullptr)
    {
        while(q_S!=nullptr)
        {
            if(p_S->duration>q_S->duration)
            {
                temp->duration=q_S->duration;
                temp->endtime=q_S->endtime;
                temp->pID=q_S->pID;
                strcpy(temp->name,q_S->name);

                q_S->duration=p_S->duration;
                q_S->endtime=p_S->endtime;
                q_S->pID=p_S->pID;
                strcpy(q_S->name,p_S->name);

                p_S->duration=temp->duration;
                p_S->endtime=temp->endtime;
                p_S->pID=temp->pID;
                strcpy(p_S->name,temp->name);
            }
            q_S=q_S->next;
        }
        p_S=p_S->next;
        q_S=p_S->next;
    }
    return 1;
}

void ShowArray_D(DLinkList L, SLinkList S)  //负责输出进程表和已结束进程表
{
    DLinkList p=L->next;
    SLinkList s=S->next;
    printf("当前系统进程名                                  PID     内存使用情况(kb)       持续时间(s)\n");
    while(p!= nullptr)
    {
        char *nameSave=p->name;
        for(int i=0;i<35;i++)
        {
            printf("%c",nameSave[i]);
            if(nameSave[i]=='\0')
            {
                for(int j=i;j<35;j++)
                {
                    printf(" ");
                }
                break;
            }
        }
        printf("      %10d %16d %18d\n",p->pID,p->memory,p->duration);
        p=p->next;
    }
    if(s!= nullptr)
    {
        printf("------------------------------------------------------------------------------------------\n");
        printf("已结束进程名                                    PID         持续时间(s)        结束时间(s)\n");
    }
    while(s!= nullptr)
    {
        if(s->endtime!=0)
        {
            char *nameSave1=s->name;
            for(int i=0;i<35;i++)
            {
                printf("%c",nameSave1[i]);
                if(nameSave1[i]=='\0')
                {
                    for(int j=i;j<35;j++)
                    {
                        printf(" ");
                    }
                    break;
                }
            }
            printf("      %10d %16d %18d\n",s->pID,s->duration,s->endtime);
        }
        s=s->next;
    }
}

SLinkList LocateOverList(SLinkList &S,const int PID)  //在已结束进程中查找进程编号为PID的进程
{
    SLinkList p=S->next;
    while(p!= nullptr)
    {
        if(p->pID==PID) return p; //如果找到返回该节点指针
        else p=p->next;
    }
    return nullptr;  //否则返回空指针
}

int UpdateTime(DLinkList &CurrentL,DLinkList &L,SLinkList &S)   //统计已结束进程
{
    DLinkList p_L=L->next,pCurrentL;
    SLinkList p_S=S->next;
    int judge_isFound=0;   //判断未结束进程是否找到
    S->duration=S->duration+1;  //头结点用来记录调试时间
    while(p_L!= nullptr)
    {
        pCurrentL=CurrentL->next;    //寻找有无未结束进程
        while(pCurrentL!= nullptr)
        {
            if(p_L->pID==pCurrentL->pID)  //该进程未结束
            {
                judge_isFound=1;
                break;
            }
            pCurrentL=pCurrentL->next;
        }
        if(judge_isFound==0)  //该进程已结束
        {
            p_S=LocateOverList(S,p_L->pID); //获取该结束进程在已结束进程链表的位置
            if(p_S->endtime==0)		 //如果结束时间为0，更新结束时间
                p_S->endtime=S->duration;	  //如果结束时间不为0，更新结束的持续时间
            else p_S->duration++;
        }
        else if(judge_isFound==1)  //进程未结束  更新当前进程的运行的持续时间
        {
            p_L->duration++;
            pCurrentL->duration=p_L->duration;
        }
        p_L=p_L->next;
        judge_isFound=0;
    }
    return 1;
}

int UpdateProgram(DLinkList &L,DLinkList CurrentL,SLinkList &S)  //刷新后更新进程
{
    SLinkList p_S=S->next,q_S=S->next,temp_S=(SLinkList)malloc(sizeof(SLNode));
    DLinkList p_L=L->next,q_L=L->next,temp_L=(DLinkList)malloc(sizeof(DLNode)), pCurrentL=CurrentL->next;
    int judge_isFound=0;   //用于判断有无找到新进程
    while(pCurrentL!= nullptr)  //遍历当前进程表
    {
        p_L=L->next;
        while(p_L!= nullptr)
        {
            if(p_L->pID==pCurrentL->pID) //该进程已经在总进程表中
            {
                judge_isFound=1;
                break;
            }
            p_L=p_L->next;
        }
        if(judge_isFound==0)   //进程不在L中，将其添加到L,S中
        {
            while(q_L->next!=nullptr) q_L=q_L->next;
            temp_L->memory=pCurrentL->memory;
            temp_L->pID=pCurrentL->pID;
            temp_L->duration=pCurrentL->duration;
            strcpy(temp_L->name,pCurrentL->name);
            q_L->next=temp_L;
            temp_L->next=nullptr;

            while(q_S->next!=nullptr) q_S=q_S->next;
            temp_S->duration=0;
            temp_S->endtime=0;
            strcpy(temp_S->name,pCurrentL->name);
            temp_S->pID=pCurrentL->pID;
            q_S->next=temp_S;
            temp_S->next=nullptr;
            temp_S->pre=q_S;
        }
        else if(judge_isFound==1)
        {
            p_S=S->next;
            while(p_S)
            {
                if(pCurrentL->pID==p_S->pID&& p_S->endtime != 0)
                {
                    p_S->endtime=0;
                    pCurrentL->duration=p_L->duration=0;
                    break;
                }
                p_S=p_S->next;
            }
        }
        pCurrentL=pCurrentL->next;
        judge_isFound=0;
    }
    return 1;
}

