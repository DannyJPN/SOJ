//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
//
// Computing with Big Numbers
//
//***************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// a += b
void add_intNint32( int *a, int b, int N );
// a *= b
void mul_intNint32( int *a, int b, int N );
// a /= b, return reminder
int div_intNint32( int *a, int b, int N );

void intN_to_str( int *n, int N, char *s );
void str_to_intN( char *s, int *n, int N );

// return n == 0
int is_zero( int *n, int N )
{
  int i = 0;
  while ( i < N ) if ( n[ i++ ] ) return 0;
  return 1;
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
  srand( getuid() );

  for ( ; i < N; i++ )
    s[ i ] = rand() % 10 + '0';

  s[ i ] = 0;
}

// function template for intN to string conversion
/*
void intN_to_str( int *n, int N, char *s )
{
  ...

  while ( !is_zero( n, N ) )
    s[ i++ ] = div_intNint32( ... ) + '0';

  ...
}*/

// function template for string to intN conversion
/*
void str_to_intN( char *s, int *n, int N )
{
  ...
  while ( *s )
  {
      mul_intNint32( ... );
      add_intNint32( ... );
  }
  ...
}
*/

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

  printf( "Content of array (low first):\n" );
  for ( ; i < N; i++ )
      printf( "%d ", n[ i ] );

  printf( "\n\n" );
}

int main()
{
  long long ll = 0xffffffff;
  int bin_number[ N_INT ] =
//    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x80000000 }; // 2^511
    { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff }; // 2^511
  int ran_number_b[ N_INT ];
  char ran_number_a[ N_CHAR ];

  printf( "\nBig number computing example.\n" );
  printf( "%d bits numbers are used.\n\n", N_INT * 32 );

  printf( "Computing with assigned number\n\n" );

  mul_intNint32( bin_number, 0xffffffff, N_INT );
  print_number( bin_number, N_INT );

  printf( "Press <Enter>\n" );
  getchar();

  printf( "Computing with random number\n\n" );

  get_random( ran_number_a, 100 );
  printf( "Generated random number:\n\n%s\n\n", ran_number_a );

  str_to_intN( ran_number_a, ran_number_b, N_INT );
  print_number( ran_number_b, N_INT );

  return 0;
}
