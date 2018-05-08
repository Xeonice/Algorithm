//
// Created by 唐和辉 on 2018/5/4.
//

#include "iostream"
#include "stdio.h"
#include "queue"
using namespace std;
bool map[10001][10001] = {false};
int n, m;
int Count;
void bfs(int x) {
    bool visited[10001] = { false };
    queue<int>q;
    q.push(x);
    visited[x] = true;
    int level = 0; /* 记录层数 */
    int last = x; /* 记录当前层数的最后一个元素 */
    int tail; /* 指向下一层最后一个元素 */
    while (!q.empty()) {
        x = q.front();
        q.pop();
        for (int i = 1; i <= n; i++) {
            if (!visited[i] && map[x][i] == 1) {
                q.push(i); /* 进队 */
                Count++;
                visited[i] = true;
                tail = i;
            }
        }
        if (last == x) {
            level++;
            last = tail;
        }
        if (level == 6)
            break;
    }
}
int main() {
    cin >> n >> m;
    //初始化图
    for (int i = 0; i < m; i++) {
        int k, l;
        cin >> k >> l;
        map[k][l] = 1;//无向图，记录当前节点
        map[l][k] = 1;
    }
    for (int i = 1; i <=n; i++) { /* 对于所有节点 做bfs() */
        Count = 1;
        bfs(i);
        cout << i << ": ";
        float answer = (float)Count / n * 100;
        printf("%.2f%%\n", answer);
    }
    return 0;
}