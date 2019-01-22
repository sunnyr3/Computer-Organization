#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
  FILE * myfile;
  char arr[128];
  char *p, *q;

  myfile = fopen("book-1984.txt", "r");
  if (!myfile) {
    fprintf(stderr, "Error: Cannot open file!\n");
    return EXIT_FAILURE;
  }  

  while (fgets(arr, 128, myfile)) {
    if (isalnum(arr[0])) {
      for (p = arr, q = arr; *p != '\0'; p++) {
        if (isalnum(*p)) { 
          printf("%c", *p);
        } else {
          q++;
        }
      }
    printf(" [%ld alnum chars]\n", p-q); 
    }
  }

  fclose(myfile);

  return EXIT_SUCCESS;
}
