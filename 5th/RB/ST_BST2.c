#include <stdlib.h>
#include <stdio.h>
#include "Item.h"
#define hl  h->l
#define hr  h->r
#define hll h->l->l
#define hlr h->l->r
#define hrl h->r->l
#define hrr h->r->r

typedef struct STnode* link;
struct STnode
{
  Item item;
  link l, r;
  int N;
  int red;
};
static link head, z;

link NEW (Item item, link l, link r, int N, int red)
{
  link x = malloc (sizeof *x);
  x->item = item;
  x->l = l;
  x->r = r;
  x->N = N;
  x->red = red;
  return x;
}

void STinit ()
{
  head = (z = NEW (NULLitem, 0, 0, 0, 0));
}

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

link rotR(link h)
{
  link x = h->l;
  h->N -= x->l->N + 1;
  x->N += h->r->N + 1;
  h->l = x->r;
  x->r = h;
  return x;
}

link rotL(link h)
{
  link x = h->r;
  h->N -= x->r->N + 1;
  x->N += h->l->N + 1;
  h->r = x->l;
  x->l = h;
  return x;
}

link RBinsert (link h, Item item, int sw)
{
  Key v = key (item);
  if (h == z)
    return NEW (item, z, z, 1, 1);
  h->N++;
  if ((hl->red) && (hr->red))
  {
    h->red = 1;
    hl->red = 0;
    hr->red = 0;
  }
  if (less (v, key (h->item)))
  {
    hl = RBinsert (hl, item, 0);
    if (h->red && hl->red && sw)
	    h = rotR (h);
    if (hl->red && hll->red)
    {
      h = rotR (h);
      h->red = 0;
      hr->red = 1;
    }
  }
  else
  {
    hr = RBinsert (hr, item, 1);
    if (h->red && hr->red && !sw)
      h = rotL (h);
    if (hr->red && hrr->red)
    {
      h = rotL (h);
      h->red = 0;
      hl->red = 1;
    }
  }
  return h;
}

void STinsert (Item item)
{
  head = RBinsert (head, item, 0);
  head->red = 0;
}

void sortR(link h, void (*visit)(Item))
{ 
  if (h == z) return;
  sortR(h->l, visit);
  visit(h->item); 
  sortR(h->r, visit);
}

int countB(link h, Key v, int count)
{
  Key t = key(h->item);
  if (h == z) return -1;
  if (h->red != 1)
    count++;
  if eq(v, t) return count;
  if less(v, t) return countB(h->l, v, count);
  else return countB(h->r, v, count);
}

void STsort(void (*visit)(Item))
{ sortR(head, visit); } 

void STshow(link h, int l)
{
  int i=0;
  if(h != NULL){
    STshow(h->r, l+1);
    for(i=0; i<l; i++) printf("\t");
    if (h->r || h->l)
    {
      if (h->r->item.key != -1 || h->l->item.key != -1)
        printf("(%d,%d,%d)\n",key(h->item), h->N, h->red);
      else
        printf("(%d,%d,%d,%d)\n",key(h->item), h->N, h->red, countB(head, key(h->item), -1));
    }
    else
      printf("(%d,%d,%d)\n",key(h->item), h->N, h->red);
    STshow(h->l, l+1);
  }
}

void STshowAll() {STshow(head, 0);} 
