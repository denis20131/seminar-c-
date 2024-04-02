#include <stdio.h>
#include <stdlib.h>
struct tree
    {
        int key;
        struct tree* left;
        struct tree* right;
        };

struct tree *create_tree()
{
    struct tree *T = NULL;
    int num;
    while (scanf("%d", &num) != -1)
    {
        struct tree *node = (struct tree *)malloc(sizeof(struct tree));
        node->key = num;
        node->left = NULL;
        node->right = NULL;

        if (T == NULL)
            T = node;
        else
        {
            struct tree *C = T;
            int flag = 1;
            while (flag)
            {
                if (num <= C->key)
                {
                    if (C->left == NULL)
                    {
                        C->left = node;
                        flag = 0;
                    }
                    else
                        C = C->left;
                }
                else
                {
                    if (C->right == NULL)
                    {
                        C->right = node;
                        flag = 0;
                    }
                    else
                        C = C->right;
                }
            }
        }
    }
    return T;
}

void del_tree(struct tree** T){
    if(!(*T)) return;
    del_tree(&((*T)->left));
    del_tree(&((*T)->right));
    free(*T);
    *T = NULL;
}

void printtree(struct tree* T){
    if (T!=NULL)
        {
           printf("%d\n",T->key);
           printtree(T->left);
           printtree(T->right);
        }
    
}

int check(struct tree* T, int n){
    if(!T) return 0;
    else if(T->key == n) return 1;
    else return check(T->left, n) || check(T->right,n);
}

int high(struct tree *T,int N)
{
    if (check(T,N)==-1) return -1;
    if (N==(T->key)) return 0;
    if (N>(T->key)) return 1+(high(T->right,N));
    if (N<(T->key)) return 1+(high(T->left,N));
}

int main()
    {
      struct tree* T=create_tree();
      printf("\n");
      printtree(T);
      if (check(T,2)== 1) printf("Входит\n");
      else printf("не входит\n");
      printf("%d\n",high(T,2));
      del_tree(&T);
      return 0;
    }