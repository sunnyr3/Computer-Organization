/* HW 6 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

int lru(int cache[], int access[], int index, int associativity) {
    int i, count, max, returnIndex=0, temp;
    for (i = 0; i < associativity; i++) {
        count = 0;
        temp = index;
        while (cache[i] != access[temp] && temp >= 0) {
            temp--;
            count++;
        }
        if (i == 0) {
            max = count;
        } 
        else {
            if (count > max) {
                max = count;
                returnIndex = i;
            }
        }
    }

    return returnIndex;
}

int belady(int cache[], int access[], int index, int associativity, int mem_count) {
    int i, count, max, returnIndex=0, temp;
    for (i = 0; i < associativity; i++) {
        count = 0;
        temp = index;
        while(cache[i] != access[temp] && temp < mem_count) {
            temp++;
            count++;
        }
        if (i == 0) {
            max = count;
        }
        else {
            if (count > max) {
                max = count;
                returnIndex = i;
            }
        }
    }

    return returnIndex;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Invalid usage\n");
        return EXIT_FAILURE;
    }

    // Get cache associativity and algorithm
    int cache_associativity = atoi(argv[1]);
    int set_num = 256 / cache_associativity;
    int cache_value[set_num][cache_associativity];
    char cache_algo[7];
    strncpy(cache_algo, argv[2], sizeof(cache_algo));

    int i, j;

    for (i = 0; i < set_num; i++) {
        for (j = 0; j < cache_associativity; j++) {
            cache_value[i][j] = 0;
        }
    }

    // Open input file
    char const* const fileName = argv[3];
    FILE * myfile;
    myfile = fopen(fileName, "r");

    // check if the file can be opened
    if (!myfile) {
        fprintf(stderr, "Error: Cannot open file!\n");
        return EXIT_FAILURE;
    }

    int mem_count = 0, temp;
    int access[1024];

    while (fscanf(myfile, "%d", &temp) == 1) {
        access[mem_count] = temp;
        mem_count++;
    }

    printf("Cache size: 256\n");
    printf("Cache associativity: %d\n", cache_associativity);
    printf("Cache sets: %d\n", set_num);
    printf("Cache algorithm: %s\n", cache_algo);

    int hit_count=0, set;

    bool alreadyhit;
    for (i = 0; i < mem_count; i++) {
        printf("%d ", access[i]);
        alreadyhit = false;
        set = access[i] % set_num;
            
        // Loop through the cache value to see if it is already got hit
        for (j = 0; j < cache_associativity; j++) {
            // Got hit already
            if (cache_value[set][j] == access[i]) {
                printf("(hit)\n");
                hit_count++;
                alreadyhit = true;
            }
        }

		if (!alreadyhit) {
            printf("(miss)\n");
			for (j = 0; j < cache_associativity; j++) {
				if (cache_value[set][j] == 0) {
					cache_value[set][j] = access[i];
					break;
				}
				if (j == cache_associativity - 1) {
                    if (strcmp(cache_algo, "LRU") == 0) {
                        temp = lru(cache_value[set], access, i, cache_associativity);
                    } 
                    else if (strcmp(cache_algo, "Belady") == 0) {
                        temp = belady(cache_value[set], access, i, cache_associativity, mem_count);
                    }
					cache_value[set][temp] = access[i];
				}
			}
		}
    }

    printf("Cache accesses: %d\n", mem_count);
    printf("Cache hits: %d\n", hit_count);
    printf("Cache misses: %d\n", mem_count-hit_count);
    printf("Overall hit rate: %1.6f\n", (float)hit_count/mem_count);
    

    fclose(myfile);
    return EXIT_SUCCESS;
}

