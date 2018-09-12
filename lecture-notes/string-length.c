/* string-functions.c */

#include <stdio.h>
#include <stdlib.h>

#if 0
int stringlen( char * s )   /* char s[] */
{
  int i = 0;
  while ( s[i] != '\0' )
  {
    i++;
  }
  return i;
}

int stringlen( char * s )   /* char s[] */
{
  int len;
  for ( len = 0 ; *s != '\0' ; s++, len++ );
  return len;
}

int stringlen( char * s )   /* char s[] */
{
  char * ptr = s;   /* ptr and s now point to the same mem address */
  while ( *ptr != '\0' )
  {
    ptr++;
  }
  return ptr - s;
}
#endif

int main()
{
  /* e.g., str is located in mem address 0x400638 */

  char * str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
             /* ABCDEFGHIJKLMNOPQRSTUVWXYZ\0 */

  printf( "this gets passed by value to stringlen: %p\n", str );
  printf( "len of str: %d\n", stringlen( str ) );
  

  return EXIT_SUCCESS;
}
