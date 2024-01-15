#ifndef _SORT_H_
#define _SORT_H_

#include<iostream>
#include <stack>
using namespace std;

//直接插入排序
void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; ++i) {
        int key = arr[i];
        int j = i - 1;

        // 移动元素，找到插入位置
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }

        // 在找到的位置插入元素
        arr[j + 1] = key;
    }
}

//希尔排序
void shellSort(int arr[], int size) {
    // 使用希尔增量序列
    for (int gap = size / 2; gap > 0; gap /= 2) {
        // 对每个间隔进行插入排序
        for (int i = gap; i < size; ++i) {
            int temp = arr[i];
            int j = i;

            // 移动元素，找到插入位置
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }

            // 在找到的位置插入元素
            arr[j] = temp;
        }
    }
}

//冒泡排序
void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            // 如果前面的元素大于后面的元素，交换它们
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

//快速排序
// 分割数组并返回分割点的索引
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // 选择最后一个元素作为基准
    int i = low - 1;  // 初始化分割点

    for (int j = low; j <= high - 1; ++j) {
        // 如果当前元素小于等于基准，交换它们
        if (arr[j] <= pivot) {
            ++i;
            int t=arr[i];
            arr[i]=arr[j];
            arr[j]=t;
        }
    }

    // 将基准放到正确的位置
    int t=arr[i+1];
    arr[i+1]=arr[high];
    arr[high]=t;
    return i + 1;
}

// 递归调用快速排序
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // 获取分割点的索引
        int pi = partition(arr, low, high);

        // 对分割点的左右两部分进行递归排序
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


// 非递归快速排序
void iterativeQuickSort(int arr[], int low, int high) {
    std::stack<int> stack;

    // 初始化栈
    stack.push(low);
    stack.push(high);

    // 循环直到栈为空
    while (!stack.empty()) {
        // 弹出栈顶的高和低
        high = stack.top();
        stack.pop();
        low = stack.top();
        stack.pop();

        // 获取分割点的索引
        int pi = partition(arr, low, high);

        // 如果分割点的左边有元素，将左边的范围压入栈
        if (pi - 1 > low) {
            stack.push(low);
            stack.push(pi - 1);
        }

        // 如果分割点的右边有元素，将右边的范围压入栈
        if (pi + 1 < high) {
            stack.push(pi + 1);
            stack.push(high);
        }
    }
}

//选择排序
void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        // 假设当前位置是最小的
        int minIndex = i;

        // 在未排序部分中找到最小的元素的索引
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // 交换找到的最小元素和当前位置的元素
        std::swap(arr[i], arr[minIndex]);
    }
}

void heapify(int arr[], int size, int i) {
    int largest = i;  // 初始化根节点为最大值
    int left = 2 * i + 1;  // 左子节点索引
    int right = 2 * i + 2;  // 右子节点索引

    // 如果左子节点比根节点大，更新最大值索引
    if (left < size && arr[left] > arr[largest]) {
        largest = left;
    }

    // 如果右子节点比根节点大，更新最大值索引
    if (right < size && arr[right] > arr[largest]) {
        largest = right;
    }

    // 如果最大值不是根节点，交换它们并递归调整
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, size, largest);
    }
}

// 堆排序
void heapSort(int arr[], int size) {
    // 构建最大堆
    for (int i = size / 2 - 1; i >= 0; --i) {
        heapify(arr, size, i);
    }

    // 逐步提取最大元素
    for (int i = size - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);  // 将最大元素移动到数组末尾
        heapify(arr, i, 0);  // 重新调整堆
    }
}

//归并排序
void merge(int arr[], int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // 创建临时数组来存储两个子数组
    int *leftArr = new int[n1];
    int *rightArr = new int[n2];

    // 将数据复制到临时数组
    for (int i = 0; i < n1; ++i) {
        leftArr[i] = arr[left + i];
    }

    for (int j = 0; j < n2; ++j) {
        rightArr[j] = arr[middle + 1 + j];
    }

    // 合并两个子数组
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            ++i;
        } else {
            arr[k] = rightArr[j];
            ++j;
        }
        ++k;
    }

    // 将未使用的元素复制回数组
    while (i < n1) {
        arr[k] = leftArr[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        ++j;
        ++k;
    }

    // 释放动态分配的内存
    delete[] leftArr;
    delete[] rightArr;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        // 递归地对左右两部分进行排序
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        // 合并已排序的两部分
        merge(arr, left, middle, right);
    }
}

// 获取数组中最大的数字
int getMax(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// 对数组按照指定位数进行计数排序
void countingSort(int arr[], int size, int exp) {
    const int radix = 10;  // 基数为10，因为数字有10个可能的值（0-9）
    int output[size];
    int count[radix] = {0};

    // 统计每个数字出现的次数
    for (int i = 0; i < size; ++i) {
        count[(arr[i] / exp) % radix]++;
    }

    // 将count数组转换为累积次数
    for (int i = 1; i < radix; ++i) {
        count[i] += count[i - 1];
    }

    // 构建输出数组
    for (int i = size - 1; i >= 0; --i) {
        output[count[(arr[i] / exp) % radix] - 1] = arr[i];
        count[(arr[i] / exp) % radix]--;
    }

    // 将输出数组复制回原数组
    for (int i = 0; i < size; ++i) {
        arr[i] = output[i];
    }
}

// 基数排序
void radixSort(int arr[], int size) {
    int max = getMax(arr, size);

    // 对每一位进行计数排序
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSort(arr, size, exp);
    }
}

#endif