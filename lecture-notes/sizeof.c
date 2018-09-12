#include <stdio.h>
#include <stdlib.h>

int main() {
  /* A pointer, regardless what it is point to, its size is always 8 bytes. */

  char c = 'c';
  int x = 13;
  
  printf("sizeof char is %lu\n", sizeof(char)); // size of a char is 1 byte

  printf("size of char * %lu\n", sizeof(char *));  // size of a pointer is always 8 bytes

  // Print out the address
  printf("address of char c is %p\n', &c);
  
  return EXIT_SUCCESS;
}
