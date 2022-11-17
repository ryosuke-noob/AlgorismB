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
	  printf ("Key %d is not found in the table.\n", k);
	}
    }

  return 0;
}
