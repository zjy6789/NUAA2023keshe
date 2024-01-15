#ifndef _FAMILYTREE_H_
#define _FAMILYTREE_H_
#include<fstream>
#include<vector>
#include<deque>
#include<direct.h>
#include"Member.h"

using namespace std;


class FamilyTree
{
private:
    Member* Root;
    Member*readmember(ifstream &file);
    void writemember(ofstream &file,Member*r);
    Member*search_name_dfs(Member*r,string name);
    void search_birth_dfs(Member*r,string birth,vector<Member*> &list);
public:
    FamilyTree():Root(nullptr){};
    ~FamilyTree();

    void CreateTree(ifstream&file);
    void SaveTree(ofstream &file);
    void show();

    Member*search_name(string name);
    void search_birth(string name,vector<Member*> &list);
    void search_generation(int n,deque<Member*>&list);
    int search_relation(string name1,string name2);//0����1��ĸ��Ů��2���3��ϵ����������4�ֵܽ��ã�5��ϵ�ֵܽ���

    bool Add(Member*p);
    bool Delete(string name);
    bool Edit(string name);

};

void FamilyTree::CreateTree(ifstream &file)
{
    deque<Member*> que;
    
    Root=readmember(file);
    que.push_back(Root);
    Member*p=nullptr,*q=nullptr;
    q=readmember(file);
    while (q!=nullptr&&!que.empty())
    {
        p=que.front();
        while(q!=nullptr&&q->parent()==p->name())
        {
            p->add_child_node(q);
            q->set_parent_node(p);
            que.push_back(q);
            q=readmember(file);
        }
        que.pop_front();
    }
    
}
Member* FamilyTree::readmember(ifstream&file)
{
    Member*p=nullptr;
    bool t;
    string ch;
    file>>ch;//������
    if(file.eof()) return nullptr;
    p=new Member;
    p->set_name(ch);
    file>>t;//���Ա�
    p->set_gender(t);
    file>>ch;//��ȡ����
    p->set_birth(ch);
    file>>t;//��ȡ���
    p->set_married(t);
    file>>ch;//��ȡסַ
    p->set_address(ch);
    file>>t;//��ȡ�Ƿ���
    p->set_alive(t);
    if(!t)
    {
        file>>ch;//�������ڶ�ȡȥ������
        p->set_deathdate(ch);
    }
    file>>ch;//��ȡ��ĸ����
    p->set_parent_name(ch);
    // int n;
    // file>>n;
    // for(int i=0;i<n;i++)
    // {
    //     file>>ch;
    //     p->add_child_name(ch);
    // }
    return p;
}

void FamilyTree::SaveTree(ofstream &file)
{
    deque<Member*>que;
    writemember(file,Root);
    que.push_back(Root);
    Member*p=nullptr;
    while (!que.empty())
    {
        p=que.front();
        for(Member*i:p->pchildren)
        {
            writemember(file,i);
            que.push_back(i);
        }
        que.pop_front();
    }
    
}

void FamilyTree::writemember(ofstream &file,Member*r)
{
    file<<r->name()<<" ";
    file<<(int)r->gender()<<" ";
    file<<r->birth()<<" ";
    file<<(int)r->married()<<" ";
    file<<r->address()<<" ";
    file<<(int)r->alive()<<" ";
    if(!r->alive())
    {
        file<<r->deathdate()<<" ";
    }
    if(r->pparent!=nullptr)
    {
        file<<r->parent()<<" ";
    }
    else
    {
        file<<"0"<<" ";
    }
    file<<endl;
}

void FamilyTree::show()
{
    if (_access(".//familytree", 0) == -1)
	{
		int checkmkdir = _mkdir("familytree");
	}
    ofstream showtree("familytree/showtree.dot",ios::binary);
    showtree<<"graph{"<<endl;

    deque<Member*> que;
    que.push_back(Root);
    Member*p=nullptr;
    while (!que.empty())
    {
        p=que.front();
        for(Member*i:p->pchildren)
        {
            showtree<<p->name()<<"--"<<i->name()<<";"<<endl;
            que.push_back(i);
        }
        que.pop_front();
    }
    
    showtree<<"}";
    showtree.close();
}

Member* FamilyTree::search_name(string name)
{
    if(Root->name()==name) return Root;
    Member*p=nullptr;
    for(Member*i:Root->pchildren)
    {
        p=search_name_dfs(i,name);
        if(p!=nullptr) return p;
    }
    return p;
}
Member* FamilyTree::search_name_dfs(Member*r,string name)
{
    if(r==nullptr) return nullptr;
    else if(r->name()==name) return r;
    else
    {
        Member*p=nullptr;
        for(Member*i:r->pchildren)
        {
            p=search_name_dfs(i,name);
            if(p!=nullptr) return p;
        }
    }
    return nullptr;
}

void FamilyTree::search_birth(string birth,vector<Member*> &list)
{
    if(Root->birth()==birth)
    {
        list.push_back(Root);
        return;
    } 
    for(Member*i:Root->pchildren)
    {
        search_birth_dfs(i,birth,list);
    }
}
void FamilyTree::search_birth_dfs(Member*r,string birth,vector<Member*> &list)
{
    if(r==nullptr)
    {
        return;
    } 
    else if(r->birth()==birth)
    {
        list.push_back(r);
        return;
    } 
    else
    {
        for(Member*i:r->pchildren)
        {
            search_birth_dfs(i,birth,list);
        }
    }
}

void FamilyTree::search_generation(int n,deque<Member*>&list)
{
    if(Root==nullptr) return;
    list.push_back(Root);
    int count=1;
    Member*t=nullptr;
    while (count<n&&!list.empty())
    {
        int n=list.size();
        
        for(int i=0;i<n;i++)
        {
            t=list.front();
            for(Member*p:t->pchildren)
            {
                list.push_back(p);
            }
            list.pop_front();
        }
        count++;
    }
    
}

int FamilyTree::search_relation(string name1,string name2)
{
    int d1=1,d2=1;
    Member*p1=search_name(name1);
    Member*p2=search_name(name2);
    if(p1==nullptr||p2==nullptr) return 0;//�����ֲ�����

    Member*t1=p1,*t2=p2;
    while(t1!=Root)
    {
        t1=t1->pparent;
        d1++;
    }
    while (t2!=Root)
    {
        t2=t2->pparent;
        d2++;
    }
    if(d1<d2)
    {
        if(p2->pparent==p1) return 1;//��ĸ����Ů
        t2=p2;
        while (t2!=nullptr)
        {
            t2=t2->pparent;
            if(t2==p1) return 2;//����
        }
        return 3;//��ϵ�������� 
    }
    else if(d1==d2)
    {
        if(p1->pparent==p2->pparent) return 4;//���ֵܽ���
        else return 5;//��ϵ�ֵܽ���
    }
    else
    {
        if(p1->pparent==p2) return -1;//��Ů�͸�ĸ
        t1=p1;
        while (t1!=nullptr)
        {
            t1=t1->pparent;
            if(t1==p2) return -2;//����
        }
        return -3;//��ϵ��������
        
    }
    
}

bool FamilyTree::Add(Member*p)
{
    Member*q=search_name(p->parent());
    if(q==nullptr) return 0;
    else
    {
        q->add_child_node(p);
        p->set_parent_node(q);
        return 1;
    }
}

bool FamilyTree::Delete(string name)
{
    Member*p=search_name(name);
    if(p==nullptr) return 0;
    else
    {
        Member *parent=p->pparent;
        parent->dele_child(p);
        deque<Member*> que;
        que.push_back(p);
        while (!que.empty())
        {
            Member*q=que.front();
            for(Member*i:q->pchildren)
            {
                que.push_back(i);
            }
            delete q;
            que.pop_front();
        }
    }
    return 1;
}

FamilyTree::~FamilyTree()
{
    deque<Member*> que;
    que.push_back(Root);
    Member*p=nullptr;
    while (!que.empty())
    {
        p=que.front();
        for(Member*i:p->pchildren)
        {
            que.push_back(i);
        }
        que.pop_front();
        delete p;
    }
    
}


#endif