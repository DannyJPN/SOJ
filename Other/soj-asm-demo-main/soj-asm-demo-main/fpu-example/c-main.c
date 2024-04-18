//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
//
// FPU unit usage examples
//
//***************************************************************************

#include <stdio.h>

// function prototypes
float add_float( float a, float b );
double add_double( double a, double b );
double area_sphere( double r );
float find_max( float *array, int N );
double array_average( double *array, int N );
double power_xy( double x, double exp );

int main()
{
    printf( "Sum of two numbers: %f\n", add_float( 11111, 22222 ) );
    printf( "Sum of two numbers: %f\n\n", add_double( 11111, 22222 ) );

    printf( "Sphere area: %f\n\n", area_sphere( 10 ) );

    float pole[ 10 ] = { 11, -8, -44, 19, 99, -6, 12, -5, 58, 28 };
    printf( "Maximum from array: %f\n\n", find_max( pole, 10 ) );

    double cisla[ 11 ] = { 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1 };
    printf( "Average of array elements: %f\n\n", array_average( cisla, 11 ) );

    printf( "Power x^y: %f\n", power_xy( 2, 8 ) );
    printf( "Power x^y: %f\n", power_xy( 27, 1.0/3 ) );

    
}

