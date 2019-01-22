#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void draw_triangle(int n) {
  char * left, * right;
  char * line = malloc(n+1);
  memset(line, ' ', n);
  line[n] = '\0';

  /* e.g., n is 7, then line is: "       \0" */
  
  left = right = line + n/2;
  *left = '*';
  printf("%s\n", line);

  while (left != line) {
    left--;
    right++;
    *left = '*';
    *right = '*';
    printf("%s\n", line);
  }

  free(line);
}

int main() {
  int n;
  printf("What is n? ");
  scanf("%d", &n);
 
  if (n<=0 || n%2 == 0) {
    fprintf(stderr, "Error: ");
    return EXIT_FAILURE;
  }

  draw_trianle(n);

  return EXIT_SUCCESS;
}
