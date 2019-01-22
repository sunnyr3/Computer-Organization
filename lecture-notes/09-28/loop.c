/* loop.c */

#include <stdio.h>
#include <stdlib.h>

int main()
{
  int i, k;
  int A[10000];
  while ( i < 100 )
  {
    int result = ( i % 2 == 0 );   /* even? */

    k = i * 9;     /*  k = i * 8 + i */
    k = i * 18;    /*  k = i * 8 + i * 8 + i + i */
    A[k] = 1234;
    i++;
  }

  return EXIT_SUCCESS;
}
