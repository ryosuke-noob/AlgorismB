/*
 * Author: Hiroyuki Chishiro
 * License: 2-Clause BSD
 */
#include <stdio.h>
#include <time.h>
 
#define N 1000000000
 
void do_work(void)
{
  volatile size_t i;
 
  for (i = 0; i < N; i++) {
  }
}
 
int main(void)
{
  clock_t begin, end;
 
  begin = clock();
  do_work();
  end = clock();
 
  printf("Execution Time = %lf [s]\n", difftime(end, begin) / CLOCKS_PER_SEC);
 
  return 0;
}