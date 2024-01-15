#include<fstream>
#include<iostream>
#include<io.h>
#include<conio.h>
#include"FamilyTree.h"
#include"Member.h"

using namespace std;

//检查选择是否有效
bool checkchoose(int a,char b)
{
    char up=0;
    switch(a)
    {
    case 0:up='3';break;
    case 1:up='4';break;
    }
    if(b>'0'&&b<=up)
        return true;
    else 
        return false;
}

bool checkbirth(string birth)
{
    if(birth.size()==10)
    {
        int i;
        for(i=0;i<10;i++)
        {
            if((i==4||i==7)&&birth[i]=='-')
            {
                continue;
            }
            else if(birth[i]<'0'||birth[i]>'9')
            {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

void SearchGenerationN(FamilyTree &tree)
{
    system("cls");
    cout<<"请输入代数N:";
    int n;
    deque<Member*> list;
    cin>>n;
    tree.search_generation(n,list);
    if(list.empty())
    {
        cout<<"不存在这代成员！"<<endl;
    }
    else
    {
        for(Member*i:list)
        {
            i->show();
        }
    }
    cout<<endl;
    system("pause");
}

void SearchName(FamilyTree &tree)
{
    system("cls");
    string name;
    cout<<"请输入要查询的姓名：";
    cin>>name;
    cout<<endl;
    Member*p=tree.search_name(name);
    if(p==nullptr)
    {
        cout<<endl<<"\""<<name<<"\""<<"不存在！"<<endl;
        system("pause");
    }
    else
    {
        p->show();
        cout<<endl;
        if(p->pparent!=nullptr)
        {
            cout<<"父母信息："<<endl;
            p->pparent->show();
            cout<<endl;
        }
        else cout<<"暂无无父母信息!"<<endl<<endl;
        if(!p->pchildren.empty())
        {
            cout<<"子女信息："<<endl;
            for(Member*i:p->pchildren)
            {
                i->show();
                cout<<endl;
            }
        }
        else cout<<"暂时没有子女！"<<endl<<endl;
        system("pause");
    }
}

void SearchBirth(FamilyTree &tree)
{
    while (1)
    {
        system("cls");
        string birth;
        cout<<"请按\"xxxx-xx-xx\"格式输入要查询的生日：";
        cin>>birth;
        if(checkbirth(birth))
        {
            cout<<endl;
            vector<Member*> list;
            tree.search_birth(birth,list);
            if(list.empty())
            {
                cout<<"不存在生日为\""<<birth<<"\"的成员！"<<endl;
                system("pause");
            }
            else
            {
                cout<<"以下是生日为\""<<birth<<"\"的成员名单："<<endl<<endl;
                for(Member*i:list)
                {
                    i->show();
                    cout<<endl;
                }
                system("pause");
            }
            break;
        }
        else
        {
            cout<<"请正确输入生日！"<<endl;
            system("pause");
        }
    }
    
    
    
}

void SearchRelation(FamilyTree &tree)
{
    system("cls");
    string name1,name2;
    cout<<"请输入要查询的姓名"<<endl;
    cout<<"姓名1：";
    cin>>name1;
    cout<<"姓名2：";
    cin>>name2;
    cout<<endl<<endl<<endl;
    int relate=tree.search_relation(name1,name2);
    if(relate==0)
    {
        cout<<"有名字不存在家谱树中！"<<endl;
        system("pause");
    }
    else if(relate==1)
    {
        cout<<name1<<"是"<<name2<<"的父母"<<endl<<endl;
        system("pause");
    }
    else if(relate==2)
    {
        cout<<name1<<"和"<<name2<<"是祖孙关系"<<endl<<endl;
        system("pause");
    }
    else if(relate==3)
    {
        cout<<name1<<"和"<<name2<<"是旁系长辈和晚辈关系"<<endl<<endl;
        system("pause");
    }
    else if(relate==4)
    {
        cout<<name1<<"和"<<name2<<"是兄弟姐妹关系"<<endl<<endl;
        system("pause");
    }
    else if(relate==5)
    {
        cout<<name1<<"和"<<name2<<"是旁系兄弟姐妹关系"<<endl<<endl;
        system("pause");
    }
    else if(relate==-1)
    {
        cout<<name2<<"是"<<name1<<"的父母"<<endl<<endl;
        system("pause");
    }
    else if(relate==-2)
    {
        cout<<name2<<"和"<<name1<<"是祖孙关系"<<endl<<endl;
        system("pause");
    }
    else
    {
        cout<<name2<<"和"<<name1<<"是旁系长辈和晚辈关系"<<endl<<endl;
        system("pause");
    }
}

//信息查询模块
void Search(FamilyTree &tree)
{
    bool exit=true;
    while(exit)
    {
        system("cls");
        cout<<"<<返回Esc"<<endl;
        cout<<endl;
        cout<<"        家谱管理系统"<<endl;
        cout<<"          信息查询"<<endl;
        cout<<endl;
        cout<<"       1.查询第n代全部成员"<<endl;
        cout<<"       2.按姓名查询"<<endl;
        cout<<"       3.按生日查询"<<endl;
        cout<<"       4.查询两人关系"<<endl;

        char choose=0;
        while(true)
        {
            choose=_getch();
            if(checkchoose(1,choose)||choose==27)
                break;
        }
        if(choose==27)
            break;
        switch(choose)
        {
            case '1':SearchGenerationN(tree);   break;
            case '2':SearchName(tree);      break;
            case '3':SearchBirth(tree);   break;
            case '4':SearchRelation(tree);   break;
        }
    }
}

void AddMember(FamilyTree&tree)//添加成员
{
    system("cls");

    Member*p=new Member;
    string str;
    bool t;
    cout<<"请输入新成员信息："<<endl;
    //读姓名
    cout<<"姓名    ：";
    cin>>str;
    if(tree.search_name(str)!=nullptr)
    {
        cout<<"已存在名为"<<str<<"的成员！"<<endl;
        system("pause");
        return;
    }
    p->set_name(str);
    //读性别
    cout<<"性别(1/0)：";
    cin>>t;
    p->set_gender(t);
    //读生日
    cout<<"生日    ：";
    cin>>str;
    while(!checkbirth(str))
    {
        cout<<"请按照\"xxxx-xx-xx\"格式正确输入生日！"<<endl;
        cout<<"重新输入生日：";
        cin>>str;
    }
    p->set_birth(str);
    //婚否
    cout<<"婚否(1/0)：";
    cin>>t;
    p->set_married(t);
    //住址
    cout<<"住址    ：";
    cin>>str;
    p->set_address(str);
    //健在
    cout<<"健在(1/0)：";
    cin>>t;
    p->set_alive(t);
    if(!t)
    {
        cout<<"去世日期：";
        cin>>str;
        p->set_deathdate(str);
    }
    //读父母姓名
    cout<<"父母    ：";
    cin>>str;
    while (tree.search_name(str)==nullptr)
    {
        cout<<"父母名字不存在！"<<endl<<"重新输入：";
        cin>>str;
    }
    
    p->set_parent_name(str);

    tree.Add(p);

    ofstream file("family.txt");
    tree.SaveTree(file);
    file.close();

    system("pause");


}

void DeleteMember(FamilyTree&tree)//删除成员及其子树
{
    system("cls");
    cout<<"请输入要删除的成员名字：";
    string name;
    cin>>name;
    if(tree.Delete(name))
    {
         ofstream file("family.txt");
        tree.SaveTree(file);
        file.close();
        cout<<"删除成功！"<<endl;
        system("pause");
    }
    else
    {
        cout<<"不存在该成员，删除失败！"<<endl;
        system("pause");
    }
}

void EditMember(FamilyTree&tree)//修改成员信息
{
    system("cls");
    cout<<"请输入要修改成员的名字：";
    string name;
    cin>>name;
    Member*p=tree.search_name(name);
    if(p==nullptr)
    {
        cout<<"该成员不存在！"<<endl;
        system("pause");
    }
    else
    {
        cout<<endl;
        p->show();
        cout<<endl<<"请输入该成员新的信息："<<endl;
        string str;
        bool t;
        cout<<"请输入新成员信息："<<endl;
        //读姓名
        cout<<"姓名    ：";
        cin>>str;
        if(tree.search_name(str)!=nullptr)
        {
            cout<<"已存在名为"<<str<<"的成员！"<<endl;
            system("pause");
            return;
        }
        p->set_name(str);
        //读性别
        cout<<"性别(1/0)：";
        cin>>t;
        p->set_gender(t);
        //读生日
            cout<<"生日    ：";
        cin>>str;
        while(!checkbirth(str))
        {
            cout<<"请按照\"xxxx-xx-xx\"格式正确输入生日！"<<endl;
            cout<<"重新输入生日：";
            cin>>str;
        }
        p->set_birth(str);
        //婚否
        cout<<"婚否(1/0)：";
        cin>>t;
        p->set_married(t);
        //住址
        cout<<"住址    ：";
        cin>>str;
        p->set_address(str);
        //健在
        cout<<"健在(1/0)：";
        cin>>t;
        p->set_alive(t);
        if(!t)
        {
            cout<<"去世日期：";
            cin>>str;
            p->set_deathdate(str);
        }
        ofstream file("family.txt");
        tree.SaveTree(file);
        file.close();

        cout<<"信息修改成功！"<<endl;
        system("pause");
    }
}

//信息管理模块
void Manage(FamilyTree&tree)
{
    bool exit=true;
    while(exit)
    {
        system("cls");
        cout<<"<<返回Esc"<<endl;
        cout<<endl;
        cout<<"        家谱管理系统"<<endl;
        cout<<"          信息管理"<<endl;
        cout<<endl;
        cout<<"       1.添加成员"<<endl;
        cout<<"       2.删除成员及其孩子"<<endl;
        cout<<"       3.修改成员信息"<<endl;

        char choose=0;
        while(true)
        {
            choose=_getch();
            if(checkchoose(1,choose)||choose==27)
                break;
        }
        if(choose==27)
            break;
        switch(choose)
        {
            case '1':AddMember(tree);break;
            case '2':DeleteMember(tree);break;
            case '3':EditMember(tree);break;
        }
    }
}

//家谱树展示
void show_the_tree(FamilyTree&tree)
{
    system("cls");
    tree.show();
    cout<<"家谱图已展示在'familytree/showtree.dot'文件中，请使用Graphviz interaction preview插件浏览"<<endl;
    system("pause");
}

int main()
{
    system("title 家谱管理系统");

    ifstream file("family.txt");
    FamilyTree tree;
    tree.CreateTree(file);
    file.close();

    bool exit=true;
    while(exit)
    {
        cout<<"        家谱管理系统"<<endl;
        cout<<"           主菜单"<<endl;
        cout<<"       1.查询信息"<<endl;
        cout<<"       2.修改信息"<<endl;
        cout<<"       3.家谱树一览"<<endl;
        cout<<"       4.退出系统"<<endl;

        char choose=0;
        while(true)
        {
            choose=_getch();
            if(checkchoose(1,choose))
                break;
        }
        switch(choose)
        {
        case '1':Search(tree);break;
        case '2':Manage(tree);break;
        case '3':show_the_tree(tree);break;
        case '4':exit=false;break;
        }
        system("cls");
    }

    return 0;
}