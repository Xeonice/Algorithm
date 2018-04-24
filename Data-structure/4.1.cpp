#include <cstdlib>
#include <cstdio>
using namespace std;
typedef struct treeNode *tree;
//两个树之间仅仅添加顺序不同，说明其他信息相同
struct treeNode{
    int v;
    tree left, right;
    int flag;
};
tree newNode(int V){
    tree T = (tree)malloc(sizeof(struct treeNode));
    T->v = V;
    T->left = T->right = NULL;
    T->flag = 0;
    return T;
}
tree insert(tree T, int V){
    if(!T) T = newNode(V);     //插入每个结点都靠这句话！
    else {
        if(V > T->v)
            T->right = insert(T->right, V);
        else
            T->left = insert(T->left, V);
    }
    //T->v = V;
    return T;
}
tree makeTree(int N){
    int V;
    tree T;
    //tree T = (tree)malloc(sizeof(struct treeNode));
    scanf("%d", &V);
    T = newNode(V);
    for(int i = 1; i < N; i++){
        scanf("%d", &V);
        T = insert(T,V);
    }
    return T;
}
int check(tree T, int V){       //按顺序查找结点，如果经过的结点之前未经过，说明不是同一颗二叉树
    if(T->flag){                //（因为结点本该插在这个未经过的结点的位置，但现在却经过了它）
        if(V > T->v) check(T->right, V);
        else if(V < T->v) check(T->left, V);
        else return 0;
    }
    else {
        if(V == T->v) {
            T->flag = 1;
            return 1;
        }
        else return 0;
    }
}
int judge(tree T, int N){
    int V, flag = 0;    //0表示查询符合
    scanf("%d", &V);
    if(T->v != V) flag = 1;   //根结点不同，树不同
    else T->flag = 1;
    for(int i = 1; i < N; i++){
        scanf("%d", &V);
        //短路特性，一旦有节点判断出现问题，就自动接收并跳过接下来的循环
        if(!flag && !check(T, V)) flag = 1;    //即使已经得到判断，也要把剩下的结点接收完，防止影响下一组数据
    }
    if(flag) return 0;
    else return 1;
}
void reset(tree T){
    if(T->left) reset(T->left);
    if(T->right) reset(T->right);
    T->flag = 0;
}
void freeTree(tree T){
    if(T->left) freeTree(T->left);
    if(T->right) freeTree(T->right);
    free(T);
}
int main(){
    int N, L;
    tree T;
    scanf("%d", &N);
    while(N){
        scanf("%d", &L);
        T = makeTree(N);
        for(int i = 0; i < L; i++){
            if(judge(T, N)) printf("Yes\n");
            else printf("No\n");
            reset(T);
        }
        freeTree(T);
        scanf("%d", &N);      //接收下一组
    }

    system("pause");
    return 0;
}