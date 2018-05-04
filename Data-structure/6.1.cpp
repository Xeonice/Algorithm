//
// Created by 唐和辉 on 2018/5/4.
//
/*
 * 06-图1 列出连通集（25 分）
 * 给定一个有N个顶点和E条边的无向图，请用DFS和BFS分别列出其所有的连通集。假设顶点从0到N−1编号。进行搜索时，假设我们总是从编号最小的顶点出发，按编号递增的顺序访问邻接点。

 * 输入格式:
 * 输入第1行给出2个整数N(0<N≤10)和E，分别是图的顶点数和边数。随后E行，每行给出一条边的两个端点。每行中的数字之间用1空格分隔。

 * 输出格式:按照"{ v1, v​2... vk }"的格式，每行输出一个连通集。先输出DFS的结果，再输出BFS的结果。

 * 输入样例:
    8 6
    0 7
    0 1
    2 0
    4 1
    2 4
    3 5
 * 输出样例:
    { 0 1 4 2 7 }
    { 3 5 }
    { 6 }
    { 0 1 2 7 4 }
    { 3 5 }
    { 6 }
 */

#include <cstdio>

#define N 15

void ListComponentsWithDFS();
void ListComponentsWithBFS();
void DFS(int V);
void BFS(int V);
void InitVisit(void);

int n;
bool Visited[N];
int G[N][N] = {0};

int main()
{
    int E;

    scanf("%d%d", &n, &E);
    for (int i = 0; i < E; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        G[b][a] = G[a][b] = 1;//无向图
    }
    ListComponentsWithDFS();
    InitVisit();
    ListComponentsWithBFS();

    return 0;
}

void ListComponentsWithDFS()
{
    for (int V = 0; V < n; V++)
        if (!Visited[V])
        {
            printf("{ ");
            DFS(V);
            printf("}\n");
        }
}

void ListComponentsWithBFS()
{
    for (int V = 0; V < n; V++)
        if (!Visited[V])
        {
            printf("{ ");
            BFS(V);
            printf("}\n");
        }
}

void DFS(int V)//深度优先
{
    Visited[V] = true;
    printf("%d ", V);
    for (int i = 0; i < n; i++)
    {
        if (G[V][i] && !Visited[i])//存在边且未被访问
            DFS(i);
    }
}

void BFS(int V)//广度优先
{
    const int MAX_SIZE = 100;
    int Queue[MAX_SIZE];
    int first = -1, last = -1;//设置两个哨兵

    Queue[++last] = V;      //入队
    Visited[V] = true;
    while (first < last)    //当队不为空时
    {
        int F = Queue[++first];     //出队
        printf("%d ", F);
        for (int i = 0; i < n; i++)
        {
            if (G[F][i] && !Visited[i])//存在边且未被访问
            {
                Queue[++last] = i;      //入队
                Visited[i] = true;
            }
        }
    }
}

void InitVisit()//DFS 后重置访问标记
{
    for (int i = 0; i < N; i++)
        Visited[i] = false;
}