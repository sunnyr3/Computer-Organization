/* string-copy.c */

#include <stdio.h>
#include <stdlib.h>

/* copy the source string into target;
   you can assume enough memory has already been allocated;
   and you can rely on source ending in '\0' at some point... */

#if 0
void stringcopy( char * target, char * source )
{
  if ( source == NULL || target == NULL ) return;

  int i = 0;
  while ( ( target[i] = source[i] ) != '\0' ) i++;
}

void stringcopy( char * target, char * source )
{
  while ( ( *target = *source ) != '\0' )
  {
    source++;
    target++;
  }
}

void stringcopy( char * target, char * source )
{
  while ( ( *target++ = *source++ ) != '\0' );
}

void stringcopy( char * target, char * source )
{
  while ( ( *target++ = *source++ ) );
}
#endif

int main()
{
  char * str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char t[100];

  t[0] = '\0';

  printf( "BEFORE: str is \"%s\"\n", str );
  printf( "BEFORE: t is \"%s\"\n", t );

  stringcopy( t, str );

  printf( "AFTER: str is \"%s\"\n", str );
  printf( "AFTER: t is \"%s\"\n", t );

  return EXIT_SUCCESS;
}
