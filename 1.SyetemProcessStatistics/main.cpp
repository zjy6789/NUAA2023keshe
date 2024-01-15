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
    char name[100];  //������
    int duration;    //����ʱ��
    int memory;      //�ڴ�ʹ�����
    int pID;         //ID
    DLNode *next;    //ָ���һ���ڵ�
}DLNode,*DLinkList;

typedef struct SLNode
{
    char name[100];  //������
    int duration;    //����ʱ��
    int endtime;     //����ʱ��
    int pID;         //ID
    SLNode *pre;     //ָ��ǰһ���ڵ�
    SLNode *next;    //ָ���һ���ڵ�
}SLNode,*SLinkList;

int PrintMemoryInfo(DWORD); //��ȡ�ڴ�
int CreateList(DLinkList &); //������ǰ��������
int CreateEndedList(SLinkList &,DLinkList);//�����ѽ�����������
int SortDList(DLinkList &);   //���ڴ��С����������
int SortSList(SLinkList &);    //������ʱ�����������
int UpdateTime(DLinkList &,DLinkList &,SLinkList&); //ͳ���ѽ�������
int UpdateProgram(DLinkList &,DLinkList ,SLinkList&);  //ˢ�º���½���
SLinkList LocateOverList(SLinkList&,const int);   //����PID���ڴ������ʱ��������в��Ҹý���
void ShowArray_D(DLinkList,SLinkList);    //��ʾ��ǰ����


int main()
{
    DLinkList L;   //LΪ�ܽ��̱����ں͵�ǰ���̱�ȽϴӶ��õ��ѽ������̱�
    DLinkList CurrentL;//CurrentLΪ��ǰ���̱�
    SLinkList S;   //SΪ�ѽ������̱�

    CreateList(L);  //�����ܽ��̱�
    CreateEndedList(S,L); //�����ѽ������̱�
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

int PrintMemoryInfo(DWORD processID)  //��ȡ�ڴ�
{
    HANDLE hProcess;   //������
    PROCESS_MEMORY_COUNTERS pmc;  //���ڻ�ȡ���̵��ڴ�ͳ����Ϣ
    hProcess=OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,processID); //��һ��ָ���Ľ��̡�������в�ѯ�Ͷ�ȡ
    if(hProcess==nullptr)
        return 0;
    if(GetProcessMemoryInfo(hProcess,&pmc,sizeof(pmc)))  //���ڻ�ȡ�ڴ��ʹ�����
    {
        CloseHandle(hProcess);
        return pmc.WorkingSetSize;   //���س����ڵ�ǰ��������ڴ�ʹ����
    }
    return 0;
}

int CreateList(DLinkList &L) //����һ����ǰ��������
{
    L=(DLNode *)malloc(sizeof(DLNode));  //����ͷ���
    if(L==nullptr) exit(-1);   //�洢�ռ�����ʧ��
    L->next=nullptr;
    DLinkList p=L,q;   //���ڴ��������ڵ�

    PROCESSENTRY32 temp;   //�����Ž�����Ϣ�Ľṹ��
    temp.dwSize=sizeof(temp);
    HANDLE hProcessSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);  //���ڻ�ȡϵͳ�ڵ����н���
    if(INVALID_HANDLE_VALUE==hProcessSnapshot)
    {
        printf("δ��ý��̣�\n");
        return 0;
    }
    BOOL bMore=Process32First(hProcessSnapshot,&temp); //��ȡϵͳ��һ������
    while(bMore)    //�����н��̻�ȡ��Ϻ��˳�ѭ��
    {
        int judge=PrintMemoryInfo(temp.th32ProcessID);  //��ȡ��ǰ���̵��ڴ��С
        if(judge)
        {
            q=(DLNode *)malloc(sizeof(DLNode));   //�����½ڵ�
            q->memory=judge/1024;     //��ȡ�½ڵ��ڴ�
            q->duration=0;     //��ȡ�½ڵ����ʱ��
            q->pID=temp.th32ProcessID;   //��ȡ�½ڵ�ID
            strcpy(q->name,(char*)temp.szExeFile);  //��ȡ�½ڵ�Ľ�����
            //���½ڵ�q���ӵ㵱ǰ���q��
            q->next=nullptr;
            p->next=q;
            p=q;
        }
        bMore=Process32Next(hProcessSnapshot,&temp); //������ȡϵͳ����һ������
    }
    CloseHandle(hProcessSnapshot);   //���hProcess���
    return 1;
}

int CreateEndedList(SLinkList &S,DLinkList L) //�����ѽ������̱�
{
    S=(SLNode *)malloc(sizeof(SLNode));  //����ͷ�ڵ�
    if(S==nullptr) exit(-1);  //�����ڴ�ռ�ʧ��
    S->next=nullptr;
    S->duration=0;
    S->endtime=0;
    DLinkList p_L=L->next;    //���ڽ��ܽ��̵Ľ��̸��Ƶ��ѽ���������
    SLinkList p_S=S,q_S=nullptr;  //���ڴ����ѽ�������
    while(p_L!= nullptr)
    {
        q_S=(SLNode *)malloc(sizeof(SLNode));  //����ڵ�
        //��p_L��ʼ���½ڵ�
        q_S->duration=0;
        q_S->endtime=0;
        q_S->pID=p_L->pID;
        strcpy(q_S->name,p_L->name);
        //���½ڵ����ӵ���ǰ���p��
        p_S->next=q_S;
        q_S->pre=p_S;
        p_S=p_S->next;
        q_S->next=nullptr;
        p_L=p_L->next;
    }
    return 1;
}

int SortDList(DLinkList &L)   //���ڴ��С����������
{
    int ElemNum=0;
    DLinkList p_L=L->next;
    while(p_L!= nullptr)  //��ý���L�Ľ���������
    {
        ElemNum++;
        p_L=p_L->next;
    }
    p_L=L->next;
    DLinkList q_L=p_L->next;
    auto temp=(DLNode *)malloc(sizeof(DLNode));
    while(q_L!=nullptr)  //ͨ��temp���ܽ��̱����ڴ��С����
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

int SortSList(SLinkList &S)    //������ʱ������̴�С����
{
    int ElemNum=0;
    SLinkList p_S=S->next;
    while(p_S)  //��ý���L�Ľ���������
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

void ShowArray_D(DLinkList L, SLinkList S)  //����������̱���ѽ������̱�
{
    DLinkList p=L->next;
    SLinkList s=S->next;
    printf("��ǰϵͳ������                                  PID     �ڴ�ʹ�����(kb)       ����ʱ��(s)\n");
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
        printf("�ѽ���������                                    PID         ����ʱ��(s)        ����ʱ��(s)\n");
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

SLinkList LocateOverList(SLinkList &S,const int PID)  //���ѽ��������в��ҽ��̱��ΪPID�Ľ���
{
    SLinkList p=S->next;
    while(p!= nullptr)
    {
        if(p->pID==PID) return p; //����ҵ����ظýڵ�ָ��
        else p=p->next;
    }
    return nullptr;  //���򷵻ؿ�ָ��
}

int UpdateTime(DLinkList &CurrentL,DLinkList &L,SLinkList &S)   //ͳ���ѽ�������
{
    DLinkList p_L=L->next,pCurrentL;
    SLinkList p_S=S->next;
    int judge_isFound=0;   //�ж�δ���������Ƿ��ҵ�
    S->duration=S->duration+1;  //ͷ���������¼����ʱ��
    while(p_L!= nullptr)
    {
        pCurrentL=CurrentL->next;    //Ѱ������δ��������
        while(pCurrentL!= nullptr)
        {
            if(p_L->pID==pCurrentL->pID)  //�ý���δ����
            {
                judge_isFound=1;
                break;
            }
            pCurrentL=pCurrentL->next;
        }
        if(judge_isFound==0)  //�ý����ѽ���
        {
            p_S=LocateOverList(S,p_L->pID); //��ȡ�ý����������ѽ������������λ��
            if(p_S->endtime==0)		 //�������ʱ��Ϊ0�����½���ʱ��
                p_S->endtime=S->duration;	  //�������ʱ�䲻Ϊ0�����½����ĳ���ʱ��
            else p_S->duration++;
        }
        else if(judge_isFound==1)  //����δ����  ���µ�ǰ���̵����еĳ���ʱ��
        {
            p_L->duration++;
            pCurrentL->duration=p_L->duration;
        }
        p_L=p_L->next;
        judge_isFound=0;
    }
    return 1;
}

int UpdateProgram(DLinkList &L,DLinkList CurrentL,SLinkList &S)  //ˢ�º���½���
{
    SLinkList p_S=S->next,q_S=S->next,temp_S=(SLinkList)malloc(sizeof(SLNode));
    DLinkList p_L=L->next,q_L=L->next,temp_L=(DLinkList)malloc(sizeof(DLNode)), pCurrentL=CurrentL->next;
    int judge_isFound=0;   //�����ж������ҵ��½���
    while(pCurrentL!= nullptr)  //������ǰ���̱�
    {
        p_L=L->next;
        while(p_L!= nullptr)
        {
            if(p_L->pID==pCurrentL->pID) //�ý����Ѿ����ܽ��̱���
            {
                judge_isFound=1;
                break;
            }
            p_L=p_L->next;
        }
        if(judge_isFound==0)   //���̲���L�У�������ӵ�L,S��
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

