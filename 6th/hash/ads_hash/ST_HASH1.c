#include <stdlib.h>
#include "Item.h"
typedef struct STnode *link;
struct STnode
{
  Item item;
  link next;
};
static link
NEW (Item item, link next)
{
  link x = malloc (sizeof *x);
  x->item = item;
  x->next = next;
  return x;
}

int
hash (Key v, int M)
{
  return v % M;
}

static link *heads, z;
static int N, M;
void
STinit (int max)
{
  int i;
  N = 0;
  M = max / 5;
  heads = malloc (M * sizeof (link));
  z = NEW (NULLitem, NULL);
  for (i = 0; i < M; i++)
    heads[i] = z;
}

Item
searchR (link t, Key v)
{
  if (t == z)
    return NULLitem;
  if (eq(key (t->item), v))
    return t->item;
  return searchR (t->next, v);
}

Item
STsearch (Key v)
{
  return searchR (heads[hash (v, M)], v);
}

void
STinsert (Item item)
{
  int i = hash (key (item), M);
  heads[i] = NEW (item, heads[i]);
  N++;
}
