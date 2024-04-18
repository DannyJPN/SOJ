//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
//
// Empty project
//
//***************************************************************************

#include <stdio.h>

// Variables
//
long long add_int64int32( long long t_a, int t_b );
long long mul_int64int32( long long t_a, int t_b );
long long div_int64int32( long long t_a, int t_b, int *t_r );

void add_intNint32( int *t_intN, int t_b, int t_N ); // t_intN += t_b
void mul_intNint32( int *t_intN, int t_b, int t_N ); // t_intN *= t_b
int div_intNint32( int *t_intN, int t_b, int t_N ); // t_intN *= t_b

#define N 8

int main()
{
    printf( "add_32_64 %llX\n", add_int64int32( 0xFFFFFFFFFFFFFFll, 1 ) ); 
    printf( "mul_32_64 %lld\n", mul_int64int32( 1111111111111111ll, 3 ) ); 
    printf( "mul_32_64 %llX\n", mul_int64int32( 0xCAFECAFECAFEll, 16 ) ); 
    int l_zbytek;
    printf( "div_32_64 %d %lld\n", l_zbytek, div_int64int32( 1234567891234ll, 100, &l_zbytek ) ); 
    printf( "div_32_64 %llX\n", div_int64int32( 0xCAFECAFECAFEll, 16, NULL ) ); 

    int l_aN[ N ] = { 0xFFFFFFFF, 0xFFFFEFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0, 0, 0, 0 };
    printf( "add\n" );
    add_intNint32( l_aN, 1, N );
    for ( int i = N - 1; i >= 0; i-- )
        printf( "%08X ", l_aN[ i ] );
    printf( "\n" );
    printf( "mul\n" );
    mul_intNint32( l_aN, 64, N );
    for ( int i = N - 1; i >= 0; i-- )
        printf( "%08X ", l_aN[ i ] );
    printf( "\n" );
    printf( "div\n" );
    add_intNint32( l_aN, 33, N );
    int l_r = div_intNint32( l_aN, 64, N );
    for ( int i = N - 1; i >= 0; i-- )
        printf( "%08X ", l_aN[ i ] );
    printf( "\n zbytek %d\n", l_r );
}
