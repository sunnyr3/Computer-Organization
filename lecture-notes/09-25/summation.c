#include <stdio.h>
#include <stdlib.h>

int main()
{
  int i;
  int sum = 0;
  int from = 1, to = 100;
  for ( i = from ; i <= to ; i++ ) sum += i;
  printf( "The sum from %d to %d is %d\n", from, to, sum );
  return EXIT_SUCCESS;
}

