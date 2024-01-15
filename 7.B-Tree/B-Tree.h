#ifndef _B_TREE_H_
#define _B_TREE_H_

#include <iostream>
#include <fstream>
#include <deque>
#define KeyType int
using namespace std;
const int m = 4;
const int Min = (m - 1) / 2;		// ���ټ��� 

typedef struct BTNode
{
	int keynum;				// �ڵ��йؼ��ֵĸ��������ڵ�Ĵ�С
	KeyType K[m + 1]; 		// �ؼ��������� 0�ŵ�Ԫδ��
	BTNode* ptr[m + 1];		// ����ָ������
}BTNode, * BTree;

//	������Ϊ���Ҳ����ķ���ֵ 
typedef struct Result 
{		
	BTNode* pre;			// ��ǰ�ڵ��˫�׽ڵ�
	BTNode* now;			// ��ǰ�ڵ�
	int seq;				// ��ʾ�ؼ��ֵ����
	int tag;				// ���Ҳ����У���ʾ�ҵ���� 
}Result;

// �ڵ�ǰ��Ѱ��key
int Search(BTNode* ptr, KeyType key)
{
    //���ҵ��򷵻عؼ�����ţ� ���򷵻ؽ�����һ��ڵ���� 
	int i = 0;
	if (ptr->K[1] > key) return i;	//	����0��λ�ã���Ϊ��һ��ڵ�Ľ���λ�� 
	for (i = 1; i < ptr->keynum; i++) 
	{
		if (ptr->K[i] == key) break;
		else if (ptr->K[i] < key && ptr->K[i + 1] > key) break;
	}
	return i;
}

// ��B-���в��ҹؼ���Ϊkey�Ľڵ�
Result SearchBTree(BTree root, KeyType key)
{
    //���ҵ��򷵻ص�ǰ�ڵ㣬�ؼ�����ţ�˫�׽ڵ㣬
    // δ�ҵ��򷵻ؽڵ���Ҫ�����λ�ã�key�Ĺؼ���ΪӦ����ָ��pt��ָ��ڵ��еĵ�i���͵�i+1���ڵ�֮�䣩
    //�Լ�˫�׽ڵ�, ����˫�׽ڵ㣬�ֲ���BTNode�в���parent��ȱ�ݣ�ͬʱҲ���ö���ά��parentָ�� 

	BTNode* p = root;					// �����������Ľڵ� 
	BTNode* pre = NULL;					// ��¼��ǰ�ڵ��˫�׽ڵ� 
	int found = 0;
	int i = 0;							// �ؼ������ 
	while (p && !found) 
	{
		i = Search(p, key);				// �ڵ�ǰ��Ѱ��key
		if (i != 0 && p->K[i] == key) 
		{
			found = 1;
		}
		else 
		{
			pre = p;
			p = p->ptr[i];
		}
	}
	return Result{ pre, p, i, found };
}

// �ڸò���в������ 
void Insert(BTNode* p, int k, BTNode* ap, KeyType x)
{// �ڸò���в������ 
	int i = 0;
	for (i = p->keynum; i > k; i--) 
	{
		p->K[i + 1] = p->K[i];
	}
	p->K[i + 1] = x;
	for (i = p->keynum; i > k; i--) 
	{
		p->ptr[i + 1] = p->ptr[i];
	}
	p->ptr[i + 1] = ap;

	p->keynum++;
}


// ���Ѳ��� 
void Split(BTNode* p, BTNode*& ap, int s)
{
	int i = 0;
	int j = 1;
	//	if (ap)	delete ap;
	ap = new BTNode;
	for (i = s + 1; i <= m; i++)
	 {				// ��s֮��Ĺؼ��ַ��ѵ��µĽڵ��� 
		ap->K[j++] = p->K[i];
	}
	j = 0;
	for (i = s; i <= m; i++) 
	{					// ��s֮��ĺ���ָ����ѵ��µĽڵ��� 
		ap->ptr[j++] = p->ptr[i];
	}

	p->keynum -= (m - s + 1);					// ���¹ؼ������� 
	ap->keynum = m - s;
}


// �����µĸ��ڵ� 
void NewRoot(BTree& root, BTNode* ap, int x)
{
	BTNode* T = new BTNode;			
	T->keynum = 1;
	T->K[1] = x;
	T->ptr[0] = root;
	T->ptr[1] = ap;

	root = T;
}

// ��B-���в���ڵ㣬
int InsertBTNode(BTree& root, KeyType key)
{
    //����Ҫ���в��Ҹùؼ��ֲ��������ؼ����Ѵ��ڣ�ֱ�ӷ��أ�������в��������
    //	�����ж��Ƿ���Ҫ���з��Ѳ���
	if (!root) 
    {
		root = new BTNode;
		root->keynum = 1;
		root->K[1] = key;
		root->ptr[0] = root->ptr[1] = NULL;
		return 1;
	}
	BTNode* p = root;					// �����������Ľڵ� 
	BTNode* ap = NULL;					// Ҫ����ڵ��Ӧ��ptrָ�� 
	int seq = 0;
	int finished = 0;
	KeyType x = key;						// ������Ĺؼ��� 
	Result r = SearchBTree(root, key);
	if (r.tag == 1) 
	{
		return 1;
	}
	else 
	{
		seq = r.seq;
		p = r.pre;
	}

	while (p && !finished)
	 {
		Insert(p, seq, ap, x);
		if (p->keynum < m) finished = 1;
		else {
			int s = (m + 1) / 2;					// ���ѵ�λ��
			x = p->K[s];
			r = SearchBTree(root, x);				// �ҵ�ǰ�ڵ�ĸ��ڵ�
			Split(p, ap, s);						// ����
			if (p == root)	break;					// �Ѿ��Ǹ��ڵ��ˣ�û�и��ڵ�
			else p = r.pre;							// ���ظ��ڵ�
			seq = Search(p, x);						// �ڸ��ڵ���Ӧ�ò����λ��
		}
	}
	if (!finished) NewRoot(root, ap, x);
	return 1;
}

// ��������ùؼ����滻��ǰ�ڵ�ؼ���
void ChangeKey(BTNode* myNode, int pos)
{// ѡ���Һ�������С�����滻 
	BTNode* temp = myNode->ptr[pos];
	while (temp->ptr[0]) {
		temp = temp->ptr[0];
	}
	myNode->K[pos] = temp->K[1];
}

// �ڵ�ǰ�ڵ�ɾ��pos���ڹؼ�����ָ�� 
void RemoveNode(BTNode* myNode, int pos)
{// �ڵ�ǰ�ڵ�ɾ��pos���ڹؼ�����ָ�� 
	int j = pos;
	while (j < myNode->keynum)
	 {
		myNode->K[j] = myNode->K[j + 1];
		myNode->ptr[j] = myNode->ptr[j + 1];
		j++;
	}
	myNode->keynum--;
}

// ���������Ҷ˼�������ǰ�ڵ㣬���ѵ�ǰ�ڵ��ж�Ӧ�������Һ��ӵ�һ������
void RightChange(BTNode* myNode, int pos)
{
	// ����ǰ�ڵ��м��������Һ��ӽڵ��� 
	BTNode* x = myNode->ptr[pos];
	int j = x->keynum;
	while (j >= 1) 
	{
		x->K[j+1] = x->K[j];
		x->ptr[j+1] = x->ptr[j];
		j--;
	}
	x->keynum++;
	x->K[1] = myNode->K[pos];
	x->ptr[1] = x->ptr[0];
    // �ڵ�ǰ�ڵ��У����Ѿ������Һ��ӵļ�ԭ����λ�û�Ϊ���������Ҷ˼� 
	BTNode* w = myNode->ptr[pos - 1];
	myNode->K[pos] = w->K[w->keynum];
	x->ptr[0] = w->ptr[w->keynum];
    //	ɾ�����������Ҷ˼� 
	w->keynum--;
}

// ���Һ��ӵ�һ����������ǰ�ڵ㣬���ѵ�ǰ�ڵ��ж�Ӧ�������������Ҷ˼�
void LeftChange(BTNode* myNode, int pos)
{
	BTNode* w = myNode->ptr[pos - 1];
	BTNode* x = myNode->ptr[pos];
	// ����ǰ�ڵ��м����������ӽڵ��� 
	w->keynum++;
	w->K[w->keynum] = myNode->K[pos];
	//	w->ptr[w->keynum] = myNode->ptr[]	
	w->ptr[w->keynum] = x->ptr[0];
	// �ڵ�ǰ�ڵ��У����Ѿ��������ӵļ�ԭ����λ�û�Ϊ�Һ����е�һ���� 
	myNode->K[pos] = x->K[1];
	//	myNode->ptr[pos] = x->ptr[1];
	//	ɾ���Һ����е�һ���� 
	x->ptr[0] = x->ptr[1];
	int j = 1;
	while (j < x->keynum) 
	{
		x->K[j] = x->K[j + 1];
		x->ptr[j] = x->ptr[j + 1];
		j++;
	}
	x->keynum--;
}

// �������Һ���ͨ����ǰ�ڵ�ļ����кϲ�
void Merge(BTNode* myNode, int pos)
{
	BTNode* w = myNode->ptr[pos - 1];
	BTNode* x = myNode->ptr[pos];
	// ����ǰ�ڵ�ļ��ϲ������� 
	w->keynum++;
	w->K[w->keynum] = myNode->K[pos];
	w->ptr[w->keynum] = x->ptr[0];
	// ���Һ���Ҳ�������� 
	int j = 1;
	while (j <= x->keynum) 
	{
		w->keynum++;
		w->K[w->keynum] = x->K[j];
		w->ptr[w->keynum] = x->ptr[j];
		j++;
	}
	// ��ǰ�ڵ�ɾ���Ѳ������ӵļ�
	j = pos;
	while (j < myNode->keynum) 
	{
		myNode->K[j] = myNode->K[j + 1];
		myNode->ptr[j] = myNode->ptr[j + 1];
		j++;
	}
	myNode->keynum--;
	delete x;
}

// �����ڵ�
void AdjustNode(BTNode* myNode, int pos)
{// myNode->ptr[pos]�ǲ���ԣ�� 
	if (!pos) {									// 0��ָ���ұ�����ԣ,
		if (myNode->ptr[1]->keynum > Min) 
		{		// ���ֵܸ�ԣ 
			LeftChange(myNode, 1); 				// ���ֵ�ͨ��˫�׽ڵ�����ֵ�һ���� 
		}
		else {									// ���ֵ�Ҳ��ϲ��� 
			Merge(myNode, 1);
		}
	}
	else if (pos != myNode->keynum) 
	{
		if (myNode->ptr[pos + 1]->keynum > Min)
		 {			// ���ֵܸ�ԣ 
			LeftChange(myNode, pos);
		}
		else if (myNode->ptr[pos - 1]->keynum > Min)
		 {		// ���ֵܸ�ԣ 
			RightChange(myNode, pos);
		}
		else 
		{												// ������ԣ���ϲ� 
			Merge(myNode, pos);
		}
	}
	else {													// ������ԣ�� ���Ҷ�ָ�� 
		if (myNode->ptr[myNode->keynum]->keynum > Min) {
			RightChange(myNode, myNode->keynum);
		}
		else {
			Merge(myNode, myNode->keynum);
		}
	}
}

// ɾ���ؼ���Ϊkey�Ľڵ� 
int DelKeyFromNode(KeyType key, BTNode* myNode)
{
	int pos, flag = 0;
	if (myNode) 
	{
		// �ڵ�ǰ�ڵ��в��ҹؼ���key 
		if (myNode->K[1] > key) {
			pos = 0;
			flag = 0;
		}
		else 
		{
			for (pos = myNode->keynum; (key < myNode->K[pos]) && pos > 1; pos--)
				;
			if (myNode->K[pos] == key) 
			{
				flag = 1;
			}
			else {
				flag = 0;
			}
		}
		// ������ϣ����ݲ��ҽ���ж�֮����� 
		if (flag == 1) {					// �ҵ��ùؼ��� 
			if (myNode->ptr[pos]) 
			{			// ��ǰ�ڵ�Ϊ�ڲ��ڵ� 
				ChangeKey(myNode, pos);		// ѡ���Һ�������С�����滻
				flag = DelKeyFromNode(myNode->K[pos], myNode->ptr[pos]);
				if (!flag) 
				{
					cout << "δ�ҵ��ýڵ�!\n";
				}
			}
			else
			 {							// ��ǰ�ڵ�ΪҶ�ӽڵ� 
				RemoveNode(myNode, pos);
			}
		}
		else 
		{								// δ�ҵ��ùؼ��� ��flag = 0 
			flag = DelKeyFromNode(key, myNode->ptr[pos]);
		}
		// �鿴�Ƿ���Ҫ����
		if (myNode->ptr[pos]) 
		{
			if (myNode->ptr[pos]->keynum < Min) 
			{
				AdjustNode(myNode, pos);
			}
		}
	}
	return flag;
}

void DeleteBTNode(KeyType key, BTNode*& myNode)
{
	if (!DelKeyFromNode(key, myNode))
	{
		cout << "δ�ҵ��ùؼ���!\n";
		return;
	}
	else {
		if (myNode->keynum == 0) 
		{			
            // ����Ҫ��һ�� 
			BTNode* temp = myNode;
			myNode = myNode->ptr[0];
			delete temp;
		}
	}
	return;
}

// ����B-��,ǰ����� 
void Traverse(BTree T)
{
    
	if (!T) return;
	if (T->ptr[0]) Traverse(T->ptr[0]);
	for (int i = 1; i <= T->keynum; i++) 
	{
		cout << T->K[i] << " ";
		Traverse(T->ptr[i]);
	}
	return;
}

// ��α��� 
void Traverse2(BTree T)
{
    
	if (!T) return;

	for (int i = 1; i <= T->keynum; i++)
	 {
		cout << T->K[i] << " ";
	}
	cout << endl;
	for (int i = 0; i <= T->keynum; i++)
	 {
		Traverse2(T->ptr[i]);
	}
}

// //���ӻ�չʾB-��
// void show(BTree T)
// {
//     if (!T) return;
//     ofstream file("show.dot",ios::binary);
//     file<<"graph{"<<endl;

//     deque<BTree> que;
//     que.push_back(T);
//     BTNode*p=NULL;
//     while(!que.empty())
//     {
//         p=que.front();
//         for(int i=0;i<=p->keynum;i++)
//         {
//             for(int j=1;j<=p->ptr[i]->keynum;j++)
//             {
//                 file<<p->ptr[i]->K[j];
//                 if(j!=p->ptr[i]->keynum) file<<";";
//                 que.push_back(p->ptr[i]);
//             }
//             file<<"--";
//             for (int j = 1; j <= p->keynum; j++)
// 	        {
// 		        file << p->K[j];
//                 if(j!=p->keynum) file<<";";
// 	        }
//         }
//         que.pop_back();
//     }
    
//     file<<"}";
//     file.close();
// }


#endif