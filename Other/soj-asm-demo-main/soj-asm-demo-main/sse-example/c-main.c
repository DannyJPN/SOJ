//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
//
// SSE unit usage examples
//
//***************************************************************************

#include <stdio.h>

float add_float( float a, float b );
double add_double( double a, double b );
double volume_sphere( double r );
float find_max( float *array, int N );
double array_average( double *array, int N );

int main()
{
    printf( "Adding two numbers: %f\n", add_float( 11111, 22222 ) );
    printf( "Adding two numbers: %f\n\n", add_double( 11111, 22222 ) );

    printf( "Volume of sphere %f\n", volume_sphere( 10 ) );

    float array[ 10 ] = { 11, -8, -44, 19, 99, -6, 12, -5, 58, 28 };
    printf( "Found maximum is: %f\n\n", find_max( array, 10 ) );

    double numbers[ 11 ] = { 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1 };
    printf( "Average of array elements: %f\n\n", array_average( numbers, 11 ) );
    
}

