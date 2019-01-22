/* lab11.c */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>

/* Given a range of bit index values (i.e., bit positions 0..31),
 * which is an inclusive range, this function determines and
 * returns the number of blocks in the cache
 *
 * e.g., given the example address below, an idx_start of 4
 *       and an idx_end of 11 would return 2^8 or 256
 *
 *    2    1    3    5    C    6    9    0  <== hex
 * 0010 0001 0011 0101 1100 0110 1001 0000  <== binary
 *                          ^       ^
 *                         end    start
 */
uint32_t block_count( uint32_t idx_start, uint32_t idx_end )
{
  /* assert() calls can help ensure that preconditions are met
   * and that your logic is valid!
   */
  assert( idx_start < idx_end );

  int range = idx_end - idx_start + 1;

  return pow(2, range);
}


/* Given an address and range of bits in the index
 * (i.e., start-to-end, inclusive), return the index
 *
 * e.g., given the address below, an idx_start of 4,
 *       and an idx_end of 11
 *
 *    2    1    3    5    C    6    9    0  <== hex
 * 0010 0001 0011 0101 1100 0110 1001 0000  <== binary
 *                          ^       ^
 *                         end    start
 *
 * this function should return 0110 1001 in binary
 * or 0x69 in hex or 105 decimal
 */
uint32_t get_index( uint32_t address, uint32_t idx_start, uint32_t idx_end )
{
  /* assert() calls can help ensure that preconditions are met
   * and that your logic is valid!
   */
  assert( idx_start < idx_end );

  int sum = 0, i;
  // Right shift
  for (i = 0; i < idx_start; i++) {
        address = address >> 1;
  }

  int range = idx_end - idx_start + 1;
  for (i = 0; i < range; i++) {
        sum = sum << 1;
        sum += 1;
  }

  sum = address & sum;
  return sum;
}


/* Utilizing slides 29-38 of Chapter 5 as a reference,
 * calculate the total bits in the cache block,
 * including data, tag, and valid bits.
 * Assume 32-bit addressing.
 *
 * The bob argument should be the leftmost bit number
 * of the block-offset bits (BOB); e.g., a 3 here means
 * bits 0-3 (inclusive) are used for the BOB.
 *
 * e.g., in calling get_cache_block_size( 2, 16, 1 ),
 *       we would first determine that we need 15 bits
 *       for the index (bits 2..16, inclusive).  Next,
 *       we have two block-offset bits (bits 0..1, inclusive).
 *       Given this, we next determine that the tag consists
 *       of 32-15-2=15 bits; therefore, the block size is:
 *
 *                  1 validity bit
 *                 15 bits (tag) 
 *               + 32 bits (data)
 *              ------------------------
 *                 48 bits (block size)
 */
uint32_t get_cache_block_size( uint32_t idx_start, uint32_t idx_end, uint32_t bob )
{
  /* assert() calls can help ensure that preconditions are met
   * and that your logic is valid!
   */
  assert( idx_start < idx_end );
  assert( bob + 1 == idx_start );

  uint32_t tag_size = 32 - idx_end;
  uint32_t bob_size = (1 << idx_start) * 8 + tag_size;
  printf("%d\n", 1 << idx_start);
  //uint32_t index_size = idx_end - idx_start + 1;
  //uint32_t tag_size = 32 - index_size - idx_start;
  //uint32_t bob_size = tag_size + 1 + 32;

  return bob_size;
}


int main()
{
  printf( "block_count( 4, 11 ) returned %d (should be 256)\n",
          block_count( 4, 11 ) );

  printf( "block_count( 5, 13 ) returned %d (should be 512)\n",
          block_count( 5, 13 ) );


  printf( "get_index( 0x2135C690, 4, 11 ) returned %d (should be 105)\n",
          get_index( 0x2135C690, 4, 11 ) );

  printf( "get_index( 0x2135C690, 5, 17 ) returned %d (should be ???)\n",
          get_index( 0x2135C690, 5, 17 ) );


  printf( "get_cache_block_size( 2, 16, 1 ) returned %d (should be 48)\n",
          get_cache_block_size( 2, 16, 1 ) );

  printf( "get_cache_block_size( 4, 15, 3 ) returned %d (should be ???)\n",
          get_cache_block_size( 4, 15, 3 ) );

  return EXIT_SUCCESS;
}
