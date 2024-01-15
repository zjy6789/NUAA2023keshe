#ifndef _MEMBER_H_
#define _MEMBER_H_

#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<algorithm>

using namespace std;

class Member
{
private:
    string Name;
    bool Gender;
    string Birthday;
    bool Married;
    string Address;
    bool Alive;
    string DeathDate;
    string Parent;
    vector<string> Children;

public:
    Member*pparent;
    vector<Member*> pchildren;
    Member():pparent(nullptr){};
    ~Member(){};

    string name(){return Name;}
    bool gender(){return Gender;}
    string birth(){return Birthday;}
    bool married(){return Married;}
    string address(){return Address;}
    bool alive(){return Alive;}
    string deathdate(){return DeathDate;}
    string parent(){return Parent;}
    string children(int n){return Children[n];}

    void set_name(string name){Name=name;}
    void set_gender(bool gender){Gender=gender;}
    void set_birth(string birth){Birthday=birth;}
    void set_married(bool married){Married=married;}
    void set_address(string address){Address=address;}
    void set_alive(bool alive){Alive=alive;}
    void set_deathdate(string deathdate){DeathDate=deathdate;}
    void set_parent_name(string parent){Parent=parent;}
    void set_parent_node(Member*parent){pparent=parent;Parent=parent->name();}
    void add_child_name(string child){Children.push_back(child);}
    void add_child_node(Member*child){Children.push_back(child->name());pchildren.push_back(child);}

    void show();

    void dele_child(Member*child);
};

void Member::show()
{
    cout<<"姓名    ："<<Name<<endl;
    cout<<"性别    ：";
    if(Gender) cout<<"男"<<endl;
    else cout<<"女"<<endl;
    cout<<"生日    ："<<Birthday<<endl;
    cout<<"婚否    ：";
    if(Married) cout<<"已婚"<<endl;
    else cout<<"未婚"<<endl;
    cout<<"住址    ："<<Address<<endl;
    if(!Alive)
    {
        cout<<"已逝    ："<<DeathDate<<endl;
    }
    cout<<endl;
}

void Member::dele_child(Member*child)
{
    Children.erase(remove(Children.begin(), Children.end(), child->name()), Children.end());
    //Children.pop_back();
    pchildren.erase(remove(pchildren.begin(), pchildren.end(), child), pchildren.end());
    //pchildren.pop_back();
}

#endif

