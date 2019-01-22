#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
  int rc;  //return code
  int i = 10, j = 12, k = 15;
  double gpa = 3.97;
  
  FILE * file = fopen("xyz.txt", "w");
  
  if (file == NULL) {
   // fprintf(stderr, "fopen() failed\n");
    perror("fopen() failed");
    return EXIT_FAILURE;
  }

  rc = fprintf(file, "%04d_%04d_%04d_%10.21f\n", i, j, k, gpa);
  printf("fprintf() wrote %d bytes to the file. \n", rc);

  fclose(file);

  return EXIT_SUCCESS;
}
