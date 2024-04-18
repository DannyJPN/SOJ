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
void intN_to_str( int *n, int N, char *s );
void str_to_intN( char *s, int *n, int N );

long long m_add_int64int32( long long t_a, int t_b );
long long m_mul_int64int32( long long t_a, int t_b );
long long m_div_int64int32( long long t_a, int t_b, int *t_r );

void m_add_intNint32( int *t_intN, int t_b, int t_N ); // t_intN += t_b
int m_add_intNintN( int *t_intaN, int* t_intbN, int t_N ); // t_intaN += t_intbN
void m_mul_intNint32( int *t_intN, int t_b, int t_N ); // t_intN *= t_b
int m_div_intNint32( int *t_intN, int t_b, int t_N ); // t_intN /= t_b
int m_shl_intN( int *t_intN, int t_N );             ; // t_intN <<= 1
int m_shr_intN( int *t_intN, int t_N );             ; // t_intN >>= 1


#define N 8
#define sN 256

int main()
{
    int l_aN[ N ] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0, 0, 0, 0 };
    int l_bN[ N ] = { 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0, 0, 0, 0 };

    char l_saN[ sN ] = "999999999999999999999999999999999999999999";
    char l_sbN[ sN ] = "111111111111111111111111111111111111111111";

    str_to_intN( l_saN, l_aN, N );
    str_to_intN( l_sbN, l_bN, N );

    m_add_intNintN( l_aN, l_bN, N );
    for ( int i = N - 1; i >= 0; i-- )
        printf( "%08X ", l_aN[ i ] );
    printf( "\n" );

    intN_to_str( l_aN, N, l_saN );
    printf( "%s\n", l_saN );

    m_shl_intN( l_bN, N );
    intN_to_str( l_bN, N, l_sbN );
    printf( "%s\n", l_sbN );

    m_shr_intN( l_bN, N );
    intN_to_str( l_bN, N, l_sbN );
    printf( "%s\n", l_sbN );


    //3^333
    printf( "Pocet bitu pro 3^3333: %f\n", 3333*log2( 3 ) );            
    printf( "Pocet dekadickych radu 3^3333: %f\n", 3333*log2( 3 ) / log2( 10 ) );

    int N3 = 170;
    int sN3 = 1600;
    int l_n3[ N3 ];
    bzero( l_n3, sizeof( l_n3 ) );
    l_n3[ 0 ] = 1; // l_n3 = 1
    for ( int i = 1; i <= 3333; i++ )
        m_mul_intNint32( l_n3, 3, N3 );

    char l_sn3[ sN3 ];
    intN_to_str( l_n3, N3, l_sn3 );
    printf( "%s\n", l_sn3 );


}

/*int mmain()
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

    return 0;
}*/
