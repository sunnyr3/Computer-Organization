/* lab09.c */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


/* Perform a logical shift-left operation on bitbucket,
 * pushing the given bit input as the least-significant bit (lsb).
 *
 * Return the resulting 32-bit integer.
 */
uint32_t push_lsb_bit( uint32_t bitbucket, uint32_t bit )
{
    return (bitbucket << 1) | bit;
}


/* Perform a logical shift-right operation on bitbucket,
 * popping and returning the least-significant bit (lsb).
 *
 * Note that bitbucket is passed by reference and should
 * be changed accordingly.
 */
uint32_t pop_lsb_bit( uint32_t * bitbucket )
{
    uint32_t temp = *bitbucket & 1;
    *bitbucket = *bitbucket >> 1;
    return temp;
}


/* Print out a 32-bit binary string using pop_lsb_bit().
 */
void print_b32( uint32_t s )
{
    int i;
    uint32_t binaryString[32];
    
    for ( i = 0 ; i < 32 ; i++ )
    {
        binaryString[i] = pop_lsb_bit( &s );
    }
    
    for ( i = 31 ; i >= 0 ; i-- )
    {
        printf( "%d", binaryString[i] );
    }

    printf( "\n" );
}


/* Isolate a range of bits within a given 32-bit integer.
 * More specifically, return the integer containing bits
 * from input bitbucket starting at msbindex and ending at
 * lsbindex, where index ranges from 0 (lsb) to 31 (msb).
 *
 * e.g., if bitbucket is 123, msbindex is 5 and lsbindex is 1:
 *
 *       0000 0000 0000 0000 0000 0000 0111 1011
 *                                       ^    ^
 *                                 msbindex  lsbindex
 *
 *       0000 0000 0000 0000 0000 0000 0001 1101
 *
 *       function returns 16+8+4+1=29 in this example
 */
uint32_t isolate_bits( uint32_t bitbucket, uint32_t msbindex, uint32_t lsbindex )
{
    uint32_t mask = (1 << (msbindex - lsbindex + 1)) - 1;
    bitbucket = bitbucket >> lsbindex;
    return bitbucket & mask;
}


/* Decode the given instruction by:
 * (1) determining the instruction opcode
 * (2) based on the opcode, returning the appropriate
 *     funct code (or zero if not applicable)
 *
 * Display the decoded instruction opcode by printing
 * add, slt, sub, j, beq, etc. as follows:
 *
 *   INSTRUCTION OPCODE: add
 *
 * Also, when applicable, display the ALU control lines
 * (from Figure B.5.13) using the format shown below:
 *
 *   ALU CONTROL INPUT: 0010
 */
uint32_t decode_inst( uint32_t instruction )
{
    uint32_t op = isolate_bits(instruction, 31, 26);
    uint32_t func = isolate_bits(instruction, 5, 0);
    if (!op) {
        switch(func) {
            case 0x20:
                printf("INSTRUCTION OPCODE: add\nALU CONTROL INPUT: 0010\n");
                return func;
            case 0x22:
                printf("INSTRUCTION OPCODE: sub\nALU CONTROL INPUT: 0110\n");
                return func;
            case 0x24:
                printf("INSTRUCTION OPCODE: and\nALU CONTROL INPUT: 0000\n");
                return func;
            case 0x25:
                printf("INSTRUCTION OPCODE: or\nALU CONTROL INPUT: 0001\n");
                return func;
            case 0x2A:
                printf("INSTRUCTION OPCODE: slt\nALU CONTROL INPUT: 0111\n");
                return func;
        }
    } else {
        switch(op) {
            case 0x04:
                printf("INSTRUCTION OPCODE: beq\n");
                break;
            case 0x02:
                printf("INSTRUCTION OPCODE: j\n");
                break;
            
        }
    }
    return 0;
    
}


/* Add other tests to main() */
int main()
{
    int i;

    /*********** CHECKPOINT 1 ***********/
    printf( "Testing pop_lsb_bit( 13 ):\n" );
    uint32_t temp = 13;
    print_b32( temp );

    uint32_t x = push_lsb_bit( 13, 1 );
    printf( "push_lsb_bit( 13, 1 ) is %d\n", x );

    printf( "in binary:\n" );
    print_b32( x );



    /*********** CHECKPOINT 2 ***********/
    uint32_t val = isolate_bits( 123, 5, 1 );
    printf( "val is %d\n", val );

    val = isolate_bits( 1234, 5, 1 );
    printf( "val is %d\n", val );

    val = isolate_bits( 65535, 8, 3 );
    printf( "val is %d\n", val );

    val = isolate_bits( 2147483647, 30, 20 );
    printf( "val is %d\n", val );

    


    /*********** CHECKPOINT 3 ***********/
    uint32_t inst[] =
    {
        45459490,
        66803754,
        273938261,
        12965920,
        137929722
    };

    for ( i = 0 ; i < 5 ; i++ )
    {
        uint32_t funct_code = decode_inst( inst[i] );
        printf( "Resulting funct code is %d\n\n", funct_code );
    }


    return EXIT_SUCCESS;
}
