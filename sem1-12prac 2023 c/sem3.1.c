#include <stdio.h>
#include <stdlib.h>
struct tree
    {
        int key;
        struct tree* left;
        struct tree* right;
        };

struct tree *create_tree() //построение дерева
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

void del_tree(struct tree *T) //удаление дерева
{
    if (T == NULL)
        return;
    del_tree (T->left);
    del_tree (T->right);
    free(T);
}

void printtree(struct tree* T) //вывод дерева
{
    if (T!=NULL)
        {
           printf("%d\n",T->key);
           printtree(T->left);
           printtree(T->right);
        }
    
}

struct tree *delete_node(struct tree *T, int key) // Функция для удаления узла с заданным ключом из дерева
{
    if (!T) return NULL;
    // Рекурсивно ищем узел, который нужно удалить
    if (key > T->key)   T->right = delete_node(T->right, key);
        else 
            if (key < T->key)   T->left = delete_node(T->left, key);
                else
                    {
                         if (!T->right)
                        {
                            struct tree *buf = T->left;
                            free(T);
                            return buf;
                        }
                        else 
                            if (!T->left)
                        {
                            struct tree *buf = T->right;
                            free(T);
                            return buf;
                        }

                        struct tree *min = T->right;
                        while (min->left)   //поиск минимального узла в дереве
                            min= min->left;
                        T->key = min->key; //  Копируем данные наименьшего узла в текущий узел
                        T->right = delete_node(T->right, min->key); //  Рекурсивно удаляем наименьший узел в правом поддереве
                    }

    return T;
}

void tree_Array(struct tree *T, int *arr, int *index) // из деррева делаеем массив отсортированный
{
    if (!T)
        return;

    tree_Array(T->left, arr, index);
    if (arr)
        arr[*index] = T->key;
    (*index)+=1;
    tree_Array(T->right, arr, index);
}

struct tree *balanced(int *arr, int start, int end) // Функция для преобразования отсортированного массива в сбалансированное дерево
{
    if (start > end)
     
        return NULL;

    int mid = (start + end) / 2;

    struct tree *T = (struct tree *)malloc(sizeof(struct tree));
    T->key = arr[mid];
    T->left = balanced(arr, start, mid - 1);
    T->right = balanced(arr, mid + 1, end);

    return T;
}

struct tree *balance(struct tree *T)
{
    int size = 0;
    tree_Array(T, NULL, &size);

    int *arr = (int *)malloc(sizeof(int) * size);
    int index = 0;
    tree_Array(T, arr, &index);
    del_tree(T);

    T = balanced(arr, 0, size - 1);
    free(arr);
    return T;
}

int main()
    {
      struct tree* T=create_tree();
      printf("\n");
      T=delete_node(T,10);
      printf("Новое дерево после удаления:\n");
      printtree(T);
      T=balance(T);
      printf("Новое сбалансированное дерево:\n");
      printtree(T);
      del_tree(T);
      return 0;

    }