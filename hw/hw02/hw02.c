/* HW 2 */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int doesexist(int len, char target, char *arr) {
  int i;
  for (i = 0; i < len; i++) {
    if (target == arr[i]) return 1;
  }

  return 0;
}


int main() {
  char * equation = malloc(128 * sizeof(char));
  char * operation = malloc(4 * sizeof(char));
  char * saved = malloc(8 * sizeof(char));
  char c;
  int * num = malloc(128 * sizeof(int));
  int i, j, k, reset, numCount, numTemp, tCount, index, temp, s=0;

  printf("Please enter a valid C assignment statement:\n");

  // ************************ Parsing the input equation ******************************
  i = j = k = reset = numCount = numTemp = 0;
  do {
      // Get the new read-in character
      c = getchar();
      
      if (isspace(c)) continue;

      // If c is a letter
      if (isalpha(c) != 0) {
          // ERROR CHECKING: if the previous character is not an operation sign, then print an error message
          if (isalpha(equation[i-1]) != 0 || isdigit(equation[i-1]) != 0) {
              fprintf(stderr, "Invalid Input 1!\n");
              return EXIT_FAILURE;
          }

          // Check if the letter has appeared previously 
          if (doesexist(k, c, saved) == 0) {
              saved[k] = c;
              k++;
          }

          equation[i] = c;
          i++;
      }
      // If c is a digit
      else if (isdigit(c) != 0) {
          temp = c - '0';
          numTemp = numTemp*10 + temp;
      }
      // If c is an operation sign 
      else if (c == '=' || c == '+' || c == '-' || c == ';') {
          // If numTemp is not zero, that means the previous input is an integer
          if (numTemp != 0) {
              num[numCount] = numTemp;
              equation[i] = numCount + '0';
              numTemp = 0;
              numCount++;
              i++;
          }

          // ERROR CHECKING: if the previous character is also an operation sign, then print an error message
          if (equation[i-1] == '+' || equation[i-1] == '-' || equation[i-1] == '=') {
              fprintf(stderr, "Invalid Input 2!\n");
              return EXIT_FAILURE;
          }

          equation[i] = c;
          i++;
      }
  } while (c != ';');

  
  printf("The MIPS pseudocode is:\n");

  // ******************************* Printing MIPS pseudocode ******************************

  i = 2;
  k = 3;
  j = 4;
  int lineCount = tCount = 0;
  while (equation[j] != '\0') {
    // Print the operation
    if (equation[k] == '-') operation = "sub";
    else if (equation[k] == '+') operation = "add";
    printf("%s ", operation);

    // Print and store the temporary variable
    if (equation[j+1] != ';') {
        // If tCount is 9, we need to reset the registry
        if (tCount == 10) {
            printf("$t0,$t9,");
            tCount = 1;
            reset++;
        }
        else if (lineCount == 0) {
            printf("$t%d,", tCount);
            tCount++;
        } else {
            printf("$t%d,$t%d,", tCount, tCount-1);
            tCount++;
        }
    } else {
        if (lineCount > 0) printf("$s0,$t%d,", tCount-1);
        else printf("$s0,");
    }
    
    // If lineCount is 0, that means there is no previous temporary variable
    if (lineCount == 0) {
        // If equation[i] is a digit 
        if (isdigit(equation[i]) != 0) {
            index = equation[i] - '0';
            printf("%d,", num[index]);
        }
        // equation[i] is not a digit
        else {
            s = 0;
            while (saved[s] != equation[i]) s++;
            printf("$s%d,", s);
        }
    } 

    // If equation[j] is a number
    if (isdigit(equation[j]) != 0) {
        // If the index has more than one digit 
        index = equation[j] - '0';
        while (isdigit(equation[j+1]) != 0) {
            temp = equation[j+1] - '0';
            index = index*10 + temp;
            j++;
        }
        printf("%d\n", num[index]);
    } else {
      s = 0;
      while (saved[s] != equation[j]) s++;
      printf("$s%d\n", s);
    }

    k += 2;
    j += 2;
    lineCount++;
  }
  
  //free(operation);
  free(equation);
  free(num);
  free(saved);
  
  return EXIT_SUCCESS;
}