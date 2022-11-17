#include <stdlib.h>
#include <stdio.h>
#include "Item.h"
#define null(A) (key(st[A]) == key(NULLitem))
static int N, M;
static Item *st;

int
hash (Key v, int M)
{
  return v % M;
}

void
STinit (int max)
{
  int i;
  N = 0;
  M = 2 * max;
  st = malloc (M * sizeof (Item));
  for (i = 0; i < M; i++)
    st[i] = NULLitem;
}

int
STcount ()
{
  return N;
}

void
STinsert (Item item)
{
  Key v = key (item);
  int i = hash (v, M);
  while (!null (i))
    i = (i + 1) % M;
  st[i] = item;
  N++;
}

Item
STsearch (Key v)
{
  int i = hash (v, M);
  int cnt = 0;
  while (!null (i))
  {
    if eq(v, key (st[i])) return st[i];
    else
      i = (i + 1) % M;
    cnt++;
  }
  printf("[searched %d times] ",cnt);
  return NULLitem;
}

void
STdelete (Item item)
{
  int j, i = hash (key (item), M);
  Item v;
  while (!null (i))
    if eq(key (item), key (st[i])) break;
    else
      i = (i + 1) % M;
  if (null (i))
    return;
  st[i] = NULLitem;
  N--;
  for (j = i + 1; !null (j); j = (j + 1) % M, N--)
    {
      v = st[j];
      st[j] = NULLitem;
      STinsert (v);
    }
}
