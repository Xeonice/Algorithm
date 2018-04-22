//
// Created by 唐和辉 on 2018/4/22.
//
#include <iostream>
using namespace std;
struct Node{ int tag; int num; };
int main() {
    int N; cin>>N;
    struct Node stack[30];
    int flag = 0; int size = 0;
    for ( int i = 0; i < 2*N; i++) {
        string str; cin>>str;
        if(str[1] == 'u'){
            cin>>stack[size].num; stack[size].tag = 1; size++;
        }
        else{
            while(size > 0 && stack[size-1].tag == 2){
                if( flag){ cout<<" "; } flag = 1; cout<<stack[--size].num;
            }
            if ( size>0){
                stack[size-1].tag = 2;
            }
        }
    }
    while(size){
        if ( flag ){
            cout<<" ";
        }
        flag = 1;
        cout<<stack[--size].num;
    }
    return 0;
}
