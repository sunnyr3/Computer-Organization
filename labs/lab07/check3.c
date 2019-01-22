/* adder.c */

#include <stdio.h>
#include <stdlib.h>

/* Use inputs d0, d1, and carry_in to compute both the sum
 * (which is returned) and the carry_out (passed by reference)
 *
 * Note that carry_out could be NULL, indicating that we do
 * not want to determine carry_out (i.e., only return the sum)
 */
int add_two_bits(int d0, int d1, int carry_in, int *carry_out)
{
  int s = (d0 ^ d1) ^ carry_in;
  int cout = ((d0 ^ d1) & carry_in) | (d0 & d1);
  if (carry_out){
    *carry_out = cout;
  }
  return s;
}

int main()
{
  int i;
  int d0[4];
  int d1[4];
  int ci[5];
  int sum[5];

  for (i = 0; i < 4; i++) {
    printf("Enter binary digit A%d: ", i);
    scanf("%d", &d0[i]);
    /* Clean the user-generated input */
    d0[i] = !!d0[i];
  }

  for (i = 0; i < 4; i++) {
    printf( "Enter binary digit B%d: ", i);
    scanf( "%d", &d1[i] );
    /* Clean the user-generated input */
    d1[i] = !!d1[i];
  }

  ci[0] = 0;
  for (i = 0; i < 4; i++) {
    sum[i] = add_two_bits(d0[i], d1[i], ci[i], &ci[i+1]);
  }

  sum[4] = ci[4];

  for(i = 3; i >= 0; i--)
        printf("%d", d0[i]);
    printf(" + ");
    for(i = 3; i >= 0; i--)
        printf("%d", d1[i]);
    printf(" = ");
    for(i = 4; i >= 0; i--)
        printf("%d", sum[i]);
    printf("\n");

  return EXIT_SUCCESS;
}