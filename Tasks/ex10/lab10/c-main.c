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
#include <strings.h>
#include <math.h>

// Variables
//
void intN_to_str( int *n, int N, char *s );
void str_to_intN( char *s, int *n, int N );

long long m_add_int64int32( long long t_a, int t_b );
long long m_mul_int64int32( long long t_a, int t_b );
long long m_div_int64int32( long long t_a, int t_b, int *t_r );

void div_intNintN( int *t_a, int *t_b, int t_N ); // t_a = t_a / t_b; t_b=zbytek
void mul_intNintN( int *t_a, int *t_b, int t_N ); // t_a *= t_b;

void m_add_intNint32( int *t_intN, int t_b, int t_N ); // t_intN += t_b
int m_add_intNintN( int *t_intaN, int* t_intbN, int t_N ); // t_intaN += t_intbN
void m_mul_intNint32( int *t_intN, int t_b, int t_N ); // t_intN *= t_b
int m_div_intNint32( int *t_intN, int t_b, int t_N ); // t_intN /= t_b
int m_shl_intN( int *t_intN, int t_N );             ; // t_intN <<= 1
int m_shr_intN( int *t_intN, int t_N );             ; // t_intN >>= 1

long long mult( int t_a, int t_b )
{
    long long l_a = t_a;
    long long l_res = 0;

    for ( int i = 0; i < sizeof( int ) * 8; i++ )
    {
        if ( t_b & 1 )
            l_res += l_a;
        l_a <<= 1;
        t_b >>= 1; 
    }
    return l_res;
}

// N-bitu = |t_a|+|t_b|
// mul_intNint32 -> t_a*t_b -> t_a*t_b[0]*2^0 + t_a*t_b[1]*2^32 + t_a*t_b[2]*2^64 ...

int div( int t_a, int t_b, int *t_zbytek )
{
    long long l_divadlo = 0; // cislo dvojnasobne velikost
    int l_res = 0;
    int *l_p_divadlo = ( int * ) &l_divadlo;

    l_p_divadlo[ 0 ] = t_a; // delenec
    l_p_divadlo[ 1 ] = 0;   // scena zacina uprostred divadla

    for ( int i = 0; i < sizeof( int ) * 8; i++ )
    {
        l_divadlo <<= 1;    // vystrcime 1 bit na scenu
        l_res <<= 1;
        if ( l_p_divadlo[ 1 ] >= t_b )
        {
            l_res |= 1;     // l_res[ 0 ] |= 1
            l_p_divadlo[ 1 ] -= t_b;
        }
    }
    if ( t_zbytek ) *t_zbytek = l_p_divadlo[ 1 ];
    return l_res;
}


#define eNstr 10002
#define eN    1040

int main()
{
//    Z = 10^K
//    Z * e = suma( Z / n! ) = Z / 1 + Z / 2 + Z / 6 ....
//
    int l_eN[ eN ], l_ZN[ eN ], l_fakt[ eN ], l_tmp1[ eN ], l_tmp2[ eN ];
    char l_eNstr[ eNstr ], l_ZNstr[ eNstr ];

    memset( l_ZNstr, '0', sizeof( l_ZNstr ) );
    l_ZNstr[ eNstr - 1 ] = 0; // konec retezce
    l_ZNstr[ 0 ] = '1';
    str_to_intN( l_ZNstr, l_ZN, eN );

    memset( l_fakt, 0, sizeof( l_fakt ) ); // l_fakt = 0
    l_fakt[ 0 ] = 1;                        // l_fakt = 1
    
    memcpy( l_eN, l_ZN, sizeof( l_ZN ) );
    m_add_intNintN( l_eN, l_ZN, eN );         // e = Z + Z

    for ( int n = 2; n < 1000; n++ )
    {
        m_mul_intNint32( l_fakt, n, eN );
        //l_Z/l_fakt
        memcpy( l_tmp1, l_ZN, sizeof( l_ZN ) );
        memcpy( l_tmp2, l_fakt, sizeof( l_fakt ) );
        div_intNintN( l_tmp1, l_tmp2, eN ); // Z/n!
        add_intNintN( l_eN, l_tmp1, eN );   // e += Z/n!
    }

    intN_to_str( l_eN, eN, l_eNstr );
    printf( "e=%s\n", l_eNstr );


}


int mmmmain()
{
    long long l_tmp = mult( 999999999, 1000 );
    printf( "mult %lld 0x%llX\n", l_tmp, l_tmp);

    int l_res, l_mod;
    l_res = div( 1000000000, 3, &l_mod );
    printf( "div %d mod %d\n", l_res, l_mod );
}



#define N 8
#define sN 256

int mmain()
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

    return 0;

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
