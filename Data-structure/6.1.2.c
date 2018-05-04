#include <stdlib.h>
#include <stdio.h>

//
// Created by 唐和辉 on 2018/5/4.
//
typedef int Vertex; //用顶点下标表示顶点，为整型
typedef int WeightType;
typedef int DataType;

typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {//邻接表元素
    Vertex AdjV; //邻接点下标
    WeightType Weight; //边权重
    PtrToAdjVNode Next;
};

typedef struct Vnode {//邻接表数组
    PtrToAdjVNode FirstEdge;
    DataType Data; //存储数据
} AdjList[10];

typedef struct GNode *PtrToGNode;

struct GNode {//
    int Nv; //顶点数
    int Ne; //边数
    AdjList G; // 邻接表
};
typedef PtrToGNode LGraph;

LGraph CreateGraph(int VertexNum)
{
    Vertex V;
    LGraph Graph;
    Graph = (LGraph)malloc(sizeof(struct GNode));
    Graph -> Nv = VertexNum;
    Graph -> Ne = 0;
    /* 这里默认顶点编号从 0 开始，到 （Graph->Nv -1）*/
    for (V = 0; V  < Graph->Nv; V++){
        Graph -> G[V].FirstEdge = NULL;
    }
    return Graph;
}
typedef struct ENode *PtrToENode;
struct ENode {
    Vertex V1, V2; //有向边<V1, V2>
    WeightType Weight; //权重
};
typedef PtrToENode Edge;
void InsertEdge (LGraph Graph, Edge E){
    PtrToAdjVNode NewNode;

    //插入边 <V1, V2>
    //为 V2 建立新的邻接点
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode -> AdjV = E -> V2;
    NewNode -> Weight = E -> Weight;
    //将 V2 插入 V1 的表头
    NewNode -> Next = Graph -> G[E->V1].FirstEdge;
    Graph -> G[E->V1].FirstEdge = NewNode;

    //若是无向图，还要插入边 <V2, V1>
    //为 V1 建立新的邻接点
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode -> AdjV = E -> V1;
    NewNode -> Weight = E -> Weight;
    //将 V1 插入 V2 的表头
    NewNode -> Next = Graph -> G[E->V2].FirstEdge;
    Graph -> G[E->V2].FirstEdge = NewNode;
}
LGraph BuildGraph(){
    LGraph Graph;
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