#include<fstream>
#include<iostream>
#include<io.h>
#include<conio.h>
#include"FamilyTree.h"
#include"Member.h"

using namespace std;

//���ѡ���Ƿ���Ч
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
    cout<<"���������N:";
    int n;
    deque<Member*> list;
    cin>>n;
    tree.search_generation(n,list);
    if(list.empty())
    {
        cout<<"�����������Ա��"<<endl;
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
    cout<<"������Ҫ��ѯ��������";
    cin>>name;
    cout<<endl;
    Member*p=tree.search_name(name);
    if(p==nullptr)
    {
        cout<<endl<<"\""<<name<<"\""<<"�����ڣ�"<<endl;
        system("pause");
    }
    else
    {
        p->show();
        cout<<endl;
        if(p->pparent!=nullptr)
        {
            cout<<"��ĸ��Ϣ��"<<endl;
            p->pparent->show();
            cout<<endl;
        }
        else cout<<"�����޸�ĸ��Ϣ!"<<endl<<endl;
        if(!p->pchildren.empty())
        {
            cout<<"��Ů��Ϣ��"<<endl;
            for(Member*i:p->pchildren)
            {
                i->show();
                cout<<endl;
            }
        }
        else cout<<"��ʱû����Ů��"<<endl<<endl;
        system("pause");
    }
}

void SearchBirth(FamilyTree &tree)
{
    while (1)
    {
        system("cls");
        string birth;
        cout<<"�밴\"xxxx-xx-xx\"��ʽ����Ҫ��ѯ�����գ�";
        cin>>birth;
        if(checkbirth(birth))
        {
            cout<<endl;
            vector<Member*> list;
            tree.search_birth(birth,list);
            if(list.empty())
            {
                cout<<"����������Ϊ\""<<birth<<"\"�ĳ�Ա��"<<endl;
                system("pause");
            }
            else
            {
                cout<<"����������Ϊ\""<<birth<<"\"�ĳ�Ա������"<<endl<<endl;
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
            cout<<"����ȷ�������գ�"<<endl;
            system("pause");
        }
    }
    
    
    
}

void SearchRelation(FamilyTree &tree)
{
    system("cls");
    string name1,name2;
    cout<<"������Ҫ��ѯ������"<<endl;
    cout<<"����1��";
    cin>>name1;
    cout<<"����2��";
    cin>>name2;
    cout<<endl<<endl<<endl;
    int relate=tree.search_relation(name1,name2);
    if(relate==0)
    {
        cout<<"�����ֲ����ڼ������У�"<<endl;
        system("pause");
    }
    else if(relate==1)
    {
        cout<<name1<<"��"<<name2<<"�ĸ�ĸ"<<endl<<endl;
        system("pause");
    }
    else if(relate==2)
    {
        cout<<name1<<"��"<<name2<<"�������ϵ"<<endl<<endl;
        system("pause");
    }
    else if(relate==3)
    {
        cout<<name1<<"��"<<name2<<"����ϵ����������ϵ"<<endl<<endl;
        system("pause");
    }
    else if(relate==4)
    {
        cout<<name1<<"��"<<name2<<"���ֵܽ��ù�ϵ"<<endl<<endl;
        system("pause");
    }
    else if(relate==5)
    {
        cout<<name1<<"��"<<name2<<"����ϵ�ֵܽ��ù�ϵ"<<endl<<endl;
        system("pause");
    }
    else if(relate==-1)
    {
        cout<<name2<<"��"<<name1<<"�ĸ�ĸ"<<endl<<endl;
        system("pause");
    }
    else if(relate==-2)
    {
        cout<<name2<<"��"<<name1<<"�������ϵ"<<endl<<endl;
        system("pause");
    }
    else
    {
        cout<<name2<<"��"<<name1<<"����ϵ����������ϵ"<<endl<<endl;
        system("pause");
    }
}

//��Ϣ��ѯģ��
void Search(FamilyTree &tree)
{
    bool exit=true;
    while(exit)
    {
        system("cls");
        cout<<"<<����Esc"<<endl;
        cout<<endl;
        cout<<"        ���׹���ϵͳ"<<endl;
        cout<<"          ��Ϣ��ѯ"<<endl;
        cout<<endl;
        cout<<"       1.��ѯ��n��ȫ����Ա"<<endl;
        cout<<"       2.��������ѯ"<<endl;
        cout<<"       3.�����ղ�ѯ"<<endl;
        cout<<"       4.��ѯ���˹�ϵ"<<endl;

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

void AddMember(FamilyTree&tree)//��ӳ�Ա
{
    system("cls");

    Member*p=new Member;
    string str;
    bool t;
    cout<<"�������³�Ա��Ϣ��"<<endl;
    //������
    cout<<"����    ��";
    cin>>str;
    if(tree.search_name(str)!=nullptr)
    {
        cout<<"�Ѵ�����Ϊ"<<str<<"�ĳ�Ա��"<<endl;
        system("pause");
        return;
    }
    p->set_name(str);
    //���Ա�
    cout<<"�Ա�(1/0)��";
    cin>>t;
    p->set_gender(t);
    //������
    cout<<"����    ��";
    cin>>str;
    while(!checkbirth(str))
    {
        cout<<"�밴��\"xxxx-xx-xx\"��ʽ��ȷ�������գ�"<<endl;
        cout<<"�����������գ�";
        cin>>str;
    }
    p->set_birth(str);
    //���
    cout<<"���(1/0)��";
    cin>>t;
    p->set_married(t);
    //סַ
    cout<<"סַ    ��";
    cin>>str;
    p->set_address(str);
    //����
    cout<<"����(1/0)��";
    cin>>t;
    p->set_alive(t);
    if(!t)
    {
        cout<<"ȥ�����ڣ�";
        cin>>str;
        p->set_deathdate(str);
    }
    //����ĸ����
    cout<<"��ĸ    ��";
    cin>>str;
    while (tree.search_name(str)==nullptr)
    {
        cout<<"��ĸ���ֲ����ڣ�"<<endl<<"�������룺";
        cin>>str;
    }
    
    p->set_parent_name(str);

    tree.Add(p);

    ofstream file("family.txt");
    tree.SaveTree(file);
    file.close();

    system("pause");


}

void DeleteMember(FamilyTree&tree)//ɾ����Ա��������
{
    system("cls");
    cout<<"������Ҫɾ���ĳ�Ա���֣�";
    string name;
    cin>>name;
    if(tree.Delete(name))
    {
         ofstream file("family.txt");
        tree.SaveTree(file);
        file.close();
        cout<<"ɾ���ɹ���"<<endl;
        system("pause");
    }
    else
    {
        cout<<"�����ڸó�Ա��ɾ��ʧ�ܣ�"<<endl;
        system("pause");
    }
}

void EditMember(FamilyTree&tree)//�޸ĳ�Ա��Ϣ
{
    system("cls");
    cout<<"������Ҫ�޸ĳ�Ա�����֣�";
    string name;
    cin>>name;
    Member*p=tree.search_name(name);
    if(p==nullptr)
    {
        cout<<"�ó�Ա�����ڣ�"<<endl;
        system("pause");
    }
    else
    {
        cout<<endl;
        p->show();
        cout<<endl<<"������ó�Ա�µ���Ϣ��"<<endl;
        string str;
        bool t;
        cout<<"�������³�Ա��Ϣ��"<<endl;
        //������
        cout<<"����    ��";
        cin>>str;
        if(tree.search_name(str)!=nullptr)
        {
            cout<<"�Ѵ�����Ϊ"<<str<<"�ĳ�Ա��"<<endl;
            system("pause");
            return;
        }
        p->set_name(str);
        //���Ա�
        cout<<"�Ա�(1/0)��";
        cin>>t;
        p->set_gender(t);
        //������
            cout<<"����    ��";
        cin>>str;
        while(!checkbirth(str))
        {
            cout<<"�밴��\"xxxx-xx-xx\"��ʽ��ȷ�������գ�"<<endl;
            cout<<"�����������գ�";
            cin>>str;
        }
        p->set_birth(str);
        //���
        cout<<"���(1/0)��";
        cin>>t;
        p->set_married(t);
        //סַ
        cout<<"סַ    ��";
        cin>>str;
        p->set_address(str);
        //����
        cout<<"����(1/0)��";
        cin>>t;
        p->set_alive(t);
        if(!t)
        {
            cout<<"ȥ�����ڣ�";
            cin>>str;
            p->set_deathdate(str);
        }
        ofstream file("family.txt");
        tree.SaveTree(file);
        file.close();

        cout<<"��Ϣ�޸ĳɹ���"<<endl;
        system("pause");
    }
}

//��Ϣ����ģ��
void Manage(FamilyTree&tree)
{
    bool exit=true;
    while(exit)
    {
        system("cls");
        cout<<"<<����Esc"<<endl;
        cout<<endl;
        cout<<"        ���׹���ϵͳ"<<endl;
        cout<<"          ��Ϣ����"<<endl;
        cout<<endl;
        cout<<"       1.��ӳ�Ա"<<endl;
        cout<<"       2.ɾ����Ա���亢��"<<endl;
        cout<<"       3.�޸ĳ�Ա��Ϣ"<<endl;

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

//������չʾ
void show_the_tree(FamilyTree&tree)
{
    system("cls");
    tree.show();
    cout<<"����ͼ��չʾ��'familytree/showtree.dot'�ļ��У���ʹ��Graphviz interaction preview������"<<endl;
    system("pause");
}

int main()
{
    system("title ���׹���ϵͳ");

    ifstream file("family.txt");
    FamilyTree tree;
    tree.CreateTree(file);
    file.close();

    bool exit=true;
    while(exit)
    {
        cout<<"        ���׹���ϵͳ"<<endl;
        cout<<"           ���˵�"<<endl;
        cout<<"       1.��ѯ��Ϣ"<<endl;
        cout<<"       2.�޸���Ϣ"<<endl;
        cout<<"       3.������һ��"<<endl;
        cout<<"       4.�˳�ϵͳ"<<endl;

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