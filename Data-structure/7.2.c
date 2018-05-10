/*
评测结果
时间  结果  得分  题目  编译器 用时（ms）  内存（MB）  用户
2017-07-04 18:58    答案正确    30  5-11    gcc 12  1
测试点结果
测试点 结果  得分/满分   用时（ms）  内存（MB）
测试点1    答案正确    15/15   1   1
测试点2    答案正确    3/3 2   1
测试点3    答案正确    2/2 2   1
测试点4    答案正确    3/3 1   1
测试点5    答案正确    6/6 2   1
测试点6    答案正确    1/1 12  1

解法，设一个空的起点，设一个空的终点
把第一跳能跳到的点和起点连起来
把最后能上岸的点和终点连起来
然后用dijkstra算法求起点到终点的最短路径
*/
#include<stdio.h>
#include<math.h>
#include <stdlib.h>

#define MAX_CROCODILE 102
//set CROCODILE #101 to start Vertex,N+1 to finish Vertex
#define _START_IDX 101
#define _FINISH_IDX N+1
#define CENTRAL_ISLAND_R 7.5//中心岛屿半径
#define BORDER 50
#define TRUE 1
#define FALSE 0
#define INF 10000
struct tCrocoVertex
{
    int x;
    int y;
    int start;
    int finish;
} gNodeTab[MAX_CROCODILE]; //主要是放坐标的，在HardVersion里面finish和start反而没什么用了

float gMatrix[MAX_CROCODILE][MAX_CROCODILE]; //放邻接矩阵
float gPathDist[MAX_CROCODILE];//放路径长度
float gFirstJump[MAX_CROCODILE];//放第一跳的长度，根据题意去重用
int gPathFrom[MAX_CROCODILE];//放最短路径的前一个节点
int gCollected[MAX_CROCODILE];//Dijkstra里面需要用的收纳表，看该点有没有被纳入集合内

int Min(int a,int b)
{
    return a<b?a:b;
}

void InitTables()
{
    int i;
    for(i=0;i<MAX_CROCODILE;i++)
    {
        gPathDist[i]=INF;
        gFirstJump[i]=INF;
        gCollected[i]=0;
    }
}
void InitMatrix()
{
    int i,j;
    for(i=0;i<= _START_IDX;i++)
        for(j=0;j<=_START_IDX;j++)
            gMatrix[i][j]=INF;
}

void FindStartAndFinishNode(int N,int jumpDistance)
{
    int i,minFinishDist;
    //minFinishDist放一个点到岸上的最短距离
    float dist;
    float startDist=jumpDistance+CENTRAL_ISLAND_R;//中心岛屿半径+跳跃距离=初始跳跃长度
    for(i=0;i<N;i++)
    {
        dist=sqrt((gNodeTab[i].x)*(gNodeTab[i].x)+(gNodeTab[i].y)*(gNodeTab[i].y));

        if(dist<=startDist) //第一步跳出去够得着的点
        {
            gNodeTab[i].start=TRUE;
            dist=dist-CENTRAL_ISLAND_R;
            gFirstJump[i]=dist;
            dist=1;//切换算距离还是算步数，算距离的话把这行注释掉
            gMatrix[i][_START_IDX]=dist;//特殊计数（起点）
            gMatrix[_START_IDX][i]=dist;
        }

        minFinishDist=abs(gNodeTab[i].x-BORDER);
        minFinishDist=Min(abs(gNodeTab[i].x+BORDER),minFinishDist);
        minFinishDist=Min(abs(gNodeTab[i].y-BORDER),minFinishDist);
        minFinishDist=Min(abs(gNodeTab[i].x+BORDER),minFinishDist);
        if(minFinishDist<=jumpDistance) //能否跳到岸上
        {
            gNodeTab[i].finish=TRUE;
            minFinishDist=1;//切换算距离还是算步数，算距离的话把这行注释掉
            gMatrix[i][_FINISH_IDX-1]=minFinishDist;//特殊计数（终点）
            gMatrix[_FINISH_IDX-1][i]=minFinishDist;
        }

    }
}

void BuildMatrix(int N,int jumpDistance)
{
    int i,j;
    float dist;
    for(i=0;i<N;i++)
        for(j=0;j<i;j++)
        {
            dist=sqrt(  (gNodeTab[i].x-gNodeTab[j].x)*
                        (gNodeTab[i].x-gNodeTab[j].x)+
                        (gNodeTab[i].y-gNodeTab[j].y)*
                        (gNodeTab[i].y-gNodeTab[j].y));
            if(dist<=jumpDistance)//跳跃距离内的计入矩阵
            {
                dist=1;//切换算距离还是算步数，算距离的话把这行注释掉
                gMatrix[i][j]=dist;//gNodeTab 中第 i 个节点到第 j 个节点的距离（在跳跃距离内）
                gMatrix[j][i]=dist;//无向图
            }
        }
}

int FindNextIDX(int N)//找出没有被收进集合的点中，dist最小的
{
    int i,minIDX,minPath;
    minIDX=-1;
    minPath=INF;
    for(i=0;i<_FINISH_IDX;i++)
    {
        if(gCollected[i]!=TRUE)
        {
            if(gPathDist[i]<minPath)
            {
                minPath=gPathDist[i];
                minIDX=i;
            }
        }
    }
    return minIDX;
}

void Dijkstra(int N)//传 N 服务 FINISH_IDX
{
    int i,nextIDX;
    gPathDist[_START_IDX]=0;//从第一个点开始
    nextIDX=_START_IDX;
    while(nextIDX!=-1)//节点集合不为空
    {
        gCollected[nextIDX]=1;
        for(i=0;i<_FINISH_IDX;i++)
        {
            //
            if(gPathDist[i]>gPathDist[nextIDX]+gMatrix[nextIDX][i]
               //nextIDX 距离 + nextIDX 到下一节点距离 < 原先记录的下一节点距离
               ||
               ((int)gPathDist[i]==(int)(gPathDist[nextIDX]+gMatrix[nextIDX][i])
                //距离相同时
                &&
                gFirstJump[i]>gFirstJump[nextIDX]
                //选用第一跳最短的
                &&
                (int)gPathDist[i]!= INF)
                //且跳跃不为空的
                )
            {
                gPathDist[i]=gPathDist[nextIDX]+gMatrix[nextIDX][i];//赋值
                gPathFrom[i]=nextIDX;//记录这一跳
                if(nextIDX!=_START_IDX)//非第一跳
                    gFirstJump[i]=gFirstJump[nextIDX];
            }
        }
        nextIDX=FindNextIDX(N);
    }
    //构建出所有的可能性
}

void DBG_ShowStatus(int N) //调试用函数
{
    int i,j;
    for(i=0;i<_FINISH_IDX;i++)
    {
        printf("ID:%d,x:%d,y:%d,start:%d,finish:%d\n",i,gNodeTab[i].x,gNodeTab[i].y,gNodeTab[i].start,gNodeTab[i].finish);
    }
    for(i=0;i<_FINISH_IDX;i++)
    {
        for(j=0;j<_FINISH_IDX;j++)
            printf("%4.1f ",gMatrix[i][j]);
        printf("\n");
    }
    for(i=0;i<_FINISH_IDX;i++)

        printf("%d,%4.1f ,FJ:%.2f,%d\n",i,gPathDist[i],gFirstJump[i],gPathFrom[i]);
}

void PrintPath(int i) //因为路径要正序输出，懒得用栈了，直接递归
{
    if (i==_START_IDX)
        return;
    PrintPath(gPathFrom[i]);
    printf("%d %d\n",gNodeTab[i].x,gNodeTab[i].y);
}

void Output(int N,int D)
{
    int i;
    if(D>=50-CENTRAL_ISLAND_R)
    {
        printf("1");
        return;
        //备注，最后一个测试点卡这里了，如果跳跃距离足够远能直接跳上岸，那么直接打个1就行了。
    }
    if((int)gPathDist[_FINISH_IDX-1]==INF)
    {
        printf("0");
        return;
    }
    printf("%d\n",(int)gPathDist[_FINISH_IDX-1]);
    PrintPath(gPathFrom[_FINISH_IDX-1]);//选取其中从终点开始的那一条
}

int main()
{
    int i,N,D;
    scanf("%d %d",&N,&D);//D->最大跳跃长度，N->节点数
    InitMatrix();
    InitTables();
    for(i=0;i<N;i++)
    {
        scanf("%d %d",&gNodeTab[i].x,&gNodeTab[i].y);
    }
    FindStartAndFinishNode(N,D);
    BuildMatrix(N,D);
//  DBG_ShowStatus(N);
    Dijkstra(N);
    Output(N,D);
}