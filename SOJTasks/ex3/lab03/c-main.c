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
//
int sum_int( int a, int b );
long long sum_int64( int a, int b );
int imul_int( int a, int b );
long long imul_int64( int a, int b );
int prumer( int *pole, int N );
int pocet_az( char *str );

int main()
{
    sum_int( 5, 6 );
    printf( "sum %d\n", sum_int( 1111, 4444 ) );
    printf( "mul %d\n", imul_int( 1000, 4444 ) );
    printf( "mul %d\n", imul_int( 1000000, 4444000 ) );
    printf( "mul64 %Ld\n", imul_int64( 1000000, 4444000 ) );

    printf( "sum %d\n", sum_int( 0x7FFFFFFF, 1 ) );
    printf( "sum64 %Ld\n", sum_int64( 0x7FFFFFFF, 1 ) );
    printf( "sum64 %Ld\n", sum_int64( 0x7FFFFFFF, 0x7FFFFFFF ) );
    printf( "sum64 0X%LX\n", sum_int64( 0x7FFFFFFF, 0x7FFFFFFF ) );

    int pole[ 10 ] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
    printf( "prumer %d\n", prumer( pole, 10 ) );

    printf( "pocet %d\n", pocet_az( "halo HALO c 12334 asm" ) );
}
