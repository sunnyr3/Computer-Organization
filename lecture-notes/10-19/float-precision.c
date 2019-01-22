/* float-precision.c */

#include <stdio.h>
#include <stdlib.h>

int main()
{
  float x = -1.5E+38;
  float y = 1.5E+38;
  float z = 1.0;

  float r1 = ( x + y ) + z;
  float r2 = x + ( y + z );

  printf( "r1: %.17f\n", r1 );
  printf( "r2: %.17f\n", r2 );

  return EXIT_SUCCESS;
}
