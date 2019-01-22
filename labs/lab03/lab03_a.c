#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE * myfile;
  myfile = fopen("lab03-data.dat", "r");
  // check if file can be opened
  if (!myfile) return -1;

  // get the size of the file
  fseek(myfile, 0, SEEK_END);
  long fsize = ftell(myfile);
  rewind(myfile);

  int * nums;
  nums = (int *)calloc(fsize+1, sizeof(int));
  
  // copy the file into nums
  size_t result = fread(nums, sizeof(int), fsize, myfile);
  
  int i;
  for (i = 0; i < result; i++) {
    printf("Data point # %3d: %d\n", i, nums[i]);
  }

  fclose(myfile);
  free(nums);

  return 0;

}
