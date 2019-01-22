#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE * myfile;
  myfile = fopen("lab03-data.dat", "r");
  // check if the file can be opened
  if (!myfile) {
    fprintf(stderr, "Error: Cannot open file!\n");
    return EXIT_FAILURE;
  }  

  // get the file size
  fseek(myfile, 0, SEEK_END);
  long fsize = ftell(myfile);
  rewind(myfile);

  unsigned long * nums;
  nums = (unsigned long *)calloc(fsize+1, sizeof(unsigned long));

  // copy the file into nums
  size_t result = fread(nums, sizeof(unsigned long), fsize, myfile);

  int i;
  for (i = 0; i < result; i++) {
    printf("Data point # %3d: %lu\n", i, nums[i]);
  }

  fclose(myfile);
  free(nums);
 
  return 0;
}
