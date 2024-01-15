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
    
    // 生成正序样本
    for (int i = 0; i < sample_size; ++i) 
    {
        arr[0].a[i] = i;
    }

    // 生成逆序样本
    for (int i =0 ; i< sample_size; ++i) 
    {
        arr[1].a[sample_size-1-i]=i;
    }

    // 生成随机样本
    random_device rd;
    mt19937 gen(rd());

    for (int i = 2; i < num_samples; ++i) 
    {
        iota(arr[i].a, arr[i].a + sample_size, 0);
        shuffle(arr[i].a, arr[i].a + sample_size, gen);
    }
}

void savedata()//将生成的数据保存至文件中
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

void getdata()//从文件中读取数据
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

void insertionSort_time()//计算直接插入排序所花时间
{
    getdata();
    cout<<setw(20)<<left<<"直接插入排序";
    for(auto i:arr)
    {
        // 记录开始时间点
        auto start_time = chrono::high_resolution_clock::now();
        insertionSort(i.a,sample_size);
        // 记录结束时间点
        auto end_time = chrono::high_resolution_clock::now();
        // 计算时间差异
        auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
        cout<<setw(10)<<left<<duration.count();
    }
    cout<<endl;
}

void shellSort_time()//计算希尔排序所花时间
{
    getdata();
    cout<<setw(20)<<left<<"希尔排序";
    for(auto i:arr)
    {
        // 记录开始时间点
        auto start_time = chrono::high_resolution_clock::now();
        shellSort(i.a,sample_size);
        // 记录结束时间点
        auto end_time = chrono::high_resolution_clock::now();
        // 计算时间差异
        auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
        cout<<setw(10)<<left<<duration.count();
    }
    cout<<endl;
}

void bubbleSort_time()//计算冒泡排序时间
{
    getdata();
    cout<<setw(20)<<left<<"冒泡排序";
    for(auto i:arr)
    {
        // 记录开始时间点
        auto start_time = chrono::high_resolution_clock::now();
        bubbleSort(i.a,sample_size);
        // 记录结束时间点
        auto end_time = chrono::high_resolution_clock::now();
        // 计算时间差异
        auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
        cout<<setw(10)<<left<<duration.count();
    }
    cout<<endl;
}

void quickSort_time()//计算快速排序时间
{
    getdata();
    // const int size = 10;
    // int arr[size] = {170, 45, 75, 90, 802, 24, 2, 66, 805, 1};
    cout<<setw(20)<<left<<"快速排序";
    //quickSort(arr,0,size-1);
    for(auto i:arr)
    {
        // 记录开始时间点
        auto start_time = chrono::high_resolution_clock::now();
        iterativeQuickSort(i.a,0,sample_size-1);
        // 记录结束时间点
        auto end_time = chrono::high_resolution_clock::now();
        // 计算时间差异
        auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
        cout<<setw(10)<<left<<duration.count();
    }
    cout<<endl;
}

void selectionSort_time()//选择排序时间计算
{
    getdata();
    cout<<setw(20)<<left<<"选择排序";
    for(auto i:arr)
    {
        // 记录开始时间点
        auto start_time = chrono::high_resolution_clock::now();
        selectionSort(i.a,sample_size);
        // 记录结束时间点
        auto end_time = chrono::high_resolution_clock::now();
        // 计算时间差异
        auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
        cout<<setw(10)<<left<<duration.count();
    }
    cout<<endl;
}

void heapSort_time()//堆排序时间计算
{
    getdata();
    cout<<setw(20)<<left<<"堆排序";
    for(auto i:arr)
    {
        // 记录开始时间点
        auto start_time = chrono::high_resolution_clock::now();
        heapSort(i.a,sample_size);
        // 记录结束时间点
        auto end_time = chrono::high_resolution_clock::now();
        // 计算时间差异
        auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
        cout<<setw(10)<<left<<duration.count();
    }
    cout<<endl;
}

void mergeSort_time()//归并排序时间
{
    getdata();
    cout<<setw(20)<<left<<"归并排序";
    for(auto i:arr)
    {
        // 记录开始时间点
        auto start_time = chrono::high_resolution_clock::now();
        mergeSort(i.a,0,sample_size-1);
        // 记录结束时间点
        auto end_time = chrono::high_resolution_clock::now();
        // 计算时间差异
        auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
        cout<<setw(10)<<left<<duration.count();
    }
    cout<<endl;
}

void radixSort_time()//基数排序时间计算
{
    getdata();
    cout<<setw(20)<<left<<"基数排序";
    for(auto i:arr)
    {
        // 记录开始时间点
        auto start_time = chrono::high_resolution_clock::now();
        radixSort(i.a,sample_size);
        // 记录结束时间点
        auto end_time = chrono::high_resolution_clock::now();
        // 计算时间差异
        auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
        cout<<setw(10)<<left<<duration.count();
    }
    cout<<endl;
}


int main() 
{
    //选择是否调用随机函数生成新的数据
    cout<<"是否生成新数据？(Y/N):";
    char ch;
    cin>>ch;
    if(toupper(ch)=='Y')
    {
        randomdata();
        savedata();
    }
    system("cls");
    cout<<setw(20)<<left<<"排序类型(时间:us)";
    cout<<setw(10)<<left<<"数据集1";
    cout<<setw(10)<<left<<"数据集2";
    cout<<setw(10)<<left<<"数据集3";
    cout<<setw(10)<<left<<"数据集4";
    cout<<setw(10)<<left<<"数据集5";
    cout<<setw(10)<<left<<"数据集6";
    cout<<setw(10)<<left<<"数据集7";
    cout<<setw(10)<<left<<"数据集8";
    cout<<setw(10)<<left<<"数据集9";
    cout<<setw(10)<<left<<"数据集10"<<endl;

    //调用各个排序函数的时间计算函数开始排序并计算时间
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
