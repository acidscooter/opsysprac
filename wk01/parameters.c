#include <stdio.h>

int scope(int a, double d)
{
  float f;
  
  f = d + 3.141596;
  a++;

  printf("Scope f=%f, a=%d\n", f, a);
  
  return (int)f;
}

int main()
{
  float f = 2.7123409;
  int a = 33;

  scope(777, f);

  printf("Main f=%f, a=%d\n", f, a);

  return 0;
} 
    
