/* hw01.c */
/* NAME: Jiaqing Ruan */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[]) {
  if (argc != 5) {
    printf("ERROR: Invalid inputs!\n");
    return EXIT_FAILURE;
  }
  
  int numRow1 = atoi(argv[1]), numCol1 = atoi(argv[2]),
      numRow2 = atoi(argv[3]), numCol2 = atoi(argv[4]);
  
  // If any of these numbers is less than one, then return failure
  // OR, if numCol1 is not equal to numRow2, then two matrices cannot multiply and return failure
  if (numRow1<1 || numCol1<1 || numRow2<1 || numCol2<1 || numCol1 != numRow2) {
    printf("ERROR: Invalid inputs!\n");
    return EXIT_FAILURE;
  }

  int i, j, k;
  int maxLen1[numCol1];  /* Stores the maximum lenth of values in each column */
  int maxLen2[numCol2]; 
  
  // Initialize these two integer arrays
  for (i = 0; i < numCol1; i++) maxLen1[i] = 0;
  for (i = 0; i < numCol2; i++) maxLen2[i] = 0;

  /*********** Read in integers for the first matrix ***********/
  int matrix1[numRow1][numCol1];
  printf("Please enter the values for the first matrix (%dx%d) :\n", numRow1, numCol1);
  for (i = 0; i < numRow1; i++) {
    for (j = 0; j < numCol1; j++) {
      scanf("%d", &(matrix1[i][j]));
      
      int templength = floor(log10(abs(matrix1[i][j]))) + 1;
      if (templength > maxLen1[j]) {
        maxLen1[j] = templength;
      }
    }
  }

  /*********** Read in integers for the second matrix **********/
  int matrix2[numRow2][numCol2];
  printf("Please enter the values for the second matrix (%dx%d) :\n", numRow2, numCol2);
  for (i = 0; i < numRow2; i++) {
    for (j = 0; j < numCol2; j++) {
      scanf("%d", &(matrix2[i][j]));

      int templength = floor(log10(abs(matrix2[i][j]))) + 1;
      if (templength > maxLen2[j]) {
        maxLen2[j] = templength;
      }
    }
  }

  printf("\n");

  /************ Calculate the new matrix ************/
  int newMatrix[numRow1][numCol2];
  int maxLen3[numCol2];
  // Initialize the array
  for (i = 0; i < numCol2; i++) maxLen3[i] = 0;
  
  for (i = 0; i < numRow1; i++) {
    for (j = 0; j < numCol2; j++) {
      newMatrix[i][j] = 0;
      for (k = 0; k < numCol1; k++) {
        newMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
      }
      // Get the number of digits of this value
      int tempLength = floor(log10(abs(newMatrix[i][j]))) + 1;
      if (tempLength > maxLen3[j]) maxLen3[j] = tempLength;
    }
  }

  /************ Print out the first matrix ************/
  for (i = 0; i < numRow1; i++) {
    printf("[");
    for (j = 0; j < numCol1; j++) {
      printf("%*d", maxLen1[j], matrix1[i][j]);
      if (j != numCol1 - 1) printf(" ");
    }
    printf("]\n");
  }

  printf("multiplied by\n");

  /************* Print out the second matrix *************/
  for (i = 0; i < numRow2; i++) {
    printf("[");
    for (j = 0; j < numCol2; j++) {
      printf("%*d", maxLen2[j], matrix2[i][j]);
      if (j != numCol2 - 1) printf(" ");
    }
    printf("]\n");
  }

  printf("equals\n");

  /************* Print out the new matrix ***********/
  for (i = 0; i < numRow1; i++) {
    printf("[");
    for (j = 0; j < numCol2; j++) {
      printf("%*d", maxLen3[j], newMatrix[i][j]);
      if (j != numCol2 - 1) printf(" ");
    }
    printf("]\n");
  }

  return EXIT_SUCCESS;
}
