/* Hw 4 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

void printli(int index, int num) {
    printf("li $s%d,%d\n", index, num);

    return;
}

int doesexist(char target, char *arr) {
    int i = 0;
    
    while(arr[i]) {
        if (target == arr[i]) return i;
        i++;
    }
    arr[i] = target;
    return i;
}

int isPowerOf2(int num) {
    int count = 0;
    while (num != 1) {
        if (num % 2 != 0){
            return 0;
        }
        num = num / 2;
        count++;
    }
    return count;
}

int findPowers(int x, int *powers) {
    int size = 0, temp;
    while (x > 0) {
        temp = x % 2;
        powers[size++] = temp;
        x = x / 2;
    }
    if (x == 0) {
        // Return the size of array
        return size;
    } else {
        return 0;
    }
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Invalid usage\n");
        return EXIT_FAILURE; 
    }
    // Open input file
    char const* const fileName = argv[1];
    FILE * myfile;
    myfile = fopen(fileName, "r");

    // check if the file can be opened
    if (!myfile) {
        fprintf(stderr, "Error: Cannot open file!\n");
        return EXIT_FAILURE;
    } 

    char * saved = malloc(9 * sizeof(char));
    char * equation = malloc(128 * sizeof(char));
    char line[128];

    int i, j, operationCount, numTemp1, numTemp2, isAssignment, numIndex, initial, k=0, tCount=0, labelnum=0;
    int savedIndex;
    int leftnum1, leftnum2, rightnum1, rightnum2, powernums, rightNeg, initNeg, reset=0, hastemp;
    

    while (fgets(line, sizeof(line), myfile)) {
        i = j = operationCount = numTemp1 = numTemp2 = isAssignment = numIndex = initial = hastemp = 0;
        printf("# %s", line);

        // Eliminate all spaces
        while (line[i] != '\0') {
            if (isspace(line[i])) {
                i++;
            } else {
                equation[j++] = line[i++];
            }
        }
        
        savedIndex = doesexist(equation[0], saved);
        
        i=2, j=3, k=4;

        do {
            leftnum1 = leftnum2 = rightnum1 = rightnum2 = rightNeg = initNeg = -1;
            // If equation[i] is '-'
            if (equation[i] == '-') {
                initNeg = 1;
                i++;
            }

            // If equation[i] is a digit
            if (isdigit(equation[i]) != 0) {
                leftnum1 = 0;
                leftnum2 = equation[i] - '0';
                while (isdigit(equation[i]) != 0) {
                    leftnum1 = leftnum1*10 + leftnum2;
                    i++;
                    leftnum2 = equation[i] - '0';
                }
                j = i;
                k = i + 1;
            }
            
            // If equation[k] is a minus sign
            if (equation[k] == '-') {
                rightNeg = 1;
                k++;
            }

            // If equation[k] is a digit
            if (isdigit(equation[k]) != 0) {
                rightnum1 = 0;
                rightnum2 = equation[k] - '0';
                while (isdigit(equation[k]) != 0) {
                    rightnum1 = rightnum1*10 + rightnum2;
                    k++;
                    rightnum2 = equation[k] - '0';
                }
                k--;
            }

            // If equation[i] is ';', then it comes to the end of this equation
            if (equation[j] == ';' && initial == 0) {
                // If this is negative
                if (initNeg == 1) {
                    printf("li $s%d,-%d\n", savedIndex, leftnum1);
                } 
                else {
                    printf("li $s%d,%d\n", savedIndex, leftnum1);
                }
                break;
            } 
            
            //=========================================== If addiction or subtraction ======================================
            if (equation[j] == '-' || equation[j] == '+') {
                if (equation[j] == '-'){
                    printf("sub ");
                } else if (equation[j] == '+') {
                    printf("add ");
                }
                
                // If it comes to the end of the equation
                if (equation[k+1] == ';') {
                    printf("$s%d,", savedIndex);

                    if (tCount == 10) {
                        printf("$t9,");
                        tCount = 0;
                    } else if (initial == 0) {
                        printf("$s%d,", doesexist(equation[i], saved));
                        initial++;
                    } else {
                        printf("$t%d,", tCount-1);
                    }

                    if (rightnum1 >= 0) {
                        printf("%d\n", rightnum1);
                    } else {
                        printf("$s%d\n", doesexist(equation[k], saved));
                    }
                } 
                else {
                    if (tCount == 10) {
                        printf("$t0,$t9,");
                        tCount = 1;
                    }
                    else if (initial == 0) {
                        printf("$t%d,", tCount);
                        tCount++;
                        initial++;
                        printf("$s%d,", doesexist(equation[i], saved));
                    } else {
                        printf("$t%d,$t%d,", tCount, tCount-1);
                        tCount++;
                    }
                    if (rightnum1 >= 0) {
                        printf("%d\n", rightnum1);
                    } else {
                        printf("$s%d\n", doesexist(equation[k], saved));
                    }
                    
                }
                
            }

            //================================= If multiplication ===================================
            if (equation[j] == '*') {
                if (isalpha(equation[i]) != 0 && isalpha(equation[k]) != 0) {
                    printf("mult ");
                    if (initial == 0) {
                        printf("$s%d,", doesexist(equation[i], saved));
                    } else {
                        if (tCount == 0 && reset == 1) {
                            printf("$t0,");
                            reset = 0;
                        } else {
                            printf("$t%d,", tCount);
                        }
                        if (tCount == 9)  {
                            tCount = 0;
                            reset = 1;
                        }
                        else tCount++;
                    }
                    printf("$s%d\n", doesexist(equation[k], saved));
                    
                    // If it comes to the end of the equation
                    if (equation[k+1] == ';') {
                        printf("mflo $s%d\n", doesexist(equation[0], saved));
                    } else {
                        printf("mflo $t%d\n", tCount);

                    }
                } 
                // If the left operand is an alphabet and the right one is a digit
                else if (isdigit(equation[k]) != 0 && isalpha(equation[i]) != 0) {
                    hastemp++;
                    powernums = 0;
                    int * powers = malloc(50 * sizeof(int));

                    // If the rightNum1 is 1, no need to check for powers of 2
                    if (rightnum1 == 1) {
                        printf("move $t%d,$s%d\n", tCount, doesexist(equation[i], saved));
                        // If it is negative 
                        if (rightNeg == 1) {
                            if (equation[k+1] == ';') {
                                printf("sub $s%d,$zero,$t%d\n", savedIndex, tCount);
                            } else {
                                printf("sub $t%d,$zero,$t%d\n", tCount, tCount);
                            }

                            if (tCount == 9) {
                                tCount = 0;
                                reset = 1;
                            } else {
                                tCount++;
                            }
                        }
                        // If it is not negative
                         else if (rightNeg != 1) {
                            if (equation[k+1] == ';') {
                                printf("move $s%d,$t%d\n", doesexist(equation[0], saved), tCount);
                            }
                            if (tCount == 9) {
                                tCount = 0;
                                reset = 1;
                            } else {
                                tCount++;
                            }
                        }
                    }
                    // If multiply a zero 
                    else if (rightnum1 == 0) {
                        printf("mult $t%d,$s%d\n", tCount, doesexist(equation[i], saved));
                        printf("mflo $t%d\n", tCount+1);
                        printf("li $s%d,0\n", doesexist(equation[0], saved));
                        if (tCount == 9) {
                            tCount = 0;
                            reset = 1;
                        } else {
                            tCount++;
                        }
                        break;
                    }
                    else {  
                        // Check if we can replace the right operand with powers of 2
                        powernums = findPowers(rightnum1, powers);
                    }
                    
                    if (powernums > 0) {
                        int firstShift = 0;
                        for (int a = powernums-1; a >= 0; a--) {
                            if (firstShift == 0 && powers[a] == 1) {
                                printf("sll $t%d,$s%d,%d\n", tCount, doesexist(equation[i], saved), a);
                                printf("move $t%d,$t%d\n", tCount+1, tCount);
                                firstShift++;
                            }
                            else if (a == 0 && powers[a] == 1) {
                                printf("add $t%d,$t%d,$s%d\n", tCount+1, tCount+1, doesexist(equation[i], saved));
                            } else if (powers[a] == 1) {
                                printf("sll $t%d,$s%d,%d\n", tCount, doesexist(equation[i], saved), a);
                                printf("add $t%d,$t%d,$t%d\n", tCount+1, tCount+1, tCount);
                            }
                        }
                        if (equation[k+1] == ';') {
                            if (tCount == 9) {
                                tCount = 0;
                               // reset = 1;
                            } else {
                                tCount++;
                            }
                            if (rightNeg == 1) {
                                printf("sub $s%d,$zero,$t%d\n", doesexist(equation[0], saved), tCount);
                            } else {
                                printf("move $s%d,$t%d\n", doesexist(equation[0], saved), tCount);
                            }

                            if (tCount == 8) {
                                tCount = 0;
                                reset = 1;
                            } else {
                                tCount += 2;
                            }
                        } else {
                            if (tCount == 9) {
                                tCount = 0;
                                reset = 1;
                            } else {
                                tCount += 2;;
                            }
                        }
                    }
                    // If it cannot be converted to powers of 2
                    else if (rightnum1 != 1 && powernums == 0 && rightnum1 != 0) {
                        
                        // Print li
                        printf("li $t%d,%d\n", tCount, rightnum1);
                        printf("mult $s%d,$t%d\n", doesexist(equation[i], saved), tCount);
                       // printf("mflo $t%d\n", tCount+1);
                        // If it comes to the end of the equation
                        if (equation[k+1] == ';') {
                            // If rightNum1 is negative
                            if (rightNeg == 1) {
                                printf("mflo $s%d\n", doesexist(equation[0], saved));
                                printf("sub $s%d,$zero,$s%d\n", doesexist(equation[0], saved), doesexist(equation[0], saved));
                            } else {
                                printf("mflo $s%d\n", doesexist(equation[0], saved));
                                //printf("move $s%d,$t%d\n", doesexist(equation[0]), tCount+1);
                            }
                            tCount += 2;
                        } else {
                            if (tCount == 9) {
                                tCount = 0;
                               // reset = 1;
                            } else {
                                tCount++;
                            }
                            printf("mflo $t%d\n", tCount);
                            if (tCount == 9) {
                                tCount = 0;
                                reset = 1;
                            } else {
                                tCount++;
                            }
                        }
                    }
                }

                else if (leftnum1 >= 0 && isalpha(equation[k]) != 0 && equation[k+2] != '0') {
                    hastemp++;
                    if (initial > 0) {
                        printf("mult $t%d,$s%d\n", tCount, doesexist(equation[k], saved));
                        if (equation[k+1] == ';') {
                            printf("mflo $s%d\n", savedIndex);
                        } else {
                            printf("mflo $t%d\n", tCount);
                            
                        }
                        if (tCount == 9) {
                            tCount = 0;
                            reset = 1;
                        } else {
                            tCount++;
                        }
                    }
                    else if (initial == 0 && leftnum1 != 0) {
                        printf("li $t%d,%d\n", tCount, leftnum1);
                        printf("mult $t%d,$s%d\n", tCount, doesexist(equation[k], saved));
                        if (equation[k+1] == ';') {
                            printf("mflo $s%d\n", savedIndex);
                        } else {
                            printf("mflo $t%d\n", tCount);
                            
                        }
                        if (tCount == 9) {
                            tCount = 0;
                            reset = 1;
                        } else {
                            tCount++;
                        }
                    }
                }

                else if (leftnum1 >= 0 && rightnum1 >= 0) {
                    hastemp++;
                    if ((leftnum1 == 0 && initial == 0) || rightnum1 == 0) {
                        printf("li $s%d,0\n", savedIndex);
                        if (initial > 0) {
                            if (tCount == 9) {
                                tCount = 0;
                                reset = 1;
                            } else {
                                tCount++;
                            }
                        }
                        break;
                    }

                    if (initial == 0) {
                        printf("li $t%d,%d\n", tCount, leftnum1);
                        if (tCount == 9) {
                            tCount = 0;
                            reset = 1;
                        } else {
                            tCount++;
                        }
                    } 
                    
                    if (rightnum1 == 1) {
                        if (tCount == 9) {
                            tCount = 0;
                            reset = 1;
                        } else {
                            tCount++;
                        }
                        if (rightNeg == 1) {
                            if (reset == 1) {
                                printf("sub $t0,$zero,$t9\n");
                                reset = 0;
                            } else {
                                printf("sub $t%d,$zero,$t%d\n", tCount, tCount-1);
                            } 
                        }
                        else {
                            if (reset == 1) {
                                printf("move $t0,$t9\n");
                                reset = 0;
                            } else {
                                printf("move $t%d,$t%d\n", tCount, tCount-1);
                            }
                        }
                    } else {
                        if (rightNeg == 1) {
                            printf("li $t%d,-%d\n", tCount, rightnum1);
                        } else {
                            printf("li $t%d,%d\n", tCount, rightnum1);
                        } 

                        if (reset == 1) {
                            printf("mult $t9,$t0\n");
                            reset = 0;
                        } else {
                            printf("mult $t%d,$t%d\n", tCount-1, tCount);
                        }
                    
                        printf("mflo $t%d\n", tCount+1);
                        if (tCount == 9) {
                            tCount = 0;
                            reset = 1;
                        } else {
                            tCount++;
                        } 
                    }
                    
                }
                initial++;
            } 

            //======================================= If division ============================================== 
            if (equation[j] == '/') {

                // If both operands are alphabets
                if (isalpha(equation[i]) != 0 && isalpha(equation[k]) != 0) {
                    printf("div ");
                    if (initial == 0) {
                        printf("$s%d,", doesexist(equation[i], saved));
                    } else {
                        printf("$t%d,", tCount);
                        if (tCount == 9) {
                            tCount = 0;
                            reset = 1;
                        } else {
                            tCount++;
                        }
                    }
                    printf("$s%d\n", doesexist(equation[k], saved));

                    // If it comes to the end of the equation
                    if (equation[k+1] == ';') {
                        printf("mflo $s%d\n", doesexist(equation[0], saved));
                    } else {
                        if (reset == 1) reset = 0;
                        printf("mflo $t%d\n", tCount);
                    }
                }

                // If the right operand is a digit and the left is an alphabet
                if (isalpha(equation[i]) != 0 && isdigit(equation[k]) != 0) {
                    hastemp++;
                    int ispower;

                    // If the right operand is 0, then print an error message
                    if (rightnum1 == 0) {
                        fprintf(stderr, "Division by zero error\n");
                    } 
                    else if(rightnum1 == 1) {
                        if (equation[k+1] == ';') {
                            if (rightNeg == 1) {
                                printf("sub $s%d,$zero,", doesexist(equation[0], saved));
                                if (initial == 0) {
                                    printf("$s%d\n", doesexist(equation[i], saved));
                                } else {
                                    printf("$t%d\n", tCount);
                                    tCount++;
                                }
                            }
                            else {
                                printf("move $s%d,", doesexist(equation[0], saved));
                                if (initial == 0) {
                                    printf("$s%d\n", doesexist(equation[i], saved));
                                } else {
                                    printf("$t%d\n", tCount);
                                    tCount++;
                                }
                            }
                        }
                        else {
                            if(rightNeg == 1) {
                                printf("sub $t%d,$zero,$s%d\n", tCount, doesexist(equation[i], saved));
                            }
                            else {
                                printf("move $t%d,", tCount);
                                if (initial == 0) {
                                    printf("$s%d\n", doesexist(equation[i], saved));
                                } else {
                                    printf("$t%d\n", tCount);
                                    if (tCount == 9) {
                                        tCount = 0;
                                        reset = 1;
                                    } else {
                                        tCount++;
                                    }
                                }
                            }
                        }
                    } else {
                        ispower = isPowerOf2(rightnum1);
                    }

                    if (ispower > 0 && rightnum1 > 1) {
                        hastemp++;
                        if (labelnum > 0) labelnum++;
                        if (initial == 0) {
                            printf("bltz $s%d,L%d\n", doesexist(equation[i], saved), labelnum);
                        }
                        else {
                            if (reset == 1) reset = 0;
                            printf("bltz $t%d,L%d\n", tCount, labelnum);
                        }
                        
                        printf("srl $s%d,", doesexist(equation[0], saved));

                        if (initial == 0) {
                            printf("$s%d,", doesexist(equation[i], saved));
                        } else {
                            printf("$t%d,", tCount);
                        }
                        
                        printf("%d\n", ispower);

                        if (rightNeg == 1) {
                            printf("sub $s%d,$zero,$s%d\n", doesexist(equation[0], saved), doesexist(equation[0], saved));
                        }
                        printf("j L%d\n", labelnum+1);
                        printf("L%d:\n", labelnum);
                        if (rightNeg == 1) {
                            if (initial == 0) {
                                if (reset == 1) reset = 0;
                                printf("li $t%d,-%d\n", tCount, rightnum1);
                            } else {
                                
                                if (tCount == 9) {
                                    tCount = 0;
                                    reset = 1;
                                } else {
                                    tCount++;
                                }
                                printf("li $t%d,-%d\n", tCount, rightnum1);
                            }
                            
                        } else {
                            if (initial == 0) {
                                if (reset == 1) {
                                    printf("li $t9,%d\n", rightnum1);
                                } else {
                                    printf("li $t%d,%d\n", tCount, rightnum1);
                                }
                            } else {
                                
                                if (tCount == 9) {
                                    tCount = 0;
                                    reset = 1;
                                } else {
                                    tCount++;
                                }
                                printf("li $t%d,%d\n", tCount, rightnum1);
                            }
                        }
                        
                        if (initial == 0) {
                            printf("div $s%d,$t%d\n", doesexist(equation[i], saved), tCount);
                        } else {
                            if (reset == 1) {
                                printf("div $t0,$t9\n");
                                reset = 0;
                            } else {
                                printf("div $t%d,$t%d\n", tCount-1, tCount);
                            }
                        }
                        
                        printf("mflo $s%d\n", doesexist(equation[0], saved));
                        printf("L%d:\n", labelnum+1);
                        labelnum++;
                        tCount++;
                    } 

                    else if (ispower == 0 && rightnum1 > 0) {

                        if (rightNeg == 1) {
                            printf("li $t%d,-%d\n", tCount, rightnum1);
                        } else {
                            printf("li $t%d,%d\n", tCount, rightnum1);
                        }

                        if (initial == 0 && hastemp > 0) {
                            printf("div $s%d,$t%d\n", doesexist(equation[i], saved), tCount);
                        } else {
                            if (reset == 1) {
                                printf("div $t0,$t9\n");
                                reset = 0;
                            } else {
                                printf("div $t%d,$t%d\n", tCount-1, tCount);
                            }
                        }
                        

                        // If it comes to the end of the equation
                        if (equation[k+1] == ';') {
                            printf("mflo $s%d\n", doesexist(equation[0], saved));
                        } else {
                            if (tCount == 9) {
                                printf("mflo $t0\n");
                            } else {
                                printf("mflo $t%d\n", tCount+1);
                            }
                            if (tCount == 9) {
                                tCount = 0;
                            } else {
                                tCount++;
                            }
                        }
                        
                    }
                }

                else if (leftnum1 >= 0 && isalpha(equation[k]) != 0){
                    hastemp++;
                    if (initial > 0) {
                        printf("div $t%d,$s%d\n", tCount, doesexist(equation[k], saved));
                        if (equation[k+1] == ';') {
                            printf("mflo $s%d\n", savedIndex);
                        } else {
                            
                            if (tCount == 9) {
                                tCount = 0;
                                reset = 1;
                            } else {
                                tCount++;
                            }
                            printf("mflo $t%d\n", tCount);
                        }
                        
                    }
                }

                else if (leftnum1 >= 0 && rightnum1 >= 0) {
                    hastemp++;
                    if (rightnum1 == 0) {
                        fprintf(stderr, "Division by zero error\n");
                    }
                    else if (rightnum1 == 1) {
                        if (initial == 0) {
                            printf("li $t%d,%d\n", tCount, leftnum1);
                        }

                        if (equation[k+1] == ';') {
                            if (rightNeg == 1) {
                                printf("sub $s%d,$zero,", doesexist(equation[0], saved));
                                printf("$t%d\n", tCount);
                            }
                            else {
                                printf("move $s%d,", doesexist(equation[0], saved));
                                printf("$t%d\n", tCount);
                            }

                            if (tCount == 9) {
                                tCount = 0;
                                reset = 1;
                            } else {
                                tCount++;
                            }
                        }
                        else {
                            if(rightNeg == 1) {
                                if (tCount + 1 == 9) {
                                    tCount = 0;
                                    reset = 1;
                                } else {
                                    tCount++;
                                }

                                if (reset == 1) {
                                    printf("sub $t0,$zero,$t9\n");
                                    reset = 0;
                                } else {
                                    printf("sub $t%d,$zero,$t%d\n", tCount, tCount-1);
                                }
                            }
                            else {
                                if (tCount + 1 == 9) {
                                    tCount = 0;
                                    reset = 1;
                                } else {
                                    tCount++;
                                }

                                if (reset == 1) {
                                    printf("move $t0,$t9\n");
                                    reset = 0;
                                } else {
                                    printf("move $t%d,", tCount);
                                    printf("$t%d\n", tCount-1);
                                }
                            }
                        }
                    }
                    else {
                        int ispower = isPowerOf2(rightnum1);
                        if (initial == 0) {
                            printf("li $t%d,%d\n", tCount, leftnum1);
                        }

                        if (ispower > 0 && rightnum1 > 1) {
                            if (labelnum > 0) labelnum++;
                            printf("bltz $t%d,L%d\n", tCount, labelnum);
                            printf("srl $s%d,$t%d,", doesexist(equation[0], saved), tCount);
                        
                            printf("%d\n", ispower);

                            if (rightNeg == 1) {
                                printf("sub $s%d,$zero,$s%d\n", doesexist(equation[0], saved), doesexist(equation[0], saved));
                            }
                            printf("j L%d\n", labelnum+1);
                            printf("L%d:\n", labelnum);
                            
                            if (tCount == 9) {
                                tCount = 0;
                                reset = 1;
                            } else {
                                tCount++;
                            }

                            if (rightNeg == 1) {
                                printf("li $t%d,-%d\n", tCount, rightnum1);
                            } else {
                                printf("li $t%d,%d\n", tCount, rightnum1);
                            }

                            if (reset == 1) {
                                printf("div $t9,$t0\n");
                            } else {
                                printf("div $t%d,$t%d\n", tCount-1, tCount);
                            }
                            
                            printf("mflo $s%d\n", doesexist(equation[0], saved));
                            printf("L%d:\n", labelnum+1);
                            labelnum++;
                            tCount++;
                        } 
                        else if (ispower == 0 && rightnum1 > 0) {
                            if (tCount == 9) {
                                tCount = 0;
                                reset = 1;
                            } else {
                                tCount++;
                            }

                            if (rightNeg == 1) {
                                printf("li $t%d,-%d\n", tCount, rightnum1);
                            } else {
                                printf("li $t%d,%d\n", tCount, rightnum1);
                            }

                            if (reset == 1) {
                                printf("div $t9,$t0\n");
                            } else {
                                printf("div $t%d,$t%d\n", tCount-1, tCount);
                            }
                            
                            // If it comes to the end of the equation
                            if (equation[k+1] == ';') {
                                printf("mflo $s%d\n", doesexist(equation[0], saved));
                                if (tCount == 9) tCount = 0;
                                else tCount++;
                            } else {
                                if (tCount == 9) tCount = 0;
                                else tCount++;
                                printf("mflo $t%d\n", tCount);
                            }
                        
                        }
                    }
                }

                initial++;
            }

            //===================================== If mod ========================================
            if (equation[j] == '%') {
                if (isalpha(equation[i]) != 0 && isalpha(equation[k]) != 0) {
                    printf("div ");
                    if (initial == 0) {
                        printf("$s%d,$s%d\n", doesexist(equation[i], saved), doesexist(equation[k], saved));
                    } else {
                        printf("$t%d,$s%d\n", tCount, doesexist(equation[k], saved));
                    }
                    if (equation[k+1] == ';') {
                        printf("mfhi $s%d\n", doesexist(equation[0], saved));
                        if (initial > 0) {
                            if (tCount == 9) {
                                tCount = 0;
                                reset = 1;
                            } else {
                                tCount++;
                            }
                        }
                    } else {
                        if (tCount == 9) {
                            tCount = 0;
                            //reset = 1;
                        } else {
                            tCount++;
                        }
                        printf("mfhi $t%d\n", tCount);
                        
                    }
                    
                }

                else if (isalpha(equation[i]) != 0 && isdigit(equation[k]) != 0) {
                    hastemp++;
                    if (rightnum1 == 1) {
                        if (equation[k+1] == ';') {
                            if (rightNeg == 1) {
                                printf("sub $s%d,$zero,", doesexist(equation[0], saved));
                                if (initial == 0) {
                                    printf("$s%d\n", doesexist(equation[i], saved));
                                } else {
                                    printf("$t%d\n", tCount);
                                    if (tCount == 9) {
                                        tCount = 0;
                                        reset = 1;
                                    } else {
                                        tCount++;
                                    }
                                }
                            }
                            else {
                                printf("move $s%d,", doesexist(equation[0], saved));
                                if (initial == 0) {
                                    printf("$s%d\n", doesexist(equation[i], saved));
                                } else {
                                    printf("$t%d\n", tCount);
                                    if (tCount == 9) {
                                        tCount = 0;
                                        //reset = 1;
                                    } else {
                                        tCount++;
                                    }
                                }
                            }
                        }
                        else {
                            if(rightNeg == 1) {
                                printf("sub $t%d,$zero,$s%d\n", tCount, doesexist(equation[i], saved));
                            }
                            else {
                                printf("move $t%d,", tCount);
                                if (initial == 0) {
                                    printf("$s%d\n", doesexist(equation[i], saved));
                                } else {
                                    printf("$t%d\n", tCount);
                                    if (tCount == 9) {
                                        tCount = 0;
                                        //reset = 1;
                                    } else {
                                        tCount++;
                                    }
                                }
                            }
                        }
                    } else if (rightnum1 == 0) {
                        fprintf(stderr, "Division by zero error\n");
                    } else {
                        if (rightNeg == 1) {
                            printf("li $t%d,-%d\n", tCount, rightnum1);
                        } else {
                            printf("li $t%d,%d\n", tCount, rightnum1);
                        }
                        printf("div ");

                        if (initial == 0) {
                            printf("$s%d,", doesexist(equation[i], saved));
                        } else {
                            if (reset == 1) {
                                printf("$t9,");
                                reset = 0;
                            } else {
                                printf("$t%d,", tCount-1);
                            }
                        
                        }
                        printf("$t%d\n", tCount);

                        if (equation[k+1] == ';') {
                            printf("mfhi $s%d\n", savedIndex);
                        } else {
                            printf("mfhi $t%d\n", tCount+1);
                        }
                        if (tCount == 9) {
                            tCount = 0;
                            //reset = 1;
                        } else {
                            tCount++;
                        }
                    }
                    
                }

                else if (leftnum1 >= 0 && isalpha(equation[k]) != 0) {
                    hastemp++;
                    if (initial > 0) {
                        printf("div $t%d,$s%d\n", tCount, doesexist(equation[k], saved));
                        if (equation[k+1] == ';') {
                            printf("mfhi $s%d\n", savedIndex);
                        } else {
                            
                            if (tCount == 9) {
                                tCount = 0;
                                reset = 1;
                            } else {
                                tCount++;
                            }
                            printf("mfhi $t%d\n", tCount);
                        }
                        
                    }
                }

                else if (leftnum1 >= 0 && rightnum1 >= 0) {
                    hastemp++;
                    if (initial > 0) {
                        if (tCount == 9) {
                            tCount = 0;
                            reset = 1;
                        } else {
                            tCount++;
                        }

                        if (rightNeg == 1) {
                            printf("li $t%d,-%d\n", tCount, rightnum1);
                        } else {
                            printf("li $t%d,%d\n", tCount, rightnum1);
                        }

                        printf("div ");

                        if (reset == 1) {
                            printf("$t9,");
                            reset = 0;
                        } else {
                            printf("$t%d,", tCount-1);
                        }
                        printf("$t%d\n", tCount);

                        if (equation[k+1] == ';') {
                            printf("mfhi $s%d\n", savedIndex);                            
                        } else {
                            if (tCount == 9) {
                                tCount = 0;
                                reset = 1;
                            } else {
                                tCount++;
                            }
                            printf("mfhi $t%d\n", tCount);                            
                        }

                        

                    } else {
                        printf("li $t%d,%d", tCount, leftnum1);
                        if (tCount == 9) {
                            tCount = 0;
                            reset = 1;
                        } else {
                            tCount++;
                        }

                        if (rightNeg == 1) {
                            printf("li $t%d,-%d\n", tCount, rightnum1);
                        } else {
                            printf("li $t%d,%d\n", tCount, rightnum1);
                        }

                        printf("div ");

                        if (reset == 1) {
                            printf("$t9,");
                            reset = 0;
                        } else {
                            printf("$t%d,", tCount - 1);
                        }
                        printf("$t%d\n", tCount);

                        if (equation[k+1] == ';') {
                            printf("mfhi $s%d\n", savedIndex);
                            tCount++;
                        } else {
                            printf("mfhi $t%d\n", tCount+1);
                            tCount++;
                        }
                    }
                }

                initial++;
            }

            i = k;
            j = i + 1;
            k = j + 1;
            initial++;
            
        } while (equation[j] != ';' || equation[j] == '\0');
        
    }

    fclose(myfile);

    free(saved);
    free(equation);

    return EXIT_SUCCESS;
}