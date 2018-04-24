//
// Created by 唐和辉 on 2018/4/24.
//

#include <stdio.h>
#include <stdlib.h>

int b[1005];
int j=0;

int compare(const void * a,  const void * b);
void mid_tre(int root,int N,int a[]);

int main(){
    int N;
    int i=0;
    scanf("%d",&N);
    int a[N];
    for(i=0;i<N;i++){
        scanf("%d",&a[i]);
    }
    qsort(a,N,sizeof(int),compare);
    mid_tre(1,N,a);
    printf("%d",b[1]);
    for(i=2;i<=N;i++){
        printf(" %d",b[i]);
    }
}

int compare(const void * a, const void * b)
{
    return *(int *)a - *(int *)b;
}

void mid_tre(int root,int N,int a[]){
    if(root<=N){
        mid_tre(2*root,N,a);//左节点（父节点下标的2倍）
        b[root]=a[j++];//将中序遍历产生的序列按照排序后的下标放回其原有位置
        mid_tre(2*root+1,N,a);//右节点（父节点下标的 2i+1 倍）
    }
}

/*
 * 利用了完全二叉树的性质：若 a 节点的下标为 i，那么它左儿子的下标为 2i，
 * 右儿子为 2i+1，这个下标就是完全二叉树在层序遍历
 * 时的输出顺序
 */
/*                   节点位置
 *                      6
 *                  /        \
 *                3            8
 *              /    \      /     \
 *            1        5   7       9
 *          /   \     /
 *         0     2  4
 *
 */
/*                   节点下标
 *                      1
 *                  /        \
 *                2            3
 *              /    \      /     \
 *            4        5   6       7
 *          /   \     /
 *         8     9  10
 *
 */