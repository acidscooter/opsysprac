#define LOOP 10
#define CUBE(z) ((z)*(z)*(z))
#define QUAD(z) (CUBE(z)*(z))

int main()
{
  int i;
  int result;
  for(i=0; i<LOOP; i++) {
    result += CUBE(i);
    result += QUAD(i+3);
    result += CUBE(QUAD(LOOP-i));
  }
}
