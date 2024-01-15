#include<iostream>
#include<cstdlib>
#include<fstream>
#include<ctime>
#include<vector>
#include<iomanip>
#include<algorithm>
#include<random>
using namespace std;

//�������������ÿ�����ݸ�����Ϊż��
void generateMatrix() 
{
    int matrix[10][20]={0};
    // ��ʼ�����������
    srand(static_cast<unsigned int>(time(nullptr)));

    //û����һ��������ʹ����Σ���֤Ϊż����
    int randomnumber;
    vector<int> number;
    for(int i=0;i<100;i++)
    {
        randomnumber=abs(rand())%10+1;
        number.push_back(randomnumber);
        number.push_back(randomnumber);
    }
    // ʹ�� C++11 ֮����������������ʼ�������������
    random_device rd;
    mt19937 g(rd());

    // ������� vector
    shuffle(number.begin(), number.end(), g);
    int *p=&matrix[0][0];
    for(int i=0;i<200;i++)
    {
        *p=number[i];
        p++;
    }
    //������д���ļ�
    ofstream file("data.txt");
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<20;j++)
        {
            file<<matrix[i][j]<<" ";
        }
        file<<endl;
    }
    file.close();

}



// �ж����������Ƿ���ͬһ��
bool sameRow(int x1, int x2) {
    return x1 == x2;
}

// �ж����������Ƿ���ͬһ��
bool sameCol(int y1, int y2) {
    return y1 == y2;
}

// �ж���������֮���Ƿ����ֱ��·��
bool hasStraightPath(int x1, int y1, int x2, int y2, int matrix[][22]) {
    // �ж��Ƿ���ͬһ����ֱ��·��
    if (sameRow(x1, x2)) {
        int minY = min(y1, y2);
        int maxY = max(y1, y2);
        for (int y = minY + 1; y < maxY; ++y) {
            if (matrix[x1][y] != 0) {
                return false;
            }
        }
        return true;
    }

    // �ж��Ƿ���ͬһ����ֱ��·��
    if (sameCol(y1, y2)) {
        int minX = min(x1, x2);
        int maxX = max(x1, x2);
        for (int x = minX + 1; x < maxX; ++x) {
            if (matrix[x][y1] != 0) {
                return false;
            }
        }
        return true;
    }

    return false;
}

// �ж���������֮���Ƿ����һ���յ�·��
bool hasOneTurnPath(int x1, int y1, int x2, int y2, int matrix[][22]) {
    int rows = 10;
    int cols = 20;

    // ˮƽ����x�ᣩ�ϵĹյ�
    for (int i = 1; i <= rows; ++i) 
    {
        if (i != x1  && matrix[i][y1] == 0&& hasStraightPath(x1, y1, i, y1, matrix)&&hasStraightPath(i,y1,x2,y2,matrix) )
        {
            return true;
        }
    }

    // ��ֱ����y�ᣩ�ϵĹյ�

    for (int j = 1; j <= cols; ++j) 
    {
        if (j != y1  && matrix[x1][j] == 0  &&hasStraightPath(x1, y1, x1, j, matrix)&&hasStraightPath(x1,j,x2,y2,matrix))
        {
            return true;
        }
    }

    return false;
}

// �ж���������֮���Ƿ���������յ�·��
bool hasTwoTurnsPath(int x1, int y1, int x2, int y2, int matrix[][22]) {
    int rows = 10;
    int cols = 20;

    // ��ͬһ�����ҵ�һ���յ�
    for (int i = 0; i <= rows+1; ++i) 
    {
        if (i != x1  && matrix[i][y1] == 0 &&
            hasStraightPath(x1, y1, i, y1, matrix) && hasOneTurnPath(i, y1, x2, y2, matrix)) 
        {
            return true;
        }
    }

    // ��ͬһ�����ҵ�һ���յ�
    for (int j = 0; j <= cols+1; ++j) 
    {
        if (j != y1  && matrix[x1][j] == 0 && 
            hasStraightPath(x1, y1, x1, j, matrix) && hasOneTurnPath(x1, j, x2, y2, matrix)) {
            return true;
        }
    }

    return false;
}

// �ж���������֮���Ƿ��ܹ�����
bool canEliminate(pair<int, int> dot1, pair<int, int> dot2, int matrix[][22]) {
    int x1 = dot1.first, y1 = dot1.second;
    int x2 = dot2.first, y2 = dot2.second;

    if (matrix[x1][y1] != matrix[x2][y2]) {
        return false;  // ��ͬ���ֵĿ��޷�����
    }

    // �ж��Ƿ���ͬһ�л�ͬһ�У�����ͨ��һ���յ�����
    return hasStraightPath(x1,y1,x2,y2,matrix)|| hasOneTurnPath(x1, y1, x2, y2, matrix) || hasTwoTurnsPath(x1, y1, x2, y2, matrix);
}

int main()
{
    generateMatrix();
    int matrix[12][22]={0};
    //������
    ifstream file("data.txt");
    for(int i=1;i<=10;i++)
    {
        for(int j=1;j<=20;j++)
        {
            file>>matrix[i][j];
        }
    }
    file.close();
    //��ӡ��ȡ��ͼ
    for(int i=1;i<=10;i++)
    {
        for(int j=1;j<=20;j++)
        {
            cout<<setw(3)<<left<<matrix[i][j];
        }
        cout<<endl;
    }
    pair<int,int> dot1,dot2;
    //��Ϸ��ѭ��
    while(1)
    {
        cout<<endl<<"�����������x,y���꣺";
        cin>>dot1.first>>dot1.second>>dot2.first>>dot2.second;
        if(canEliminate(dot1,dot2,matrix)==true)
        {
            matrix[dot1.first][dot1.second]=0;
            matrix[dot2.first][dot2.second]=0;
        }
        //��ӡ���º��ͼ;
        system("cls");
        for(int i=1;i<=10;i++)
        {
            for(int j=1;j<=20;j++)
            {
                if(matrix[i][j]!=0)
                    cout<<setw(3)<<left<<matrix[i][j];
                else cout<<"   ";
            }
            cout<<endl;
        }
        //�����˳�ѭ������
        bool flag=true;
        for(int i=1;i<=10;i++)
        {
            for(int j=1;j<=20;j++)
            {
                //���������δ�����ķ���
                if(matrix[i][j]!=0)
                    flag=false;
            }
        }
        //����ȫ����������Ϸ����
        if(flag) break;
    }
    system("pause");
    return 0;
}