/* lab08.c */

#include <stdio.h>
#include <stdlib.h>

#define UNDEF -1
#define FALSE 0
#define TRUE 1

/* define BIT type as a char (i.e., one byte) */ 
typedef char BIT;

/* function prototypes (basic gates) */
BIT not_gate( BIT );
BIT or_gate( BIT, BIT );
BIT and_gate( BIT, BIT );
BIT xor_gate( BIT, BIT );

/* function prototypes (combinational circuits) */
BIT multiplexer( BIT, BIT, BIT, BIT, BIT, BIT );
void decoder( BIT, BIT, BIT*, BIT*, BIT*, BIT* );

/* function prototypes (sequential circuits) */
BIT sr_latch( BIT, BIT, BIT );

/* main() provides some unit testing */
int main()
{
   BIT A, B;
   BIT I0, I1, I2, I3;
   BIT O0, O1, O2, O3;
   BIT S0, S1;
   BIT S, R, Q;

   /* Unit test for NOT gate:
    *      _
    *  A | A
    * ---|---
    *  0 | 1
    *  1 | 0
    */
   printf( "===== Unit test for not_gate =====\n" );
   printf( "not_gate( A ) | RESULT\n" );
   printf( "--------------|--------\n" );
   printf( "not_gate( 0 ) | %d\n", not_gate( 0 ) );
   printf( "not_gate( 1 ) | %d\n", not_gate( 1 ) );
  

   /* Unit test for OR gate:
    *
    *  A  B | A OR B
    * ------|--------
    *  0  0 |   0
    *  0  1 |   1
    *  1  0 |   1
    *  1  1 |   1
    */
   printf( "\n===== Unit test for or_gate =====\n" );
   printf( "or_gate( A, B ) | RESULT\n" );
   printf( "----------------|--------\n" );

   for( A = 0 ; A < 2 ; A++ )
      for( B = 0 ; B < 2 ; B++ )
         printf( "or_gate( %d, %d ) | %d\n", A, B, or_gate( A, B ) );

   
   /* Unit test for AND gate:
    *
    *  A  B | A AND B
    * ------|--------
    *  0  0 |    0
    *  0  1 |    0
    *  1  0 |    0
    *  1  1 |    1
    */
   printf( "\n===== Unit test for and_gate =====\n" );
   printf( "and_gate( A, B ) | RESULT\n" );
   printf( "-----------------|--------\n" );

   for( A = 0 ; A < 2 ; A++ )
      for( B = 0 ; B < 2 ; B++ )
         printf( "and_gate( %d, %d ) | %d\n", A, B, and_gate( A, B ) );

   
   /* Unit test for XOR gate:
    *
    *  A  B | A XOR B
    * ------|--------
    *  0  0 |    0
    *  0  1 |    1
    *  1  0 |    1
    *  1  1 |    0
    */
   printf( "\n===== Unit test for xor_gate =====\n" );
   printf( "xor_gate( A, B ) | RESULT\n" );
   printf( "-----------------|--------\n" );

   for( A = 0 ; A < 2 ; A++ )
      for( B = 0 ; B < 2 ; B++ )
         printf( "xor_gate( %d, %d ) | %d\n", A, B, xor_gate( A, B ) );


   /* Unit test for 4-input multiplexer */
   printf( "\n===== Unit test for 4-input multiplexer =====\n" );
   printf( "multiplexer( S0, S1 ) | ( I0, I1, I2, I3 ) | RESULT ( I0 | I1 | I2 | I3 )\n" );
   printf( "----------------------|--------------------|------------------------------\n" );
   for( S0 = 0 ; S0 < 2 ; S0++ )
      for( S1 = 0 ; S1 < 2 ; S1++ )
         for( I0 = 0; I0 < 2; I0++ )
            for( I1 = 0; I1 < 2; I1++ )
               for( I2 = 0; I2 < 2; I2++ )
                  for( I3 = 0; I3 < 2; I3++ )
                     printf( "multiplexer( %2d, %2d ) | ( %2d, %2d, %2d, %2d ) | %2d\n",
                             S0, S1, I0, I1, I2, I3, multiplexer( I0, I1, I2, I3, S0, S1 ) );


   /* Unit test for 2-input decoder:
    *
    *  I0 I1 | O0 O1 O2 O3
    * -------|-------------
    *   0  0 |  1  0  0  0
    *   0  1 |  0  1  0  0
    *   1  0 |  0  0  1  0
    *   1  1 |  0  0  0  1
    */
   printf( "\n===== Unit test for 2-input decoder =====\n" );
   printf( "decoder( I0, I1 ) | ( O0, O1, O2, O3 )\n" );
   printf( "------------------|--------------------\n" );
   for (I0 = 0; I0 < 2; I0++) {
      for (I1 = 0; I1 < 2; I1++) {
            decoder(I0, I1, &O0, &O1, &O2, &O3);
            printf("decoder(  %d, %d  ) | (  %d,  %d,  %d,  %d )\n", I0, I1, O0, O1, O2, O3);
      }
   }


   /* Unit test for S-R latch:
    *
    *  Q( t ) | S  R | Q( t + 1 )
    * --------|------|------------
    *    0    | 0  0 |     0
    *    0    | 0  1 |     0
    *    0    | 1  0 |     1
    *    0    | 1  1 |    -1  <== undefined
    *    1    | 0  0 |     1
    *    1    | 0  1 |     0
    *    1    | 1  0 |     1
    *    1    | 1  1 |    -1  <== undefined
    */
   printf( "\n===== Unit test for sr_latch =====\n" );
   printf( " Q( t ) | S  R | sr_latch( S, R )\n" );
   printf( "--------|------|------------------\n" );
   for (S = 0; S < 2; S++) {
      for (R = 0; R < 2; R++) {
            for (Q = 0; Q < 2; Q++) {
                  printf("   %d    | %d  %d |    %d\n", Q, S, R, sr_latch(S, R, Q));
            }
      }
   }


   return EXIT_SUCCESS;
}


BIT not_gate( BIT A )
{
   if (A == FALSE) {
      return TRUE;
   } else{
      return FALSE;
   }
}


BIT or_gate( BIT A, BIT B )
{
      if (A == FALSE && B == FALSE){
            return FALSE;
      } else {
            return TRUE;
      }
}


BIT and_gate( BIT A, BIT B )
{
      return A & B;
}


BIT xor_gate( BIT A, BIT B )
{
      return A != B;
}


BIT multiplexer( BIT I0, BIT I1, BIT I2, BIT I3, BIT S0, BIT S1 )
{
      return ((I0 && !S0 && !S1) || (I1 && !S0 && S1) || (I2 && S0 && !S1) || (I3 && S0 && S1));
}


void decoder( BIT I0, BIT I1, BIT *O0, BIT *O1, BIT *O2, BIT *O3 )
{
      *O0 = !I0 && !I1;
      *O1 = !I0 && I1;
      *O2 = I0 && !I1;
      *O3 = I0 && I1;
      return;
}


/* Returns the next state of the S-R Latch */
BIT sr_latch( BIT S, BIT R, BIT Q )
{
      /* if both S and R are true then the behavior of the S-R latch
      * is undefined, so the simulation returns -1 (undefined)
      */
      if (S == TRUE && R == TRUE) return UNDEF;

      if (Q){
            if (R) {
                  return FALSE;
            } else {
                  return TRUE;
            }
      } else {
            if (S) {
                  return TRUE;
            } else {
                  return FALSE;
            }
      }
}
