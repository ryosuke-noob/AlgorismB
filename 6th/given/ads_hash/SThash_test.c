#include <stdio.h>
#include "Item.h"
#include "ST.h"

int
main (void)
{
  Item u, v;
  Key k = 100, l = 101;
  key (u) = k;

  STinit (10);
  STinsert (u);

  v = STsearch (k);
  if (key (v) != key (NULLitem))
    printf ("Key %d is found in the table.\n", k);
  else
    printf ("Key %d is not found in the table.\n", k);

  v = STsearch (l);
  if (key (v) != key (NULLitem))
    printf ("Key %d is found in the table.\n", l);
  else
    printf ("Key %d is not found in the table.\n", l);

  return 0;
}
