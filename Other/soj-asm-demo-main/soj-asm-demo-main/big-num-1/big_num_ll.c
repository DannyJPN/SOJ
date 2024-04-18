//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
//
// Computing with Big Numbers
//
//***************************************************************************

#include <stdio.h>
#include <string.h>

// a += b
void add_intNint32( int *a, int b, int N );
// a *= b
void mul_intNint32( int *a, int b, int N );
// a /= b, return reminder
int div_intNint32( int *a, int b, int N );

void intN_to_str( int *n, int N, char *s );
void str_to_intN( char *s, int *n, int N );


#define N_INT   2
#define N_CHAR  ( N_INT * 32 * 10 / 3 + 2 )

int main()
{
  long long x = 8983082438909876534LL;
  long long y = 0;
  char cislo[ N_CHAR ];

  printf( "Example of big number computing.\n" );
  printf( "The use of 64-bit number (long long)\n\n" );

  printf( "Assigned number in binary form: x=%Ld\n\n", x );

  intN_to_str( ( int * ) &x, N_INT, cislo );

  printf( "Number 'x' converted into string: '%s'\n\n", cislo );

  str_to_intN( cislo, ( int * ) &y, N_INT );

  printf( "Text form of 'x' back in binary form: y=%Ld\n\n", y );

}
