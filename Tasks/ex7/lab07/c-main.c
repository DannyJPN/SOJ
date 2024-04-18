//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
//
// Empty project
//
//***************************************************************************

#include <stdio.h>
#include <string.h>

// Variables

int add32( int, int );
long add64( long, long );

void minmax( long *t_array, int t_N, long *t_min, long *t_max );
long average( long *t_array, int t_N );

long mystrlen( const char *t_str );
char *strmirror( char *t_str );

int main()
{
    printf( "add32  %d\n", add32( 1000000000, 1000000000 ) );
    printf( "add64  %ld\n", add64( 1000000000000000, 1000000000000000 ) );

    long l_long_array[ 10 ] = { -11, 2, 3, -4, 5, 6, -7, 8, -99 };
    long l_min, l_max;

    minmax( l_long_array, 10, &l_min, &l_max );
    printf( "min %ld max %ld\n", l_min, l_max );

    printf( "average %ld\n", average( l_long_array, 10 ) );


    printf( "strlen %ld\n", mystrlen( "Ahoj programatori!" ) );
    printf( "strlen %ld\n", strlen( "Ahoj programatori!" ) );

    char l_str[] = "Prechod na 64 bitu.";
    printf( "mirror '%s'\n", strmirror( l_str ) );
}
