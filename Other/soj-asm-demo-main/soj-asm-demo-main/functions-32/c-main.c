//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
//
// Implementation of functions with parameters
//
//***************************************************************************

#include <stdio.h>

// functions prototypes
int sum( int a, int b );
int average( int *array, int N );
int division( int a, int b, int *remainder );
char *strmirror( char *str );
char *int2str( int number, char *str );
int strlength( char *str );
char *strnospaces( char *str );

int main()
{
    printf( "Sum of two numbers: %d\n\n", sum( 1111, 2222 ) );

    int i_array[ 10 ] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    printf( "Average of array elements: %d\n\n", average( i_array, 10 ) );

    int remainder;
    printf( "Division of two numbers: %d\n", division( 100, 31, &remainder ) );
    printf( "Remainder: %d\n\n", remainder );

    char strformirror[] = "String before mirror.";
    printf( "Mirrored string: '%s'\n\n", strmirror( strformirror ) );

    char str[ 32 ];
    printf( "Positive number:  %s\n", int2str( 7621, str ) );
    printf( "Zero           :  %s\n", int2str( 0, str ) );
    printf( "Negative number:  %s\n\n", int2str( -2389, str ) );

    char mezery[] = "  T e xt w a  s fu l l   o f spa c e s.   ";
    printf( "String length before: %d\n", strlength( mezery ) );
    printf( "Text bez mezer: '%s'\n", strnospaces( mezery ) );
    printf( "String length after:  %d\n", strlength( mezery ) );

}
