#include <stdio.h>
#include <math.h>

double distance(double x, double y, double z)
{
  return sqrt(x*x+y*y+z*z);
}


int main()
{
  double d = distance(4.0, -3.0, 5.34);

  printf("Distance=%g\n",d);

  return 0;
}
