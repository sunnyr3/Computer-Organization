/* Checkpoint 3 */

#include <stdio.h>
#include <stdlib.h>

void ieee754encode(float value, char* encoded);

int main() {
    float input;
    char * output = malloc(33 * sizeof(char *));
    
    printf("Enter a float value: ");
    scanf("%f", &input);   

    // Print input
    printf("input: %f\n", input);

    // Call function
    ieee754encode(input, output);

    // Print output
    printf("output: %s\n", output);

    return EXIT_SUCCESS;
}

int getExponent(int value, char* mantissa) {
    int exponent = 0, i = 0, j = 0, binary;
    int * temp = malloc(33);

    while (value > 0) {
        binary = value % 2;
        temp[i++] = binary;
        exponent++;
        value = value / 2;
    }
    exponent--;
    i -= 2;

    while (i >= 0) {
        mantissa[j] = temp[i] + '0';
        j++;
        i--;
    }

    return exponent;
}

void ieee754encode(float value, char* encoded) {
    char * mantissa = malloc(23 * sizeof(char*));
    // Determine the sign
    int sign = 0;
    if (value < 0) {
        sign = 1;
    }

    // Print sign
    printf("sign: %d\n", sign);
    encoded[0] = sign + '0';

    // Get exponent
    int temp = (int)value;
    int exponent = getExponent(temp, mantissa);
    exponent += 127;

    int index = 8, binary;
    while (exponent > 0) {
        binary = exponent % 2;
        encoded[index] = binary + '0';
        index--;
        exponent = exponent / 2;
    }

    // Print exponent
    printf("exponent: ");
    index = 1;
    for (index = 1; index < 9; index++) {
        printf("%c", encoded[index]);
    }
    printf("\n");

    float fraction = value - (float)temp;
    
    printf("fraction: ");
    int j = 0;
    while (mantissa[j]) {
        encoded[index] = mantissa[j++];
        printf("%c", encoded[index]);
        index++;
    }
    for (; index < 33; index++) {
        fraction *= 2.0;
        if (fraction >= 1) {
            encoded[index] = 1 + '0';
            fraction -= 1.0;
            printf("%c", encoded[index]);
        } else {
            encoded[index] = '0';
            printf("%c", encoded[index]);
        }
    } 
    printf("\n");
    
    return;
}