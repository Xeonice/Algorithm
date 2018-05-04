//
// Created by 唐和辉 on 2018/5/4.
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
int E,N,flag;
int visit[200]={0};
struct crocodile
{
    int x;
    int y;
}croco[200];
int reachFromCenter(crocodile p){//中间岛屿需要额外判断
    return (15+E)*(15+E)>=p.x*p.x+p.y*p.y;//岛屿长+跳跃最长长度是否大于坐标长
}
int success(crocodile a){//判断当前点能否跳到岸上
    return a.x>=50-E||a.y>=50-E||a.x-E<=-50||a.y-E<=-50;
}
int move(crocodile a,crocodile b){//鳄鱼头上跳
    return E*E>=(a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
void DFS(int n){//深度优先搜索
    if(success(croco[n])){
        flag=1;
    }
    else{
        for(int i=0;i<N;i++){
            if(!visit[i]&&move(croco[n],croco[i])){//如果点未被遍历过，且能跳过去
                visit[i]=1;//标记为已访问
                DFS(i);//调用当前变量 i 继续进行 DFS 搜索（判断点+DFS）
            }
        }
    }
}
int main(){
    cin>>N>>E;
    if(E>=35){
        flag=1;
    }
    else{
        for(int i=0;i<N;i++){
            cin>>croco[i].x>>croco[i].y;
        }
        for(int i=0;i<N;i++){
            if(!visit[i]&&reachFromCenter(croco[i])){//跳出小岛到鳄鱼身上
                visit[i]=1;
                DFS(i);
            }
        }
    }
    if(flag) printf("Yes\n");
    else printf("No\n");
    return 0;
}