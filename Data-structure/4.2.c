//
// Created by 唐和辉 on 2018/4/24.
//

//AVL的原理和图示见 http://www.cnblogs.com/Camilo/p/3917041.html
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20

typedef struct AVLTreeNode *AVLTree;
typedef struct AVLTreeNode{
    int Data;
    AVLTree left;
    AVLTree right;
    int Height;
};
AVLTree workT=NULL;

int Max(int a,int b)
{
    return a>b?a:b;
}

int GetHeight(AVLTree T)
{
    if(T==NULL)
        return 0;
    else
        return T->Height;
}

//旋转部分-------------------------------------------------
//左单旋算法
AVLTree SingleLeftRotation(AVLTree A)
{
//A必须有一个左子结点b
//问题出在左子树的左子树上
//将A与B做左单旋，更新A与B的高度，然后把B返回
    AVLTree B = A->left;
    A->left = B->right;
    B->right = A;
    A->Height = Max(GetHeight(A->left),GetHeight(A->right)) +1;
    B->Height = Max(GetHeight(B->left),GetHeight(B->right)) +1;
    return B;
}

AVLTree SingleRightRotation(AVLTree A)
{
//右单旋，问题出在右子树的右子树上
    AVLTree B = A->right;
    A->right = B->left;
    B->left = A;
    A->Height = Max(GetHeight(A->left),GetHeight(A->right)) +1;
    B->Height = Max(GetHeight(B->left),GetHeight(B->right)) +1;
    return B;
}
AVLTree DoubleLeftRightRotation(AVLTree A)
{
//左右双旋，插入的不平衡出现在左孩子的右子树上
//先对A的左儿子进行右单旋，再对A进行左单旋
    A->left = SingleRightRotation(A->left);
    return SingleLeftRotation(A);
}
AVLTree DoubleRightLeftRotation(AVLTree A)
{
//右左双旋，插入的不平衡出现在右孩子的左子树上
//先对A的右儿子进行左单旋，再对A进行右单旋
    A->right = SingleLeftRotation(A->right);
    return SingleRightRotation(A);
}

//插入操作--------------------------------------------

AVLTree AVL_Insertion(int X,AVLTree T)
{
    if(T==NULL)
    {
//      printf("ready to malloc\n");
        T= malloc(sizeof(struct AVLTreeNode));
        T->Data = X;
        T->Height = 0;
        T->left = T->right = NULL;
//      printf("create node done\n");
    }
    else if(X < T->Data)
    {
        T->left = AVL_Insertion( X , T->left);
        if(GetHeight(T->left) - GetHeight(T->right) == 2)
            if(X < T->left->Data)
                T = SingleLeftRotation(T); //左单旋
            else
                T = DoubleLeftRightRotation(T);//左右双旋
    }
    else if(X > T->Data)
    {
        T->right = AVL_Insertion( X , T->right);
        if(GetHeight(T->right) - GetHeight(T->left) == 2)
            if(X > T->right->Data)
                T = SingleRightRotation(T);
            else
                T= DoubleRightLeftRotation(T);
    }
    // X==T时无需插入
    T->Height = Max(GetHeight(T->left),GetHeight(T->right)) + 1;  //树高为子树高度+1；

    return T; //返回调整后的树
}


//--------------------------------------------------------
//查找
AVLTree Find(int X,AVLTree T)
{
    if (T == NULL)
        return NULL;
    if (T->Data == X)
        return T;
    else if(T->Data > X)
        return Find(X,T->right);
    else if(T->Data < X)
        return Find(X,T->left);
}

int gNum;
int gWorkarray[MAX_N];
int getinput()
{
    int i,temp;
    scanf("%d",&gNum);
    for(i=0;i<gNum;i++)
    {
        scanf("%d",&temp);
        workT=AVL_Insertion(temp,workT);
    }
}

int main()
{
    getinput();
    printf("%d",workT->Data);
}
