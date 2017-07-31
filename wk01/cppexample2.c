#include <stdio.h>



int main()
{
  int i;
  int accumulate;

#ifdef FACT
  accumulate = 1;
#else
  accumulate = 0;
#endif

  for(i=1; i<11; i++) {

#ifdef FACT
    accumulate *= i;
#else
    accumulate += i;
#endif

  }

#ifdef FACT
  printf("Factorial=%d\n", accumulate);  
#else
  printf("Sum=%d\n", accumulate);   
#endif

}
