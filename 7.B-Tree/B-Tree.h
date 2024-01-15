#ifndef _B_TREE_H_
#define _B_TREE_H_

#include <iostream>
#include <fstream>
#include <deque>
#define KeyType int
using namespace std;
const int m = 4;
const int Min = (m - 1) / 2;		// 最少键数 

typedef struct BTNode
{
	int keynum;				// 节点中关键字的个数，即节点的大小
	KeyType K[m + 1]; 		// 关键字向量， 0号单元未用
	BTNode* ptr[m + 1];		// 子树指针向量
}BTNode, * BTree;

//	用来作为查找操作的返回值 
typedef struct Result 
{		
	BTNode* pre;			// 当前节点的双亲节点
	BTNode* now;			// 当前节点
	int seq;				// 表示关键字的序号
	int tag;				// 查找操作中，表示找到与否 
}Result;

// 在当前层寻找key
int Search(BTNode* ptr, KeyType key)
{
    //若找到则返回关键字序号， 否则返回进入下一层节点序号 
	int i = 0;
	if (ptr->K[1] > key) return i;	//	返回0号位置，作为下一层节点的进入位置 
	for (i = 1; i < ptr->keynum; i++) 
	{
		if (ptr->K[i] == key) break;
		else if (ptr->K[i] < key && ptr->K[i + 1] > key) break;
	}
	return i;
}

// 在B-树中查找关键词为key的节点
Result SearchBTree(BTree root, KeyType key)
{
    //若找到则返回当前节点，关键字序号，双亲节点，
    // 未找到则返回节点需要插入的位置（key的关键字为应插入指针pt所指向节点中的第i个和第i+1个节点之间）
    //以及双亲节点, 返回双亲节点，弥补了BTNode中不用parent的缺陷，同时也不用额外维护parent指针 

	BTNode* p = root;					// 用来遍历树的节点 
	BTNode* pre = NULL;					// 记录当前节点的双亲节点 
	int found = 0;
	int i = 0;							// 关键字序号 
	while (p && !found) 
	{
		i = Search(p, key);				// 在当前层寻找key
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

// 在该层进行插入操作 
void Insert(BTNode* p, int k, BTNode* ap, KeyType x)
{// 在该层进行插入操作 
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


// 分裂操作 
void Split(BTNode* p, BTNode*& ap, int s)
{
	int i = 0;
	int j = 1;
	//	if (ap)	delete ap;
	ap = new BTNode;
	for (i = s + 1; i <= m; i++)
	 {				// 将s之后的关键字分裂到新的节点中 
		ap->K[j++] = p->K[i];
	}
	j = 0;
	for (i = s; i <= m; i++) 
	{					// 将s之后的孩子指针分裂到新的节点中 
		ap->ptr[j++] = p->ptr[i];
	}

	p->keynum -= (m - s + 1);					// 更新关键字数量 
	ap->keynum = m - s;
}


// 创建新的根节点 
void NewRoot(BTree& root, BTNode* ap, int x)
{
	BTNode* T = new BTNode;			
	T->keynum = 1;
	T->K[1] = x;
	T->ptr[0] = root;
	T->ptr[1] = ap;

	root = T;
}

// 在B-树中插入节点，
int InsertBTNode(BTree& root, KeyType key)
{
    //首先要进行查找该关键字操作，若关键字已存在，直接返回，否则进行插入操作，
    //	并且判断是否需要进行分裂操作
	if (!root) 
    {
		root = new BTNode;
		root->keynum = 1;
		root->K[1] = key;
		root->ptr[0] = root->ptr[1] = NULL;
		return 1;
	}
	BTNode* p = root;					// 用来遍历树的节点 
	BTNode* ap = NULL;					// 要插入节点对应的ptr指针 
	int seq = 0;
	int finished = 0;
	KeyType x = key;						// 待插入的关键字 
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
			int s = (m + 1) / 2;					// 分裂的位置
			x = p->K[s];
			r = SearchBTree(root, x);				// 找当前节点的父节点
			Split(p, ap, s);						// 分裂
			if (p == root)	break;					// 已经是根节点了，没有父节点
			else p = r.pre;							// 返回父节点
			seq = Search(p, x);						// 在父节点中应该插入的位置
		}
	}
	if (!finished) NewRoot(root, ap, x);
	return 1;
}

// 用中序后置关键字替换当前节点关键字
void ChangeKey(BTNode* myNode, int pos)
{// 选择右孩子中最小的来替换 
	BTNode* temp = myNode->ptr[pos];
	while (temp->ptr[0]) {
		temp = temp->ptr[0];
	}
	myNode->K[pos] = temp->K[1];
}

// 在当前节点删除pos所在关键字与指针 
void RemoveNode(BTNode* myNode, int pos)
{// 在当前节点删除pos所在关键字与指针 
	int j = pos;
	while (j < myNode->keynum)
	 {
		myNode->K[j] = myNode->K[j + 1];
		myNode->ptr[j] = myNode->ptr[j + 1];
		j++;
	}
	myNode->keynum--;
}

// 将左孩子最右端键移至当前节点，并把当前节点中对应键移至右孩子第一个键中
void RightChange(BTNode* myNode, int pos)
{
	// 将当前节点中键移入有右孩子节点中 
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
    // 在当前节点中，将已经移至右孩子的键原来的位置换为左孩子中最右端键 
	BTNode* w = myNode->ptr[pos - 1];
	myNode->K[pos] = w->K[w->keynum];
	x->ptr[0] = w->ptr[w->keynum];
    //	删除左孩子中最右端键 
	w->keynum--;
}

// 将右孩子第一个键移至当前节点，并把当前节点中对应键移至左孩子最右端键
void LeftChange(BTNode* myNode, int pos)
{
	BTNode* w = myNode->ptr[pos - 1];
	BTNode* x = myNode->ptr[pos];
	// 将当前节点中键移入有左孩子节点中 
	w->keynum++;
	w->K[w->keynum] = myNode->K[pos];
	//	w->ptr[w->keynum] = myNode->ptr[]	
	w->ptr[w->keynum] = x->ptr[0];
	// 在当前节点中，将已经移至左孩子的键原来的位置换为右孩子中第一个键 
	myNode->K[pos] = x->K[1];
	//	myNode->ptr[pos] = x->ptr[1];
	//	删除右孩子中第一个键 
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

// 将左孩子右孩子通过当前节点的键进行合并
void Merge(BTNode* myNode, int pos)
{
	BTNode* w = myNode->ptr[pos - 1];
	BTNode* x = myNode->ptr[pos];
	// 将当前节点的键合并入左孩子 
	w->keynum++;
	w->K[w->keynum] = myNode->K[pos];
	w->ptr[w->keynum] = x->ptr[0];
	// 将右孩子也并入左孩子 
	int j = 1;
	while (j <= x->keynum) 
	{
		w->keynum++;
		w->K[w->keynum] = x->K[j];
		w->ptr[w->keynum] = x->ptr[j];
		j++;
	}
	// 当前节点删除已并入左孩子的键
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

// 调整节点
void AdjustNode(BTNode* myNode, int pos)
{// myNode->ptr[pos]是不富裕的 
	if (!pos) {									// 0号指针且本身不富裕,
		if (myNode->ptr[1]->keynum > Min) 
		{		// 右兄弟富裕 
			LeftChange(myNode, 1); 				// 右兄弟通过双亲节点给左兄弟一个键 
		}
		else {									// 右兄弟也穷，合并吧 
			Merge(myNode, 1);
		}
	}
	else if (pos != myNode->keynum) 
	{
		if (myNode->ptr[pos + 1]->keynum > Min)
		 {			// 右兄弟富裕 
			LeftChange(myNode, pos);
		}
		else if (myNode->ptr[pos - 1]->keynum > Min)
		 {		// 左兄弟富裕 
			RightChange(myNode, pos);
		}
		else 
		{												// 都不富裕，合并 
			Merge(myNode, pos);
		}
	}
	else {													// 本身不富裕， 最右端指针 
		if (myNode->ptr[myNode->keynum]->keynum > Min) {
			RightChange(myNode, myNode->keynum);
		}
		else {
			Merge(myNode, myNode->keynum);
		}
	}
}

// 删除关键字为key的节点 
int DelKeyFromNode(KeyType key, BTNode* myNode)
{
	int pos, flag = 0;
	if (myNode) 
	{
		// 在当前节点中查找关键字key 
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
		// 查找完毕，根据查找结果判断之后操作 
		if (flag == 1) {					// 找到该关键字 
			if (myNode->ptr[pos]) 
			{			// 当前节点为内部节点 
				ChangeKey(myNode, pos);		// 选择右孩子中最小的来替换
				flag = DelKeyFromNode(myNode->K[pos], myNode->ptr[pos]);
				if (!flag) 
				{
					cout << "未找到该节点!\n";
				}
			}
			else
			 {							// 当前节点为叶子节点 
				RemoveNode(myNode, pos);
			}
		}
		else 
		{								// 未找到该关键字 即flag = 0 
			flag = DelKeyFromNode(key, myNode->ptr[pos]);
		}
		// 查看是否需要调整
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
		cout << "未找到该关键字!\n";
		return;
	}
	else {
		if (myNode->keynum == 0) 
		{			
            // 树需要降一层 
			BTNode* temp = myNode;
			myNode = myNode->ptr[0];
			delete temp;
		}
	}
	return;
}

// 遍历B-树,前序遍历 
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

// 层次遍历 
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

// //可视化展示B-树
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