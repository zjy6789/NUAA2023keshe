#include <iostream>
#include <fstream>
#include "B-Tree.h"
using namespace std;

bool JudgeSu(int n)
{// �жϵ�ǰ�����Ƿ�Ϊ���� 
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
	cout << "\n1.���β�ѯ200-300��ÿ�����Ƿ���B-tree�У������д���ļ�b-tree1.txt\n";
	fstream file;
	file.open("b-tree1.txt", ios::out);
	if (!file.is_open()) {
		cout << "�ļ���ʧ�ܣ�\n";
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
	cout << "��ѯ��д�����!\n";
	//	Traverse(root);
}
void question2(BTree& root)
{
	cout << "\n2.����ɾ��500-2000�е�ÿ���������ٲ�ѯ 600-700֮���ÿ�������Ƿ���, �����д���ļ�b-tree2.txt\n";
	fstream file;
	file.open("b-tree2.txt", ios::out);
	if (!file.is_open()) {
		cout << "�ļ���ʧ�ܣ�\n";
		exit(0);
	}
	for (int i = 500; i <= 2000; i++) 
	{
		if (JudgeSu(i)) 
		{
			DeleteBTNode(i, root);
		}
	}
	cout << " \nɾ�����!\n";
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
	cout << " \nд�����!\n";
	file.close();
}
void question3(BTree& root)
{
	cout << "\n3.��2�Ļ����ϵ�B-tree�����β���1-1000������ż�������β�ѯ100-200��ÿ��ż���Ƿ���B-tree��, �����д���ļ�b-tree3.txt\n";
	fstream file;
	file.open("b-tree3.txt", ios::out);
	if (!file.is_open()) 
	{
		cout << "�ļ���ʧ�ܣ�\n";
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
	cout << "��ѯ��д�����!\n";
}

int main()
{
    BTree tree=NULL;
    ifstream file("data.txt");//���ļ�������
    int i;
    file>>i;
    while(!file.eof())
    {
        InsertBTNode(tree,i);//�����ݲ���B-����
        file>>i;
    }
    question1(tree);
    question2(tree);
    question3(tree);

    system("pause");
    return 0;
}

