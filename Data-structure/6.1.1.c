#include <stdlib.h>
#include <stdio.h>

//
// Created by 唐和辉 on 2018/5/4.
//
//邻接矩阵
typedef int WeightType;
typedef int DataType;
typedef struct GNode *PtrToGNode;
struct GNode {
    int Nv; //顶点数
    int Ne; //边数
    WeightType G[10][10];
    DataType Data[10]; //存储点的数据
};
typedef PtrToGNode MGraph; //以邻接矩阵存储的图类型
typedef int Vertex; //用顶点下标表示顶点，为整型
MGraph CreateGraph(int VertexNum)
{
    Vertex V, W;
    MGraph Graph;
    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph -> Nv = VertexNum;
    Graph -> Ne = 0;
    /* 这里默认顶点编号从 0 开始，到 （Graph->Nv -1）*/
    for (V = 0; V  < Graph->Nv; V++){
        for (W = 0; W < Graph->Nv; W++) {
            Graph -> G[V][W] = 0; //或 INFINITY
        }
    }
    return Graph;
}
//向 MGraph 插入边
typedef struct ENode *PtrToENode;
struct ENode {
    Vertex V1, V2; //有向边<V1, V2>
    WeightType Weight; //权重
};
typedef PtrToENode Edge;
void InsertEdge (MGraph Graph, Edge E){
    //插入边 <V1, V2>
    Graph -> G[E->V1][E->V2] = E->Weight;
    //若是无向图，还要插入边 <V2, V1>
    Graph -> G[E->V2][E->V1] = E->Weight;
}
MGraph BuildGraph(){
    MGraph Graph;
    Edge E;
    int Nv;
    scanf("%d", &Nv);
    Graph = CreateGraph(Nv);
    scanf("%d", &(Graph->Ne));
    if (Graph -> Ne != 0){//图存在边
        E = (Edge)malloc(sizeof(struct ENode));
        for (int i = 0; i < Graph->Ne; ++i) {
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
            InsertEdge( Graph, E );
        }
    }
//    如果顶点有数据的话，读入数据
//    for(V = 0; V < Graph->Nv; V++){
//        scanf("%c", &(Graph->Data[V]));
//    }
    return Graph;
}
int main(){
    BuildGraph();

    return 0;
}