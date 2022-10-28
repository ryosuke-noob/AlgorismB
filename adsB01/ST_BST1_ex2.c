#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include "Item.h"
typedef struct STnode* link;
struct STnode { Item item; link l, r; int N; };
static link head, z;
static int counter = 0;

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
{ 
  unsigned int sec;
  int nsec;
  double d_nsec;
  double d_msec;

  struct timespec start_time, end_time;
  clock_gettime(CLOCK_REALTIME, &start_time);

  head = insertR(head, item);

  clock_gettime(CLOCK_REALTIME, &end_time);

  sec = end_time.tv_sec - start_time.tv_sec;
  nsec = end_time.tv_nsec - start_time.tv_nsec;

  d_nsec = (double)sec + (double)nsec / (1000 * 1000 * 1000);
  // d_msec = d_nsec / 1000 / 1000;

  if (d_nsec != 0) printf("%d BST1 time[s] : %f\n",++counter,d_nsec);
  // printf("BST1 time[ms] : %f\n",d_msec);
}

void sortR(link h, void (*visit)(Item))
{ 
  if (h == z) return;
  sortR(h->l, visit);
  visit(h->item); 
  sortR(h->r, visit);
}

void STsort(void (*visit)(Item))
{ sortR(head, visit); } 
