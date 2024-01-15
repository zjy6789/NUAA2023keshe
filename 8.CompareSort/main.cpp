#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>
#include <iomanip>
#include "Sort.h"
using namespace std;

const int num_samples = 10;
const int sample_size = 50000;

struct arrey
{
    int a[sample_size];
};
vector<arrey> arr(10);
void randomdata()
{
    
    // ������������
    for (int i = 0; i < sample_size; ++i) 
    {
        arr[0].a[i] = i;
    }

    // ������������
    for (int i =0 ; i< sample_size; ++i) 
    {
        arr[1].a[sample_size-1-i]=i;
    }

    // �����������
    random_device rd;
    mt19937 gen(rd());

    for (int i = 2; i < num_samples; ++i) 
    {
        iota(arr[i].a, arr[i].a + sample_size, 0);
        shuffle(arr[i].a, arr[i].a + sample_size, gen);
    }
}

void savedata()//�����ɵ����ݱ������ļ���
{
    ofstream file("data.txt");
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<sample_size;j++)
        {
            file<<arr[i].a[j]<<" ";
        }
        file<<endl<<endl;
    }
    file.close();
}

void getdata()//���ļ��ж�ȡ����
{
    ifstream file("data.txt");
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<sample_size;j++)
        {
            file>>arr[i].a[j];
        }
    }
}

void insertionSort_time()//����ֱ�Ӳ�����������ʱ��
{
    getdata();
    cout<<setw(20)<<left<<"ֱ�Ӳ�������";
    for(auto i:arr)
    {
        // ��¼��ʼʱ���
        auto start_time = chrono::high_resolution_clock::now();
        insertionSort(i.a,sample_size);
        // ��¼����ʱ���
        auto end_time = chrono::high_resolution_clock::now();
        // ����ʱ�����
        auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
        cout<<setw(10)<<left<<duration.count();
    }
    cout<<endl;
}

void shellSort_time()//����ϣ����������ʱ��
{
    getdata();
    cout<<setw(20)<<left<<"ϣ������";
    for(auto i:arr)
    {
        // ��¼��ʼʱ���
        auto start_time = chrono::high_resolution_clock::now();
        shellSort(i.a,sample_size);
        // ��¼����ʱ���
        auto end_time = chrono::high_resolution_clock::now();
        // ����ʱ�����
        auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
        cout<<setw(10)<<left<<duration.count();
    }
    cout<<endl;
}

void bubbleSort_time()//����ð������ʱ��
{
    getdata();
    cout<<setw(20)<<left<<"ð������";
    for(auto i:arr)
    {
        // ��¼��ʼʱ���
        auto start_time = chrono::high_resolution_clock::now();
        bubbleSort(i.a,sample_size);
        // ��¼����ʱ���
        auto end_time = chrono::high_resolution_clock::now();
        // ����ʱ�����
        auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
        cout<<setw(10)<<left<<duration.count();
    }
    cout<<endl;
}

void quickSort_time()//�����������ʱ��
{
    getdata();
    // const int size = 10;
    // int arr[size] = {170, 45, 75, 90, 802, 24, 2, 66, 805, 1};
    cout<<setw(20)<<left<<"��������";
    //quickSort(arr,0,size-1);
    for(auto i:arr)
    {
        // ��¼��ʼʱ���
        auto start_time = chrono::high_resolution_clock::now();
        iterativeQuickSort(i.a,0,sample_size-1);
        // ��¼����ʱ���
        auto end_time = chrono::high_resolution_clock::now();
        // ����ʱ�����
        auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
        cout<<setw(10)<<left<<duration.count();
    }
    cout<<endl;
}

void selectionSort_time()//ѡ������ʱ�����
{
    getdata();
    cout<<setw(20)<<left<<"ѡ������";
    for(auto i:arr)
    {
        // ��¼��ʼʱ���
        auto start_time = chrono::high_resolution_clock::now();
        selectionSort(i.a,sample_size);
        // ��¼����ʱ���
        auto end_time = chrono::high_resolution_clock::now();
        // ����ʱ�����
        auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
        cout<<setw(10)<<left<<duration.count();
    }
    cout<<endl;
}

void heapSort_time()//������ʱ�����
{
    getdata();
    cout<<setw(20)<<left<<"������";
    for(auto i:arr)
    {
        // ��¼��ʼʱ���
        auto start_time = chrono::high_resolution_clock::now();
        heapSort(i.a,sample_size);
        // ��¼����ʱ���
        auto end_time = chrono::high_resolution_clock::now();
        // ����ʱ�����
        auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
        cout<<setw(10)<<left<<duration.count();
    }
    cout<<endl;
}

void mergeSort_time()//�鲢����ʱ��
{
    getdata();
    cout<<setw(20)<<left<<"�鲢����";
    for(auto i:arr)
    {
        // ��¼��ʼʱ���
        auto start_time = chrono::high_resolution_clock::now();
        mergeSort(i.a,0,sample_size-1);
        // ��¼����ʱ���
        auto end_time = chrono::high_resolution_clock::now();
        // ����ʱ�����
        auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
        cout<<setw(10)<<left<<duration.count();
    }
    cout<<endl;
}

void radixSort_time()//��������ʱ�����
{
    getdata();
    cout<<setw(20)<<left<<"��������";
    for(auto i:arr)
    {
        // ��¼��ʼʱ���
        auto start_time = chrono::high_resolution_clock::now();
        radixSort(i.a,sample_size);
        // ��¼����ʱ���
        auto end_time = chrono::high_resolution_clock::now();
        // ����ʱ�����
        auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
        cout<<setw(10)<<left<<duration.count();
    }
    cout<<endl;
}


int main() 
{
    //ѡ���Ƿ����������������µ�����
    cout<<"�Ƿ����������ݣ�(Y/N):";
    char ch;
    cin>>ch;
    if(toupper(ch)=='Y')
    {
        randomdata();
        savedata();
    }
    system("cls");
    cout<<setw(20)<<left<<"��������(ʱ��:us)";
    cout<<setw(10)<<left<<"���ݼ�1";
    cout<<setw(10)<<left<<"���ݼ�2";
    cout<<setw(10)<<left<<"���ݼ�3";
    cout<<setw(10)<<left<<"���ݼ�4";
    cout<<setw(10)<<left<<"���ݼ�5";
    cout<<setw(10)<<left<<"���ݼ�6";
    cout<<setw(10)<<left<<"���ݼ�7";
    cout<<setw(10)<<left<<"���ݼ�8";
    cout<<setw(10)<<left<<"���ݼ�9";
    cout<<setw(10)<<left<<"���ݼ�10"<<endl;

    //���ø�����������ʱ����㺯����ʼ���򲢼���ʱ��
    insertionSort_time();
    shellSort_time();
    bubbleSort_time();
    quickSort_time();
    selectionSort_time();
    heapSort_time();
    mergeSort_time();
    radixSort_time();

    system("pause");
    return 0;
}
