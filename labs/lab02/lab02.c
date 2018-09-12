#include <stdio.h>
#include <stdlib.h>

int gcd(int x, int y) {
  int larger, smaller;
  if (x > y) {
    larger = x;
    smaller = y;
  } else {
    larger = y;
    smaller = x;
  }
  
  int remainder = larger % smaller;
  if (remainder == 0) return smaller;
  return gcd(remainder, smaller);
}

int main() {

  /************************* Checkpoint 1 *************************/
  /* Insert your four bytes of ASCII for your secret message */
  // "cute"
  int z = 0x63757465;
  /* The 0x prefix above indicates a hexadecimal number */
  
  char * c = (char*)&z;

  printf("%c", *c++);
  printf("%c", *c++);
  printf("%c", *c++);
  printf("%c\n", *c++);

  /************************* Checkpoint 2 ************************/
  int x, y;
  printf("\n****************** Checkpoint 2 *******************\n");
  printf("Enter two integers: ");
  scanf("%d", &x);
  scanf("%d", &y);
  printf("The gcd of %d and %d is %d\n", x, y, gcd(x, y)); 

  return EXIT_SUCCESS;
}
