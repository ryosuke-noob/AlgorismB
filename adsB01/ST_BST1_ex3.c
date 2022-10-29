#include <stdlib.h>
#include <stdio.h>
#include "Item.h"
#define max(p,q)((p)>(q)?(p):(q))
typedef struct STnode* link;
struct STnode { Item item; link l, r; int N; };
static link head, z;

link NEW(Item item, link l, link r, int N)
{ link x = malloc(sizeof *x); 
  x->item = item; x->l = l; x->r = r; x->N = N;
  return x;
}

void STinit()
{ head = (z = NEW(NULLitem, 0, 0, 0)); }

int STcount(void) { return head->N; }

Item searchR(link h, Key v)
{ Key t = key(h->item);
  if (h == z) return NULLitem;
  if eq(v, t) return h->item;
  if less(v, t) return searchR(h->l, v);
  else return searchR(h->r, v);
}

Item STsearch(Key v) 
{ return searchR(head, v); } 

link insertR(link h, Item item)
{ Key v = key(item), t = key(h->item);
  if (h == z) return NEW(item, z, z, 1);
  if less(v, t) 
	   h->l = insertR(h->l, item);
  else h->r = insertR(h->r, item);
  (h->N)++; return h;
}

void STinsert(Item item)
{ head = insertR(head, item); }

void sortR(link h, void (*visit)(Item))
{ 
  if (h == z) return;
  sortR(h->l, visit);
  visit(h->item); 
  sortR(h->r, visit);
}

void STsort(void (*visit)(Item))
{ sortR(head, visit); } 

///////////////////////////////////////
//height
int heightR(link h, int level)
{
  int height;

  if (h != z)
    height = max(heightR(h->l, level+1),heightR(h->r, level+1));
  else
    height = level - 1;
  return (height);
}

void STheight(void)
{
  printf("Height : %d\n",heightR(head, 0));
}

//internal 
void ipathlengthR(link h, int level, int *internal)
{
  if (h == z)
    return ;
  *internal += level;
  ipathlengthR(h->l, level+1, internal);
  ipathlengthR(h->r, level+1, internal);
}

void STipathlength(void)
{
  int internal = 0;

  ipathlengthR(head, 0, &internal);
  printf("Internal Pathlength : %d\n",internal);
}

//external
void epathlengthR(link h, int level, int *external)
{
  if (h == z)
  {
    *external += level;
    return ;
  }
  epathlengthR(h->l, level+1, external);
  epathlengthR(h->r, level+1, external);
}

void STepathlength(void)
{
  int external = 0;

  epathlengthR(head, 0, &external);
  printf("Enternal Pathlength : %d\n",external);
}

