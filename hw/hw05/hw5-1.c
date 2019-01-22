/* HW 5 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void headline() {
    printf("CPU Cycles ===>\t1\t2\t3\t4\t5\t6\t7\t8\t9\n");
    return;
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

    char prevreg[5][2], curreg1[5][2], curreg2[5][2];
    char mips[5][128];
    int linecount = 0, i, regcount, cyclecount=1, index, k, lwnum=-1;
    int isnop1[5], isnop2[5], hasnop[5], original[5];

    // Initialize isnop array
    for (i = 0; i < 5; i++) {
        isnop1[i] = -1;
        isnop2[i] = -1;
        hasnop[i] = -1;
        original[i] = -1;
    }

    // Parse pipelines
    while (fgets(mips[linecount], sizeof(mips[linecount]), myfile)) {
        i = 0;
        regcount = 0;

        while (mips[linecount][i] != '\n') {
            if (mips[linecount][i] == '$') {
                // If the first register of this line
                if (regcount == 0) {
                    prevreg[linecount][0] = mips[linecount][i+1];
                    prevreg[linecount][1] = mips[linecount][i+2];
                    if (mips[linecount][0] == 's' && mips[linecount][1] == 'w') {
                        
                        for (index = 0; index < linecount; index++) {
                            if (prevreg[linecount][0] == curreg1[index][0] && prevreg[linecount][1] == curreg1[index][1]) {
                                lwnum = index;
                                break;
                            }
                            else if (prevreg[linecount][0] == curreg2[index][0] && prevreg[linecount][1] == curreg2[index][1]) {
                                lwnum = index;
                                break;
                            }
                        }
                        
                    }
                } 
                // If the second register of this line
                else if (regcount == 1) {
                    curreg1[linecount][0] = mips[linecount][i+1];
                    curreg1[linecount][1] = mips[linecount][i+2];
                    // Find if there is any dependencies 
                    if (linecount > 0) {
                        for (index = 0; index < linecount; index++) {
                            if (prevreg[index][0] == curreg1[linecount][0] && prevreg[index][1] == curreg1[linecount][1]) {
                                isnop1[linecount] = index;
                                break;
                            }
                        }
                    }
                }
                // If the third register of this line
                else if (regcount == 2) {
                    curreg2[linecount][0] = mips[linecount][i+1];
                    curreg2[linecount][1] = mips[linecount][i+2];
                    // Find if there is any dependencies 
                    if (linecount > 0) {
                        for (index = 0; index < linecount; index++) {
                            if (prevreg[index][0] == curreg2[linecount][0] && prevreg[index][1] == curreg2[linecount][1]) {
                                isnop2[linecount] = index;
                                break;
                            }
                        }
                    }
                }
                i += 2;
                regcount++;
            }
            i++;
        }
        mips[linecount][i] = '\t';
        linecount++;
    }


    // Start simulation
    printf("START OF SIMULATION\n\n");

    while (cyclecount < 10) {
        if (cyclecount == linecount+5) break;
        headline();
        i = 0;
        
        while (i < linecount) {

            // If cyclecount is 1
            if (cyclecount == 1) {
                printf("%s", mips[i]);
                // If first line
                if (i == 0) {
                    printf("IF\t.\t.\t.\t.\t.\t.\t.\t.\n");
                } 
                else {
                    printf(".\t.\t.\t.\t.\t.\t.\t.\t.\n");
                }
            }

            // If cyclecount is 2
            else if (cyclecount == 2) {
                printf("%s", mips[i]);
                // If first line
                if (i == 0) {
                    printf("IF\tID\t.\t.\t.\t.\t.\t.\t.\n");
                }
                else if (i == 1) {
                    printf(".\tIF\t.\t.\t.\t.\t.\t.\t.\n");
                } 
                else {
                    printf(".\t.\t.\t.\t.\t.\t.\t.\t.\n");
                }
            }

            // If cyclecount is 3
            else if (cyclecount == 3) {
                printf("%s", mips[i]);
                // If first line
                if (i == 0) {
                    printf("IF\tID\tEX\t.\t.\t.\t.\t.\t.\n");
                } 
                else if (i == 1) {
                    printf(".\tIF\tID\t.\t.\t.\t.\t.\t.\n");
                }
                else if (i == 2) {
                    printf(".\t.\tIF\t.\t.\t.\t.\t.\t.\n");
                }
                else {
                    printf(".\t.\t.\t.\t.\t.\t.\t.\t.\n");
                }
            }

            // If cyclecount is 4
            else if (cyclecount == 4) {
                // If first line
                if (i == 0) {
                    printf("%s", mips[i]);
                    printf("IF\tID\tEX\tMEM\t.\t.\t.\t.\t.\n");
                }
                else if (i == 1) {
                    // If it has dependencies 
                    if (isnop1[i] == 0 || isnop2[i] == 0) {
                        for (k = linecount; k > i; k--) {
                            strncpy(mips[k], mips[k-1], sizeof(mips[k]));
                            original[k] = k-1;
                        }
                        strncpy(mips[i], "nop\t\t", sizeof(mips[i]));
                        linecount++;

                        printf("%s", mips[i]);
                        printf(".\tIF\tID\t*\t.\t.\t.\t.\t.\n");
                        i++;

                        if (isnop1[i] == 0 || isnop2[i] == 0) {
                            for (k = linecount; k > i; k--) {
                                strncpy(mips[k], mips[k-1], sizeof(mips[k]));
                                original[k] = original[k-1];
                            }
                            strncpy(mips[i], "nop\t\t", sizeof(mips[i]));
                            linecount++;

                            printf("%s", mips[i]);
                            printf(".\tIF\tID\t*\t.\t.\t.\t.\t.\n");
                            i++;

                            printf("%s", mips[i]);
                            printf(".\tIF\tID\tID\t.\t.\t.\t.\t.\n");
                            i++;

                            printf("%s", mips[i]);
                            printf(".\t.\tIF\tIF\t.\t.\t.\t.\t.\n");
                            hasnop[i-1] = hasnop[i] = 6;
                            
                        } else {
                            printf("%s", mips[i]);
                            printf(".\tIF\tID\tID\t.\t.\t.\t.\t.\n");
                            hasnop[i] = 6;
                            i++;
                            if (mips[i][0] != '\0') {
                                printf("%s", mips[i]);
                                printf(".\t.\tIF\tID\t.\t.\t.\t.\t.\n");
                            }
                        }
                    } 
                    else {
                        printf("%s", mips[i]);
                        printf(".\tIF\tID\tEX\t.\t.\t.\t.\t.\n");
                        i++;
                        printf("%s", mips[i]);
                        printf(".\t.\tIF\tID\t.\t.\t.\t.\t.\n");
                    }
                    //i++;
                }
                else if (i == 3) {
                    printf("%s", mips[i]);
                    printf(".\t.\t.\tIF\t.\t.\t.\t.\t.\n");
                }
                else {
                    printf("%s", mips[i]);
                    if (original[i] == 3) {
                        printf(".\t.\t.\tIF\t.\t.\t.\t.\t.\n");
                    }
                    else {
                        printf(".\t.\t.\t.\t.\t.\t.\t.\t.\n");
                    }
                }
            }

            // If cyclecount is 5
            else if (cyclecount == 5) {
                if (i == 0) {
                    printf("%s", mips[i]);
                    printf("IF\tID\tEX\tMEM\tWB\t.\t.\t.\t.\n");
                }
                else if (i == 1) {
                    printf("%s", mips[i]);
                    if (strcmp(mips[i], "nop\t\t") == 0) {
                        printf(".\tIF\tID\t*\t*\t.\t.\t.\t.\n");
                    } 
                    else {
                        printf(".\tIF\tID\tEX\tMEM\t.\t.\t.\t.\n");
                    }
                }
                else if (i == 2) {
                    if (strcmp(mips[i], "nop\t\t") == 0) {
                        printf("%s", mips[i]);
                        printf(".\tIF\tID\t*\t*\t.\t.\t.\t.\n");
                    }
                    else if (original[i] == -1) {
                        if (isnop1[i] >= 0 || isnop2[i] >= 0) {
                            
                            // If the dependencies are the same
                            if (isnop1[i] == isnop2[i]) {
                                for (k = linecount; k > i; k--) {
                                    strncpy(mips[k], mips[k-1], sizeof(mips[k]));
                                    if (original[k-1] > 0) original[k] = original[k-1];
                                    else original[k] = k-1;
                                }
                                strncpy(mips[i], "nop\t\t", sizeof(mips[i]));
                                linecount++;
                                
                                if (isnop1[i] == 0) {
                                    hasnop[i+1] = 6; 
                                } 
                                else if (isnop1[i] == 1) {
                                    hasnop[i+1] = 7;
                                }
                                if (lwnum == isnop1[i]) lwnum = -1;
                            }
                            else if (isnop1[i] == -1) {
                                for (k = linecount; k > i; k--) {
                                    strncpy(mips[k], mips[k-1], sizeof(mips[k]));
                                    if (original[k-1] > 0) original[k] = original[k-1];
                                    else original[k] = k-1;
                                }
                                strncpy(mips[i], "nop\t\t", sizeof(mips[i]));
                                linecount++;
                                
                                if (isnop2[i] == 0) {
                                    hasnop[i+1] = 6; 
                                } 
                                else if (isnop2[i] == 1) {
                                    hasnop[i+1] = 7;
                                }
                                if (lwnum == isnop2[i]) lwnum = -1;
                            }
                            else if (isnop2[i] == -1) {
                                for (k = linecount; k > i; k--) {
                                    strncpy(mips[k], mips[k-1], sizeof(mips[k]));
                                    if (original[k-1] > 0) original[k] = original[k-1];
                                    else original[k] = k-1;
                                }
                                strncpy(mips[i], "nop\t\t", sizeof(mips[i]));
                                linecount++;
                                
                                if (isnop1[i] == 0) {
                                    hasnop[i+1] = 6; 
                                } 
                                else if (isnop1[i] == 1) {
                                    hasnop[i+1] = 7;
                                }
                                if (lwnum == isnop1[i]) lwnum = -1;
                            }
                            else if (isnop1[i] >= 0 && isnop2[i] >= 0 && isnop1[i] != isnop2[i]) {
                                strncpy(mips[i+2], mips[i], sizeof(mips[i+2]));
                                strncpy(mips[i+1], "nop\t\t", sizeof(mips[i+1]));
                                strncpy(mips[i], "nop\t\t", sizeof(mips[i]));
                                linecount += 2;
                                original[i+2] = i;
                                hasnop[i+2] = 7;
                                printf("%s", mips[i]);
                                printf(".\t.\tIF\tID\t*\t.\t.\t.\t.\n");
                                i++;
                            }
                            printf("%s", mips[i]);
                            printf(".\t.\tIF\tID\t*\t.\t.\t.\t.\n");
                            i++;

                            if (lwnum >= 0) {
                                strncpy(mips[linecount], mips[i], sizeof(mips[linecount]));
                                original[linecount] = original[i];
                                strncpy(mips[i], "nop\t\t", sizeof(mips[i]));
                                hasnop[4] = hasnop[3];
                                hasnop[3] = original[i] = -1;
                                printf("%s", mips[i]);
                                printf(".\t.\tIF\tID\t*\t.\t.\t.\t.\n");
                                i++;
                                linecount++;
                            }
                            printf("%s", mips[i]);
                            printf(".\t.\tIF\tID\tID\t.\t.\t.\t.\n");

                        }
                        // else
                    }
                    else {
                        printf("%s", mips[i]);
                        if (hasnop[i] == 6) {
                            printf(".\tIF\tID\tID\tID\t.\t.\t.\t.\n");
                        }
                        else {
                            printf(".\t.\tIF\tID\tEX\t.\t.\t.\t.\n");
                        }
                    }
                }
                else if (i == 3) {
                /*    index = original[i];
                    if (original[i] >= 0 && (isnop1[index] >= 0 || isnop2[index] >= 0 || lwnum >= 0)) {
                        strncpy(mips[4], mips[i], sizeof(mips[4]));
                        strncpy(mips[3], "nop\t\t", sizeof(mips[3]));
                        linecount++;
                        printf("%s", mips[i]);
                        printf(".\t.\tIF\tID\t*\t.\t.\t.\t.\n");
                        printf("%s", mips[i+1]);
                        printf(".\t.\tIF\tID\tID\t.\t.\t.\t.\n");
                        if (isnop1[index] == 0 || isnop2[index] == 0 || lwnum == 0) hasnop[i+1] = 6;
                        else if (isnop1[index] == 1 || isnop2[i] == 1 || lwnum == 1) hasnop[i+1] = 7;
                        
                        if (original[i] >= 0) original[i+1] = original[i];
                        else original[i+1] = i;
                    } */
                   // else {
                        printf("%s", mips[i]);
                        if (hasnop[i] == 6) {
                            if (strcmp(mips[1], "nop\t\t") == 0 && strcmp(mips[2], "nop\t\t") == 0) {
                                printf(".\tIF\tID\tID\tID\t.\t.\t.\t.\n");
                            }   
                            else {
                                printf(".\t.\tIF\tID\tID\tEX\t.\t.\t.\n");
                            }
                        }
                        else {
                            if (original[i] == 2) {
                                printf(".\t.\tIF\tID\tEX\t.\t.\t.\t.\n");
                            } else {
                                printf(".\t.\t.\tIF\tID\t.\t.\t.\t.\n");
                            }
                        }
                   // }
                    
                    
                }
                else if (i == 4) {
                    printf("%s", mips[i]);
                    if (original[i] == 2 && strcmp(mips[1], "nop\t\t") == 0 && strcmp(mips[2], "nop\t\t") == 0) {
                        printf(".\t.\tIF\tIF\tIF\t.\t.\t.\t.\n");
                    }
                    else if (original[i] == 3) {
                        printf(".\t.\t.\tIF\tID\t.\t.\t.\t.\n");
                    }
                    else {
                        printf(".\t.\t.\t.\tIF\t.\t.\t.\t.\n");
                    }
                    
                }
            }

            else if (cyclecount == 6) {
                if (i == 0) {
                    printf("%s", mips[i]);
                    printf("IF\tID\tEX\tMEM\tWB\t.\t.\t.\t.\n");
                }

                else if (i == 1) {
                    printf("%s", mips[i]);
                    if (strcmp(mips[i], "nop\t\t") == 0) {
                        printf(".\tIF\tID\t*\t*\t*\t.\t.\t.\n");
                    } 
                    else {
                        printf(".\tIF\tID\tEX\tMEM\tWB\t.\t.\t.\n");
                    }
                }

                else if (i == 2) {
                    printf("%s", mips[i]);
                    if (strcmp(mips[i], "nop\t\t") == 0) {
                        if (strcmp(mips[i-1], "nop\t\t") == 0) {
                            printf(".\tIF\tID\t*\t*\t*\t.\t.\t.\n");
                        }
                        else {
                            printf(".\t.\tIF\tID\t*\t*\t.\t.\t.\n");
                        }

                    }
                    else {
                        if (hasnop[i] == 6) {
                            printf(".\tIF\tID\tID\tID\tEX\t.\t.\t.\n");
                        }
                        else {
                            printf(".\t.\tIF\tID\tEX\tMEM\t.\t.\t.\n");
                        }
                    }
                }

                else if (i == 3) {
                    if (strcmp(mips[i], "nop\t\t") == 0) {
                        printf("%s", mips[i]);
                        printf(".\t.\tIF\tID\t*\t*\t.\t.\t.\n");

                    }
                    else if (hasnop[i] == 6) {
                        printf("%s", mips[i]);
                        if (strcmp(mips[1], "nop\t\t") == 0 && strcmp(mips[2], "nop\t\t") == 0) {
                            printf(".\tIF\tID\tID\tID\tEX\t.\t.\t.\n");
                        }
                        else {
                            printf(".\t.\tIF\tID\tID\tEX\t.\t.\t.\n");
                        }
                    }
                    else if (hasnop[i] == 7) {
                        printf("%s", mips[i]);
                        printf(".\t.\tIF\tID\tID\tID\t.\t.\t.\n");
                    }
                    else {
                        if (isnop1[i] == 1 || isnop2[i] == 1) {
                            if (linecount == 4) {
                                strncpy(mips[linecount], mips[i], sizeof(mips[linecount]));
                                strncpy(mips[i], "nop\t\t", sizeof(mips[i]));
                                original[linecount] = i;
                                linecount++;

                                printf("%s", mips[i]);
                                printf(".\t.\t.\tIF\tID\t*\t.\t.\t.\n");
                                i++;
                                hasnop[i] = 7;
                                printf("%s", mips[i]);
                                printf(".\t.\t.\tIF\tID\tID\t.\t.\t.\n");
                            }

                        }
                        else if (original[i] == 2) {
                            printf("%s", mips[i]);
                            printf(".\t.\tIF\tID\tEX\tMEM\t.\t.\t.\n");
                        }
                        else {
                            printf("%s", mips[i]);
                            printf(".\t.\t.\tIF\tID\tEX\t.\t.\t.\n");
                        }
                    }
                }

                else if (i == 4) {
                    printf("%s", mips[i]);
                    if (original[i] == 2) {
                        if (hasnop[i] == 7 && strcmp(mips[i-2], "nop\t\t") == 0) {
                            printf(".\t.\tIF\tID\tID\tID\t.\t.\t.\n");
                        }
                        else if (hasnop[i] == 6 && strcmp(mips[1], "nop\t\t") == 0 && strcmp(mips[2], "nop\t\t") == 0) {
                            printf(".\t.\tIF\tIF\tIF\tID\t.\t.\t.\n");
                        }
                    }
                    else if (original[i] == 3) {
                        printf(".\t.\t.\tIF\tID\tEX\t.\t.\t.\n");
                    }
                    else {
                        printf(".\t.\t.\t.\tIF\tID\t.\t.\t.\n");
                    }
                }
            }

            else if (cyclecount == 7) {
                if (i == 0) {
                    printf("%s", mips[i]);
                    printf("IF\tID\tEX\tMEM\tWB\t.\t.\t.\t.\n");
                }

                else if (i == 1) {
                    printf("%s", mips[i]);
                    if (strcmp(mips[i], "nop\t\t") == 0) {
                        printf(".\tIF\tID\t*\t*\t*\t.\t.\t.\n");
                    } 
                    else {
                        printf(".\tIF\tID\tEX\tMEM\tWB\t.\t.\t.\n");
                    }
                }

                else if (i == 2) {
                    printf("%s", mips[i]);
                    if (strcmp(mips[i], "nop\t\t") == 0) {
                        if (strcmp(mips[i-1], "nop\t\t") == 0) {
                            printf(".\tIF\tID\t*\t*\t*\t.\t.\t.\n");
                        }
                        else {
                            printf(".\t.\tIF\tID\t*\t*\t*\t.\t.\n");
                        }
                    } 
                    else {
                        if (hasnop[i] == 6) {
                            printf(".\tIF\tID\tID\tID\tEX\tMEM\t.\t.\n");
                        }
                        else {
                            printf(".\t.\tIF\tID\tEX\tMEM\tWB\t.\t.\n");
                        }
                    }
                }

                else if (i == 3) {
                    printf("%s", mips[i]);
                    if (hasnop[i] == 6) {
                        if (strcmp(mips[1], "nop\t\t") == 0 && strcmp(mips[2], "nop\t\t") == 0) {
                            printf(".\tIF\tID\tID\tID\tEX\tMEM\t.\t.\n");
                        }
                        else {
                            printf(".\t.\tIF\tID\tID\tEX\tMEM\t.\t.\n");
                        }
                    }
                    else if (hasnop[i] == 7) {
                        printf(".\t.\tIF\tID\tID\tID\tEX\t.\t.\n");
                    }
                    else if (strcmp(mips[i], "nop\t\t") == 0) {
                        if (strcmp(mips[i-1], "nop\t\t") == 0) {
                            printf(".\t.\tIF\tID\t*\t*\t*\t.\t.\n");
                        } else {
                            printf(".\t.\t.\tIF\tID\t*\t*\t.\t.\n");
                        }
                    }
                    else {
                        if (hasnop[2] >= 0) {
                            printf(".\t.\tIF\tID\tEX\tMEM\tWB\t.\t.\n");
                        } else {
                            printf(".\t.\t.\tIF\tID\tEX\tMEM\t.\t.\n");
                        }
                    }
                }

                else if (i == 4) {
                    printf("%s", mips[i]);
                    if (original[i] == 2) {
                        if (hasnop[i] == 7) {
                            if (strcmp(mips[i-2], "nop\t\t") == 0) {
                                printf(".\t.\tIF\tID\tID\tID\tEX\t.\t.\n");
                            }
                            else {
                                printf(".\t.\t.\tIF\tID\tID\tEX\t.\t.\n");
                            }
                        }
                        else if (hasnop[i] == 6 && strcmp(mips[1], "nop\t\t") == 0 && strcmp(mips[2], "nop\t\t") == 0) {
                            printf(".\t.\tIF\tIF\tIF\tID\tEX\t.\t.\n");
                        }
                    }
                    else if (original[i] == 3) {
                        if (hasnop[i] == 7) {
                            printf(".\t.\t.\tIF\tID\tID\tEX\t.\t.\n");
                        }
                        else {
                            printf(".\t.\t.\tIF\tID\tEX\tMEM\t.\t.\n");
                        }
                        
                    }
                    else {
                        printf(".\t.\t.\t.\tIF\tID\tEX\t.\t.\n");
                    }
                }

            }

            else if (cyclecount == 8) {
                if (i == 0) {
                    printf("%s", mips[i]);
                    printf("IF\tID\tEX\tMEM\tWB\t.\t.\t.\t.\n");
                }

                else if (i == 1) {
                    printf("%s", mips[i]);
                    if (strcmp(mips[i], "nop\t\t") == 0) {
                        printf(".\tIF\tID\t*\t*\t*\t.\t.\t.\n");
                    } 
                    else {
                        printf(".\tIF\tID\tEX\tMEM\tWB\t.\t.\t.\n");
                    }
                } 

                else if (i == 2) {
                    printf("%s", mips[i]);
                    if (strcmp(mips[i], "nop\t\t") == 0) {
                        if (strcmp(mips[i-1], "nop\t\t") == 0) {
                            printf(".\tIF\tID\t*\t*\t*\t.\t.\t.\n");
                        }
                        else {
                            printf(".\t.\tIF\tID\t*\t*\t*\t.\t.\n");
                        }
                    } 
                    else {
                        if (hasnop[i] == 6) {
                            printf(".\tIF\tID\tID\tID\tEX\tMEM\tWB\t.\n");
                        }
                        else {
                            printf(".\t.\tIF\tID\tEX\tMEM\tWB\t.\t.\n");
                        }
                    }
                }

                else if (i == 3) {
                    printf("%s", mips[i]);
                    if (hasnop[i] == 6) {
                        if (strcmp(mips[1], "nop\t\t") == 0 && strcmp(mips[2], "nop\t\t") == 0) {
                            printf(".\tIF\tID\tID\tID\tEX\tMEM\tWB\t.\n");
                        }
                        else {
                            printf(".\t.\tIF\tID\tID\tEX\tMEM\tWB\t.\n");
                        }
                    }
                    else if (hasnop[i] == 7) {
                        printf(".\t.\tIF\tID\tID\tID\tEX\tMEM\t.\n");
                    }
                    else if (strcmp(mips[i], "nop\t\t") == 0) {
                        if (strcmp(mips[i-1], "nop\t\t") == 0) {
                            printf(".\t.\tIF\tID\t*\t*\t*\t.\t.\n");
                        } else {
                            printf(".\t.\t.\tIF\tID\t*\t*\t*\t.\n");
                        }
                    }
                    else {
                        if (hasnop[2] >= 0) {
                            printf(".\t.\tIF\tID\tEX\tMEM\tWB\t.\t.\n");
                        } else {
                            printf(".\t.\t.\tIF\tID\tEX\tMEM\tWB\t.\n");
                        }
                    }
                }

                else if (i == 4) {
                    printf("%s", mips[i]);
                    if (original[i] == 2) {
                        if (hasnop[i] == 7) {
                            if (strcmp(mips[i-2], "nop\t\t") == 0) {
                                printf(".\t.\tIF\tID\tID\tID\tEX\tMEM\t.\n");
                            }
                            else {
                                printf(".\t.\t.\tIF\tID\tID\tEX\tMEM\t.\n");
                            }
                        }
                        else if (hasnop[i] == 6 && strcmp(mips[1], "nop\t\t") == 0 && strcmp(mips[2], "nop\t\t") == 0) {
                            printf(".\t.\tIF\tIF\tIF\tID\tEX\tMEM\t.\n");
                        }
                    }
                    else if (original[i] == 3) {
                        if (hasnop[i] == 7) {
                            printf(".\t.\t.\tIF\tID\tID\tEX\tMEM\t.\n");
                        }
                        else {
                            printf(".\t.\t.\tIF\tID\tEX\tMEM\tWB\t.\n");
                        }
                    }
                    else {
                        printf(".\t.\t.\t.\tIF\tID\tEX\tMEM\t.\n");
                    }
                }
            }

            else if (cyclecount == 9) {
                if (i == 0) {
                    printf("%s", mips[i]);
                    printf("IF\tID\tEX\tMEM\tWB\t.\t.\t.\t.\n");
                }

                else if (i == 1) {
                    printf("%s", mips[i]);
                    if (strcmp(mips[i], "nop\t\t") == 0) {
                        printf(".\tIF\tID\t*\t*\t*\t.\t.\t.\n");
                    } 
                    else {
                        printf(".\tIF\tID\tEX\tMEM\tWB\t.\t.\t.\n");
                    }
                } 

                else if (i == 2) {
                    printf("%s", mips[i]);
                    if (strcmp(mips[i], "nop\t\t") == 0) {
                        if (strcmp(mips[i-1], "nop\t\t") == 0) {
                            printf(".\tIF\tID\t*\t*\t*\t.\t.\t.\n");
                        }
                        else {
                            printf(".\t.\tIF\tID\t*\t*\t*\t.\t.\n");
                        }
                    } 
                    else {
                        if (hasnop[i] == 6) {
                            printf(".\t.\tIF\tID\tID\tEX\tMEM\tWB\t.\n");
                        }
                        else {
                            printf(".\t.\tIF\tID\tEX\tMEM\tWB\t.\t.\n");
                        }
                    }
                }

                else if (i == 3) {
                    printf("%s", mips[i]);
                    if (hasnop[i] == 6) {
                        if (strcmp(mips[1], "nop\t\t") == 0 && strcmp(mips[2], "nop\t\t") == 0) {
                            printf(".\tIF\tID\tID\tID\tEX\tMEM\tWB\t.\n");
                        }
                        else {
                            printf(".\t.\tIF\tID\tID\tEX\tMEM\tWB\t.\n");
                        }
                    }
                    else if (hasnop[i] == 7) {
                        printf(".\t.\tIF\tID\tID\tID\tEX\tMEM\tWB\n");
                    }
                    else if (strcmp(mips[i], "nop\t\t") == 0) {
                        if (strcmp(mips[i-1], "nop\t\t") == 0) {
                            printf(".\t.\tIF\tID\t*\t*\t*\t.\t.\n");
                        } else {
                            printf(".\t.\t.\tIF\tID\t*\t*\t*\t.\n");
                        }
                    }
                    else {
                        if (hasnop[2] >= 0) {
                            printf(".\t.\tIF\tID\tEX\tMEM\tWB\t.\t.\n");
                        } else {
                            printf(".\t.\t.\tIF\tID\tEX\tMEM\tWB\t.\n");
                        }
                    }
                }

                else if (i == 4) {
                    printf("%s", mips[i]);
                    if (original[i] == 2) {
                        if (hasnop[i] == 7) {
                            if (strcmp(mips[i-2], "nop\t\t") == 0) {
                                printf(".\t.\tIF\tID\tID\tID\tEX\tMEM\tWB\n");
                            }
                            else {
                                printf(".\t.\t.\tIF\tID\tID\tEX\tMEM\tWB\n");
                            }
                        }
                        else if (hasnop[i] == 6 && strcmp(mips[1], "nop\t\t") == 0 && strcmp(mips[2], "nop\t\t") == 0) {
                            printf(".\t.\tIF\tIF\tIF\tID\tEX\tMEM\tWB\n");
                        }
                    }
                    else if (original[i] == 3) {
                        if (hasnop[i] == 7) {
                            printf(".\t.\t.\tIF\tID\tID\tEX\tMEM\t.\n");
                        }
                        else {
                            printf(".\t.\t.\tIF\tID\tEX\tMEM\tWB\t.\n");
                        }
                    }
                    else {
                        printf(".\t.\t.\t.\tIF\tID\tEX\tMEM\tWB\n");
                    }
                }
            }

            i++;
        }
        printf("\n");
        cyclecount++;

    }

    // End simulation
    printf("END OF SIMULATION\n");

    fclose(myfile);

    return EXIT_SUCCESS;
}