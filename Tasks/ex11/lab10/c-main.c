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
int shrd_test( int t_a, int t_b, int t_okolit );

int mult_fix( int t_a, int t_b, int t_fixed );
int div_fix( int t_a, int t_b, int t_fixed );

int float2fix( float t_a, int t_fixed )
{
    return t_a * ( 1 << t_fixed ); // 2**t_fixed
}

float fix2float( int t_a, int t_fixed )
{
    return ( ( float ) t_a ) / ( 1 << t_fixed );
}

#define FIXED 8


int main()
{
    printf( "0x%x\n", shrd_test( 0x11223344, 0x88776655, 8 ) );


    float l_f_pi = 3.14;
    int l_i_pi = float2fix( l_f_pi, FIXED );
    float l_f_10 = 10;
    int l_i_10 = float2fix( l_f_10, FIXED );
    printf( "pi %f\n", fix2float( l_i_pi, FIXED ) );

    int l_i_res = mult_fix( l_i_10, l_i_pi, FIXED );
    printf( "%d %f\n", l_i_res, fix2float( l_i_res, FIXED ) );

    printf( "%f\n", fix2float( mult_fix( float2fix( 0.5, FIXED ), 
                                         float2fix( 0.5, FIXED ), FIXED ), FIXED ) );
    printf( "%f\n", fix2float( div_fix( float2fix( 1, FIXED ), 
                                         float2fix( 32, FIXED ), FIXED ), FIXED ) );
}
