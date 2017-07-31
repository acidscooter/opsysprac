#include <stdio.h>

int main()
{
  float f;
  int i;
  char c;


  f = 72.764;
  i = (int)f;
  c = (char)f;

  printf("Float=%f, Integer=%d, Character=%c\n", f, i, c);

  i = 89;
  f = (float)i;
  c = (char)i;

  printf("Float=%.12f, Integer=%d, Character=%c\n", f, i, c);

  c = 'Z';
  f = (float)c;
  i = (int)c;

  printf("Float=%f, Integer=%d, Character=%c\n", f, i, c);

  i=34;
  c=4;

  f = i/c;

  printf("Float (%d/%d) = %f\n", i, c, f);
  
  f = (float)i/(float)c;

  printf("Float (float)%d/(float)%d = %f\n", i, c, f);

  f = i/(float)c;

  printf("Float %d/(float)%d = %f\n", i, c, f);

  f = (float)i/c;

  printf("Float (float)%d/%d = %f\n", i, c, f);

  return 0;
}
