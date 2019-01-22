/* floats.c */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
  float z = -0.9375;  /* 0.5 + 0.25 + 0.125 + 0.0625 */

  z = -0.75;
  z = -5.0;
  printf( "%f is represented as %a\n", z, z );

  union { float f; int u; } un = { .f = z };
  printf( "0x%x\n", un.u );


  /* OUTPUT:

     -0.500000 is represented as -0x1p-1
                                           -1
                                   -1.0 x 2

     -0.750000 is represented as -0x1.8p-1
                                           -1
                                   -1.0 x 2

     0xbf400000 ==> 1011 1111 0100 0000 ... 0000

     What value is represented using this 32-bit float?

      0xc0a00000
      1100 0000 1010 0000 ... 0000
      ^          ^^^^^^^^^^^^^^^^^
      S = 1       Fraction = 01000.....000

       Exponent = 10000001    = 129
                          two      ten

              S                       (Exp - Bias)
      R = (-1)  x ( 1 + Fraction ) x 2

              1                  (129-127)
      R = (-1)  x ( 1 + .01 ) x 2
                           2


      R = - ( 1.25 ) x 4

      R = - 5.0


   */

  return EXIT_SUCCESS;
}