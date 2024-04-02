#include <stdio.h>
#include <stdlib.h>

struct list 
{
    int elem;
    struct list *next;
};


void create_list(struct list **l)
{int n;
    struct list *node=*l;
    while (scanf("%d",&n)==1)
        {if (!(*l))
            {
                (*l)=malloc(sizeof(struct list));
                (*l)->elem=n;
                (*l)->next=NULL;
                node=*l;
            }
            else
                {
                    node->next=malloc(sizeof(struct list));
                    node->next->elem=n;
                    node->next->next=NULL;
                    node=node->next;
                }
        }
}

void print_list(struct list *l)
{
    struct list *p;
    p=l;
    if (!p) {printf("NULL\n");return;}
    while(p)
    {
    printf("%d  ",p->elem);
    p=p->next;
    }
    printf("\n");
}

void del_list(struct list **l)
{
    while(*l)
    {
        struct list *p=*l;
        (*l)=(*l)->next;
        free(p);
    }
    (*l)=NULL;
}

struct  list* reverse_list(struct  list* l) 
{
  struct  list* next = NULL;
  struct  list* p = NULL;
  struct  list* l1 = l;
   while (l1 != NULL) 
   {
        next = l1->next;
        l1->next = p;
        p = l1;
        l1 = next;
    }
    return p;
}

int main()
{
    struct list *l=NULL;
    create_list(&l);
    printf("\n");
    printf("Изначальный список\n");
    print_list(l);
    l=reverse_list(l);
    printf("Перевёрнутый список\n");
    print_list(l);
    del_list(&l);
    return 0;
}