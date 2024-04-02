#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list
{
  char *elem; // поле данных
  struct list *next; // указатель на следующий элемент
  struct list *prev; // указатель на предыдущий элемент
};

void addelem(struct list **L,char *c) //добавление элемента в список
{
  struct list *L_cops =(*L);
  if (!(*L))
    {
      (*L)=malloc(sizeof(struct list));
      (*L)->elem = malloc(256);
      strcpy((*L)->elem,c);
      (*L)->next =NULL;
      (*L)->prev =NULL;
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
      L_cops->next->next=NULL;
      L_cops->next->prev=L_cops;
      
    }
}

void createlist(struct list **L) //создание списка
{
  int n;//размер
  printf("Размер списка: ");
  scanf("%d",&n);
  for (int i=0;i<n;i++)
    {
      char *c;
      c = malloc(256);
      scanf("%s",c);
      addelem(L,c);
      free(c);
    }
}

int length(struct list *L) //длина списка
{
  int m=0;
  while (L)
  {
    L=L->next;
    m+=1;
  }
  return m;
}

void deletelist(struct list **L) //удаление списка
{
    if (!(*L)) {return;}
    if (!((*L)->next))
      {
        free((*L)->elem);
        free(*L);
      }
    else
      {
        free((*L)->elem);
        deletelist(&((*L)->next));
        free(*L);
      }
    (*L)=NULL;
}

void listprint(struct list **L) //вывод списка
{
  if (!(*L)) {printf("Список пуст\n");return;}
  printf("Список в прямом порядке\n");
  while ((*L)->next)
    {
      printf("%s ", (*L)->elem);
      (*L) = (*L)->next; 
    }
  printf("%s\n", (*L)->elem);
  printf("\nСписок в обратном порядке\n");
  while ((*L)->prev)
    {
      printf("%s ", (*L)->elem);
      (*L) = (*L)->prev; 
    }
  printf("%s\n", (*L)->elem);
}

void del_elem(struct list **L)
{
  int len=length(*L);
  int numb;
  printf("Номер удаляемого элемента "); //нумерация с единицы
  scanf("%d",&numb);
  if ((numb<0) || (numb>=len)) {fprintf(stderr,"Нет в списке элемента с этим номером\n");return;}
  if (numb==0)
    {
      struct list *L2=*L;
      (*L)=(*L)->next;
      free(L2->elem);
      free(L2);
      if (*L) (*L)->prev=NULL;
      return;
    }
  if (numb==(len-1))
    {
      struct list *L2=(*L);
      while(L2->next)
        L2=L2->next;
      L2->prev->next=NULL;
      free(L2->elem);
      free(L2);
      return; 
    }
  struct list *tmp = (*L);
  int k=0;
  while (k<numb)
    {
      tmp = tmp->next;
      k++;
    }
  tmp->prev->next=tmp->next;
  tmp->next->prev= tmp->prev;
  free(tmp->elem);
  free(tmp);
}

void insert(struct list **L)
{
  int m,number;//элемент для вставки и номер после которого она осуществляется
  int len=length(*L);
  char *s;
  s=malloc(256);
  printf("Вставляемый элемент ");
  scanf("%s",s);
  printf("номер элемента, после которого вставляем данный элемент: "); //нумерация элементов начинается с нуля
  scanf("%d",&number);
  if ((number<0) || (number>=len)) {fprintf(stderr,"Нет в списке элемента с этим номером\n");free(s);return;}
  if ((number==(len-1))||(len==0)) {addelem(L,s);free(s);return;}
  int k=0;
  struct list *tmp = (*L);
  
  while (k<number)
    {
      tmp = tmp->next;
      k++;
    }
  struct list *ins_elem;
  ins_elem=malloc(sizeof(struct list));
  ins_elem->elem = malloc(256);
  strcpy(ins_elem->elem,s);
  free(s);
  ins_elem->next = tmp ->next;
  tmp->next->prev= ins_elem;
  ins_elem->prev = tmp;
  tmp->next = ins_elem;
}

int main()
  {
    struct list *L=NULL ;
    createlist(&L);
    void (*f[3])(struct list**);
    f[0]= insert;
    f[1]=del_elem;
    f[2]=listprint;
    for (int i=0;i<=2;i++)
    {
      f[i](&L);
    }
    deletelist(&L);
    return 0;
  }