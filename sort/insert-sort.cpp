//
// Created by 唐和辉 on 2018/4/22.
//

#include <iostream>
using namespace std;
void InsertionSort (int a[], int size) {
    for (int i = 1; i < size; ++i) {
        //a[i] 是最左的无序元素，每次循环将 a[i] 放到合适位置
        for(int j = 0; j < i; ++j){
            if (a[j] > a[i]){
                //要把 a[i] 放到位置 j，原下标 j 到 i-1 的元素都往后移一个位子
                int tmp = a[i];
                for (int k = i; k > j; --k) {
                    a[k] = a[k-1];
                }
                a[j] = tmp;
                break;
            }
        }
    }
    for (int l = 0; l < sizeof(a)/sizeof(int); ++l) {
        cout << a[l];
    }
}
int main () {
    int a[10] = {5,2,3,1,4,8,7,9,6,10};
    InsertionSort(a, 10);
    return 0;
}