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
extern "C" {

float f2f( float a ); // return a;
double d2d( double a );

float d2f( double a );
double f2d( float a );

double add_d( double a, double b );
float prepona( float, float );
double diskriminant( double a, double b, double c );

float soucet( float *t_pole, int t_N );
float max( float *t_pole, int t_N );

}

int main()
{
    printf( "f2f %f\n", f2f( 100 ) );
    printf( "d2d %f\n", d2d( 1000 ) );
    printf( "f2d %f\n", f2d( 10000 ) );
    printf( "d2f %f\n", d2f( 100000 ) );
    printf( "add %f\n", add_d( 100, 333 ) );
    printf( "prepona %f\n", prepona( 6, 8 ) );
    printf( "diskriminat %f\n", diskriminant( 1, 2, 3 ) );
    
    float f_pole[ 10 ] = { 11, 2, 3, 4, 15, 6, 7, 8, 9, 10 };
    printf( "soucet %f\n", soucet( f_pole, 10 ) );
    printf( "max %f\n", max( f_pole, 10 ) );

}
