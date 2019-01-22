/* q3-4.c */

#include <stdio.h>
#include <stdlib.h>

/* Change all uppercase letters in string s to lowercase, leaving all
 * other characters intact; return the number of "down-cased" characters
 *
 * ASCII: 'a' is 0x61; 'z' is 0x7a; 'A' is 0x41; 'Z' is 0x5a
 */
int downcase( char * s )
{
  int count;

  for ( count = 0 ; *s ; s++ )
  {
    if ( *s >= 'A' && *s <= 'Z' )
    {
      *s += 0x20;
      count++;
    }
  }

  return count;
}

int main()
{
  char test[80] = "abcdEFGHijklMNOP1234!!!!";
  printf( "BEFORE: [%s]\n", test );
  int count = downcase( test );
  printf( " AFTER: [%s] returned %d\n", test, count );
  return EXIT_SUCCESS;
}
