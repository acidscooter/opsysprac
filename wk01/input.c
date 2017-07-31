#include <stdio.h>

int main()
{
  char input[8];
  int k = 3;

  printf("Please enter a string: ");
  gets(input);
  printf("The string you entered is: %s\n", input);
  printf("The integer k=%d\n", k);

  return 0;
}
