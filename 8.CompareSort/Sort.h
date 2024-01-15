#ifndef _SORT_H_
#define _SORT_H_

#include<iostream>
#include <stack>
using namespace std;

//ֱ�Ӳ�������
void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; ++i) {
        int key = arr[i];
        int j = i - 1;

        // �ƶ�Ԫ�أ��ҵ�����λ��
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }

        // ���ҵ���λ�ò���Ԫ��
        arr[j + 1] = key;
    }
}

//ϣ������
void shellSort(int arr[], int size) {
    // ʹ��ϣ����������
    for (int gap = size / 2; gap > 0; gap /= 2) {
        // ��ÿ��������в�������
        for (int i = gap; i < size; ++i) {
            int temp = arr[i];
            int j = i;

            // �ƶ�Ԫ�أ��ҵ�����λ��
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }

            // ���ҵ���λ�ò���Ԫ��
            arr[j] = temp;
        }
    }
}

//ð������
void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            // ���ǰ���Ԫ�ش��ں����Ԫ�أ���������
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

//��������
// �ָ����鲢���طָ�������
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // ѡ�����һ��Ԫ����Ϊ��׼
    int i = low - 1;  // ��ʼ���ָ��

    for (int j = low; j <= high - 1; ++j) {
        // �����ǰԪ��С�ڵ��ڻ�׼����������
        if (arr[j] <= pivot) {
            ++i;
            int t=arr[i];
            arr[i]=arr[j];
            arr[j]=t;
        }
    }

    // ����׼�ŵ���ȷ��λ��
    int t=arr[i+1];
    arr[i+1]=arr[high];
    arr[high]=t;
    return i + 1;
}

// �ݹ���ÿ�������
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // ��ȡ�ָ�������
        int pi = partition(arr, low, high);

        // �Էָ������������ֽ��еݹ�����
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


// �ǵݹ��������
void iterativeQuickSort(int arr[], int low, int high) {
    std::stack<int> stack;

    // ��ʼ��ջ
    stack.push(low);
    stack.push(high);

    // ѭ��ֱ��ջΪ��
    while (!stack.empty()) {
        // ����ջ���ĸߺ͵�
        high = stack.top();
        stack.pop();
        low = stack.top();
        stack.pop();

        // ��ȡ�ָ�������
        int pi = partition(arr, low, high);

        // ����ָ��������Ԫ�أ�����ߵķ�Χѹ��ջ
        if (pi - 1 > low) {
            stack.push(low);
            stack.push(pi - 1);
        }

        // ����ָ����ұ���Ԫ�أ����ұߵķ�Χѹ��ջ
        if (pi + 1 < high) {
            stack.push(pi + 1);
            stack.push(high);
        }
    }
}

//ѡ������
void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        // ���赱ǰλ������С��
        int minIndex = i;

        // ��δ���򲿷����ҵ���С��Ԫ�ص�����
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // �����ҵ�����СԪ�غ͵�ǰλ�õ�Ԫ��
        std::swap(arr[i], arr[minIndex]);
    }
}

void heapify(int arr[], int size, int i) {
    int largest = i;  // ��ʼ�����ڵ�Ϊ���ֵ
    int left = 2 * i + 1;  // ���ӽڵ�����
    int right = 2 * i + 2;  // ���ӽڵ�����

    // ������ӽڵ�ȸ��ڵ�󣬸������ֵ����
    if (left < size && arr[left] > arr[largest]) {
        largest = left;
    }

    // ������ӽڵ�ȸ��ڵ�󣬸������ֵ����
    if (right < size && arr[right] > arr[largest]) {
        largest = right;
    }

    // ������ֵ���Ǹ��ڵ㣬�������ǲ��ݹ����
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, size, largest);
    }
}

// ������
void heapSort(int arr[], int size) {
    // ��������
    for (int i = size / 2 - 1; i >= 0; --i) {
        heapify(arr, size, i);
    }

    // ����ȡ���Ԫ��
    for (int i = size - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);  // �����Ԫ���ƶ�������ĩβ
        heapify(arr, i, 0);  // ���µ�����
    }
}

//�鲢����
void merge(int arr[], int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // ������ʱ�������洢����������
    int *leftArr = new int[n1];
    int *rightArr = new int[n2];

    // �����ݸ��Ƶ���ʱ����
    for (int i = 0; i < n1; ++i) {
        leftArr[i] = arr[left + i];
    }

    for (int j = 0; j < n2; ++j) {
        rightArr[j] = arr[middle + 1 + j];
    }

    // �ϲ�����������
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

    // ��δʹ�õ�Ԫ�ظ��ƻ�����
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

    // �ͷŶ�̬������ڴ�
    delete[] leftArr;
    delete[] rightArr;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        // �ݹ�ض����������ֽ�������
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        // �ϲ��������������
        merge(arr, left, middle, right);
    }
}

// ��ȡ��������������
int getMax(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// �����鰴��ָ��λ�����м�������
void countingSort(int arr[], int size, int exp) {
    const int radix = 10;  // ����Ϊ10����Ϊ������10�����ܵ�ֵ��0-9��
    int output[size];
    int count[radix] = {0};

    // ͳ��ÿ�����ֳ��ֵĴ���
    for (int i = 0; i < size; ++i) {
        count[(arr[i] / exp) % radix]++;
    }

    // ��count����ת��Ϊ�ۻ�����
    for (int i = 1; i < radix; ++i) {
        count[i] += count[i - 1];
    }

    // �����������
    for (int i = size - 1; i >= 0; --i) {
        output[count[(arr[i] / exp) % radix] - 1] = arr[i];
        count[(arr[i] / exp) % radix]--;
    }

    // ��������鸴�ƻ�ԭ����
    for (int i = 0; i < size; ++i) {
        arr[i] = output[i];
    }
}

// ��������
void radixSort(int arr[], int size) {
    int max = getMax(arr, size);

    // ��ÿһλ���м�������
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSort(arr, size, exp);
    }
}

#endif