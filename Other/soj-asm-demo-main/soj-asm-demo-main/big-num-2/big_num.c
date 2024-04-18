//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
//
// Computing with Big Numbers
// Multiplication and Division
//
//***************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// a /= b; return n % div
int div_intNint32( int *a, int b, int N );
// a += b 
void add_intNint32( int *a, int b, int N );
// a *= b
void mul_intNint32( int *a, int b, int N );
// a += b
void add_intNintN( int *a, int *b, int N );
// a -= b
void sub_intNintN( int *a, int *b, int N );
// n <<= 1; return CF;
int shl_intN( int *n, int N );
// n >>= 1; return CF
int shr_intN( int *n, int N );
// n >>>= 1; return CF
int ror_intN( int *n, int N );
// n >>= cl <0,31>; return lost bits
int shrd_intN( int *n, int cl, int N );
// n <<= cl <0,31>; return lost bits
int shld_intN( int *n, int cl, int N );

// intN to string
void intN_to_str( int *n, int N, char *s );
// string to intN
void str_to_intN( char *s, int *n, int N );

// a /= b, b = remainder
void div_intNintN( int *a, int *b, int N );
// a *= b
void mul_intNintN( int *a, int *b, int N );
// is zero? ( n == 0 )
// return n == 0
int is_zero( int *n, int N )
{
  int i = 0;
  while ( i < N ) if ( n[ i++ ] ) return 0;
  return 1;
}

// compare of two intN numbers
// a >  b return  1
// a == b return  0
// a <  b return -1
int cmp_intNintN( int *a, int *b, int N )
{
  int i;
  for ( i = N - 1; i >= 0; i-- )
  {
      if ( a[ i ] == b[ i ] ) continue;
      if ( ( unsigned int ) a[ i ] > ( unsigned int ) b[ i ] ) return 1;
      return -1;
  }
  return 0;
}

// intN to string in hexadecimal form
void intN_to_hex( int *n, int N, char *s )
{
   int i = 0;
   for ( ; i < N; i++, s+= 8 )
       sprintf( s, "%08X", n[ N - i - 1 ] );
}

// random number
void get_random( char *s, int N )
{
  int i = 0;
  static int init_rand = 1;
  if ( init_rand ) srand( getuid() );

  for ( ; i < N; i++ )
    s[ i ] = rand() % 10 + '0';

  s[ i ] = 0;
}

// a /= b, b = remainder
/*void div_intNintN( int *a, int *b, int N )
{
  int dividend[ 2 * N ];
  int *H = divident + N;

  divident = a

  for ( all_bits ... )
  {
      divident <<= 1
      res <<= 1
      if ( H >= b )
      {
          H -= b;
          res |= 1;
      }
  }
  ... store res-ult and remainder
}*/

// a *= b
/*void mul_intNintN( int *a, int *b, int N )
{
  res = 0

  for( all_bits.... )
  {
      if ( b is odd )
          res += a;
      a <<= 1;
      b >>= 1;
  }
  store res-ult...
}*/

#define N_INT   16
#define N_CHAR  ( N_INT * 32 * 3 / 10 + 2 )

void print_number( int *n, int N )
{
  char number[ N_CHAR ];
  int i = 0;

  intN_to_hex( n, N, number );
  printf( "Hexadecimal number:\n%s\n\n", number );

  intN_to_str( n, N_INT, number );
  printf( "Decimal number:\n%s\n\n", number );

  //printf( "Content of array (low first):\n" );
  //for ( ; i < N; i++ )
  //    printf( "%d ", n[ i ] );

  //printf( "\n\n" );
}

int main()
{
  int bin1[ N_INT ] =
    { 0xabcd, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // 2^255
  int bin2[ N_INT ] =
    { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 }; // 2^256
  int divisor[ N_INT ] =
    { 1000000000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // 10^9

  int ran_number_b[ N_INT ];
  char ran_number_a[ N_CHAR ];

  printf( "\nBig number computing example.\n" );
  printf( "Computing with assigned numbers\n\n" );
  printf( "Numbers multiplication:\n\n" );

  mul_intNintN( bin1, bin2, N_INT );
  print_number( bin1, N_INT );

  printf( "Press <Enter>\n" );
  getchar();

  get_random( ran_number_a, 100 );
  printf( "Computing with random number:\n\n" );

  printf( "Division of numbers\n\n" );

  str_to_intN( ran_number_a, ran_number_b, N_INT );
  print_number( ran_number_b, N_INT );

  div_intNintN( ran_number_b, divisor, N_INT );

  printf( "Result of division:\n" );
  print_number( ran_number_b, N_INT );

  printf( "Remainder:\n" );
  print_number( divisor, N_INT );

  return 0;
}

