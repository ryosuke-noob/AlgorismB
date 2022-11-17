#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "ST.h"

#define MAX 97
#define TRIAL 30

int
main (int argc, char **argv)
{
  Item u, v;
  STinit (MAX);

  int cnt;
  for (cnt = 0; cnt < atoi (argv[1]) && cnt < 2 * MAX;)
  {
    int k = rand ();
    key (u) = k;
    v = STsearch (k);

    if (key (v) != key (NULLitem))
      printf ("Key %d is found in the table.\n", k);
    else
    {
      cnt++;
      STinsert (u);
      printf ("[cnt:%3d] Key %d is not found in the table.\n", cnt, k);
    }
  }

  // int n;
  // n = ((((((97%97)*128+98)%97)*128+99)%97)*128+100)%97;
  // printf("[%d]\n",n);

  return 0;
}
