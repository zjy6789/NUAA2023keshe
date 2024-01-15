#include <iostream>
#include <fstream>
#include "B-Tree.h"
using namespace std;

bool JudgeSu(int n)
{// 判断当前数字是否为素数 
	if (n == 1) return false;
	for (int i = 2; i < n; i++)
	{
		if (n % i == 0) {
			//			cout << i;
			return false;
		}
	}
	return true;
}

void question1(BTree root)
{
	cout << "\n1.依次查询200-300的每个数是否在B-tree中，将结果写入文件b-tree1.txt\n";
	fstream file;
	file.open("b-tree1.txt", ios::out);
	if (!file.is_open()) {
		cout << "文件打开失败！\n";
		exit(0);
	}

	for (int i = 200; i <= 300; i++) 
	{
		Result r = SearchBTree(root, i);
		if (r.tag == 0) 
		{
			file << i << " no" << endl;
			cout << i << " no" << endl;
		}
		else 
		{
			file << i << " yes" << endl;
			cout << i << " yes" << endl;
		}
	}
	file.close();
	cout << "查询并写入完毕!\n";
	//	Traverse(root);
}
void question2(BTree& root)
{
	cout << "\n2.依次删除500-2000中的每个质数，再查询 600-700之间的每个质数是否在, 将结果写入文件b-tree2.txt\n";
	fstream file;
	file.open("b-tree2.txt", ios::out);
	if (!file.is_open()) {
		cout << "文件打开失败！\n";
		exit(0);
	}
	for (int i = 500; i <= 2000; i++) 
	{
		if (JudgeSu(i)) 
		{
			DeleteBTNode(i, root);
		}
	}
	cout << " \n删除完毕!\n";
	//	Traverse(root);
	for (int i = 600; i <= 700; i++) 
	{
		if (JudgeSu(i)) 
		{
			Result r = SearchBTree(root, i);
			if (r.tag == 0) 
			{
				file << i << " no" << endl;
				cout << i << " no" << endl;
			}
			else 
			{
				file << i << " yes" << endl;
				cout << i << " yes" << endl;
			}
		}
	}
	cout << " \n写入完毕!\n";
	file.close();
}
void question3(BTree& root)
{
	cout << "\n3.在2的基础上的B-tree，依次插入1-1000的所有偶数，依次查询100-200的每个偶数是否在B-tree中, 将结果写入文件b-tree3.txt\n";
	fstream file;
	file.open("b-tree3.txt", ios::out);
	if (!file.is_open()) 
	{
		cout << "文件打开失败！\n";
		exit(0);
	}
	for (int i = 2; i <= 1000; i += 2)
	 {
		InsertBTNode(root, i);
	}
	for (int i = 100; i <= 200; i++)
	 {
		Result r = SearchBTree(root, i);
		if (r.tag == 0) 
		{
			file << i << " no" << endl;
			cout << i << " no" << endl;
		}
		else 
		{
			file << i << " yes" << endl;
			cout << i << " yes" << endl;
		}
	}
	file.close();
	cout << "查询并写入完毕!\n";
}

int main()
{
    BTree tree=NULL;
    ifstream file("data.txt");//打开文件读数据
    int i;
    file>>i;
    while(!file.eof())
    {
        InsertBTNode(tree,i);//将数据插入B-树中
        file>>i;
    }
    question1(tree);
    question2(tree);
    question3(tree);

    system("pause");
    return 0;
}

