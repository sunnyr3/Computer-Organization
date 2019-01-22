/* factorial.c */

#include <stdio.h>
#include <stdlib.h>

int factorial( int n )
{
  if ( n < 1 ) return 1;
  else return n * factorial( n - 1 );
}

int main()
{
  int result = factorial( 10 );
  printf( "10! is %d\n", result );

  return EXIT_SUCCESS;
}
