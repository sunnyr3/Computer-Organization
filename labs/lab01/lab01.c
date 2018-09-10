// Lab 01
// 09/04/2018 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long fib_recursive(int n) {
  if (n == 0 || n == 1) return 1;
  long ret =  fib_recursive(n-1) + fib_recursive(n-2);
  return ret;
}

long fib_bottom_up(int n) {
   if (n == 0 || n == 1) return 1;
   long bottom_up[n+1];
   bottom_up[0] = bottom_up[1] = 1;
   int i;
   for (i = 2; i <= n; i++) {
     bottom_up[i] = bottom_up[i-1] + bottom_up[i-2];
   }
   return bottom_up[n];
} 

int main() {
  // ============== Checkpoint 1 =================
  int n, height = 0;
  printf("What is n? ");
  scanf("%d", &n);
 
  int i;
  for(i = 1; i <= n; i += 2) {
    // Print the space
    int numSpace = (n-i) / 2 + 1;
    printf("%*c", numSpace, ' ');
    // Print *
   // printf("%*c", i, '*');
    printf("%.*s", i, "*******************************************");
    height++;
    printf("\n");
  }
  // Print the area of the triangle
  float area = (float)n * height / 2;
  printf("The area of this triangle is %.2f\n", area);

  //====================================================
  // ============= Checkpoit 2 - Fibonacci =============
  //====================================================
  printf("Fibonacci - What is n? ");
  scanf("%d", &n);

  long result;
  //result = fib_recursive(n);
  result = fib_bottom_up(n);
  printf("Its Fibonacci number is %ld. \n", result);

  return 0;
}
