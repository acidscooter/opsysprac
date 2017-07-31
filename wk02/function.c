#include <stdio.h>

void inc(int *i)
{
  printf("inc: passed parameter value: %p\n", i);
  *i = *i +1;
}


int main()
{
  int k = 4;

  printf("main: k address %p, k value %d\n", &k, k);
  inc(&k);
  printf("main: k address %p, k value %d\n", &k, k);
}  
