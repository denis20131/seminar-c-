#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct list
{
    char *elem;
    int length;
    struct list *next;
};
struct elems
{
    struct list *elem;
    size_t length;
    struct list *next;
};

void addelem(struct list *L,char *c) //добавление элемента в список
{
  struct list *L_cops =(L);
  if (!(L))
    {
      (L)=malloc(sizeof(struct list));
      (L)->elem = malloc(256);
      strcpy((L)->elem,c);
      (L)->next =NULL;
    }
  else
    {
      while (L_cops->next)
      {
        L_cops = L_cops->next;
      }
      L_cops->next=malloc(sizeof(struct list));
      L_cops->next->elem=malloc(256);
      strcpy(L_cops->next->elem,c);
    }
}
void createlist(struct list *L) //создание списка
{
    char *c;
    c = malloc(256);
    while(scanf("%s",c)!=-1)
    {
      scanf("%s",c);
      addelem(L,c);
      free(c);
    }
}

void listprint(struct list *l)
{
  struct list *p;
  p = l;
  do {
    printf("%s %lu", p->elem,strlen(p->elem));
    p = p->next;
  } while (p != NULL);
}

void deletelist(struct list *L) //удаление списка
{
    if (!(L)) {return;}
    if (!((L)->next))
      {
        free((L)->elem);
        free(L);
      }
    else
      {
        free(L->elem);
        deletelist((L)->next);
        free(L);
      }
    L=NULL;
}

int main()
{
    struct list *L;
    createlist(L);
    //listprint(L);
    //deletelist(L);
    return 0;
}
