//
// Created by 唐和辉 on 2018/4/22.
//
#include <iostream>
using namespace std;
void SelectionSort(int a[], int size){
    for (int i = 0; i < size-1; ++i) {//每次循环后将第 i 小的元素放好
        int tmpMin = i;
        // 用来记录从第 i 个到 第 size-1 个元素中，最小的那个元素的下标
        for (int j = 0; j < size; ++j) {
            if (a[j] < a[tmpMin])
                tmpMin = j;
        }
        //将第 i 小的元素放在第 i 个位子上，并将原来占着第 i 个位子的元素挪到后面
        int tmp = a[i];
        a[i] = a[tmpMin];
        a[tmpMin] = tmp;
    }
}
int main() {
    cout << "hello";
    return 0;
}

