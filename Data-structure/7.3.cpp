//
// Created by 唐和辉 on 2018/5/7.
//

#include<iostream>
using namespace std;
const int maxn=505,infinity=10000;
int N,M,S,D,DL[maxn],DP[maxn],path[maxn]={0},GL[maxn][maxn]={0},GP[maxn][maxn]={0};
void Dijkstra(){
    int v,minl,minp,final[maxn]={0};
    for(int i=0;i<N;i++){
        DL[i] = GL[S][i];
        DP[i] = GP[S][i];
        if(DL[i]<infinity) path[i] = S;
    }
    final[S] = 1;
    for(int i=0;i<N;i++){
        minl = infinity;
        for(int j=0;j<N;j++){
            if(!final[j] && (DL[j]<minl || (DL[j]==minl && DP[j]<minp))){
                v = j;
                minl = DL[j];
                minp = DP[j];
            }
        }
        if(minl<infinity) final[v] = 1;
        else break;
        for(int i=0;i<N;i++){
            if(!final[i] && ((minl+GL[v][i])<DL[i] || (((minl+GL[v][i])==DL[i]) && (minp+GP[v][i])<DP[i]))){
                DL[i] = minl + GL[v][i];
                DP[i] = minp + GP[v][i];
                path[i] = v;
            }
        }
    }
    cout<<DL[D]<<' '<<DP[D]<<endl;
}
int main(){
    int a,b,l,p;
    cin>>N>>M>>S>>D;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(i!=j) GL[i][j]=GP[i][j] = infinity;
        }
    }
    for(int i=0;i<M;i++){
        cin>>a>>b>>l>>p;
        GL[a][b]=GL[b][a] = l;
        GP[a][b]=GP[b][a] = p;
    }
    Dijkstra();

    return 0;
}