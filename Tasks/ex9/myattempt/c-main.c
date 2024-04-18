//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// daniel.krupa.st@vsb.cz, Department of Computer Science, VSB-TUO
//
// Empty project
//
//***************************************************************************

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <math.h>

// Variables
//
void intN_to_str( int *n, int N, char *s );
void str_to_intN( char *s, int *n, int N );

//int m_add_int64int32( int t_a, int t_b );
//int m_mul_int64int32( int t_a, int t_b );
//int m_div_int64int32(  int t_a, int t_b, int *t_r );

void m_add_intNint32( int *t_intN, int t_b, int t_N ); // t_intN += t_b
int m_add_intNintN( int *t_intaN, int* t_intbN, int t_N ); // t_intaN += t_intbN
int m_sub_intNintN( int *t_intaN, int* t_intbN, int t_N ); // t_intaN -= t_intbN

void m_mul_intNint32( int *t_intN, int t_b, int t_N ); // t_intN *= t_b
int m_div_intNint32( int *t_intN, int t_b, int t_N ); // t_intN /= t_b
int m_shl_intN( int *t_intN, int t_N );             ; // t_intN <<= 1
int m_shr_intN( int *t_intN, int t_N );             ; // t_intN >>= 1
char *mirror( char *t_str );

int is_zero( int *n, int N )
{
  int i = 0;
  while ( i < N ) if ( n[ i++ ] ) return 0;
  return 1;
}


// function template for intN to string conversion

void intN_to_str( int *n, int N, char *s )
{
  int * num = (int*)malloc(N*sizeof(int));
	for(int i =0;i<N;i++)
	{
			num[i] = n[i];
	}
	
int i = 0;
  while ( !is_zero( num, N ) )
    s[ i++ ] = m_div_intNint32( num,10,N ) + '0';
    
  
  s[i] = 0;
mirror(s);
free(num);
  
}

// function template for string to intN conversion

void str_to_intN( char *s, int *n, int N )
{
  	for(int i =0;i<N;i++)
	{
			 n[i]=0;
	}
	//printf("Trasnfer\n");
  while ( *s )
  {
	//  printf("Analyzing %c\n",*s);
      m_mul_intNint32( n,10,N );
      m_add_intNint32( n,*s++ - '0',N );

	  }
  
}

#define N 8
#define sN 256

int main()
{
    int l_aN[ N ] = { 0x5454512, 0xFAC801, 0x7414, 0x0, 0, 0, 0, 0 };
    int l_bN[ N ] = { 0xFaaaa,0xFaaaa,0xf000,0,0, 0, 0, 0 };
	char I_saN[ sN ] = "";
    char I_sbN[ sN ] = "";

     printf("IAN:  ");
    for ( int i = N - 1; i >= 0; i-- )
        printf( "%08X ", l_aN[ i ] );
    printf( "\n" );
    intN_to_str( l_aN, N, I_saN );
    printf("IAN STR: %s\n",I_saN);
    
    printf("IBN:  ");
    for ( int i = N - 1; i >= 0; i-- )
        printf( "%08X ", l_bN[ i ] );
    printf( "\n" );
       intN_to_str( l_bN, N, I_sbN );
    printf("IBN STR: %s\n",I_sbN);
    

    m_add_intNintN( l_aN, l_bN, N );
    printf("SUM:  ");
    for ( int i = N - 1; i >= 0; i-- )
        printf( "%08X ", l_aN[ i ] );
    printf( "\n" );
	
    intN_to_str( l_aN, N, I_saN );
    printf("SUM STR: %s\n",I_saN);
    
    printf("IBN BEF SHL: ");
    for ( int i = N - 1; i >= 0; i-- )
        printf( "%08X ", l_bN[ i ] );
    printf( "\n" );
    m_shl_intN( l_bN, N );
    printf("IBN SHL:  ");
    for ( int i = N - 1; i >= 0; i-- )
        printf( "%08X ", l_bN[ i ] );
    printf( "\n" );
    intN_to_str( l_bN, N, I_sbN );
    printf("IBN SHL STR: %s\n",I_sbN);
    
    
    
  printf("IBN BEF SHR: ");
    for ( int i = N - 1; i >= 0; i-- )
        printf( "%08X ", l_bN[ i ] );
    printf( "\n" );
     m_shr_intN( l_bN, N );
    printf("IBN SHR:  ");
    for ( int i = N - 1; i >= 0; i-- )
        printf( "%08X ", l_bN[ i ] );
    printf( "\n" );
    intN_to_str( l_bN, N, I_sbN );
    printf("IBN SHL STR: %s\n",I_sbN);

    int base = 3;
    int power = 30;
    printf( "Pocet bitu pro %d^%d: %f\n",base,power, power*log2( base ) );            
    printf( "Pocet dekadickych radu %d^%d: %f\n",base,power, power*log2( base ) / log2( 10 ) );

    int N3 = ceil(power*log2( base )  );
    int sN3 = ceil(power*log2( base ) / log2( 10 ) );
    printf("Pocet bitu INT %d\n",N3);
    printf("Pocet dek. radu INT %d\n",sN3);
    int intsize3 = ceil(N3/(double)(sizeof(int)*8));
	printf("Pocet INTů INT %d\n",intsize3);
    
    int l_n3[ intsize3 ];
    bzero( l_n3, sizeof( l_n3 ) );
    l_n3[ 0 ] = 1; // l_n3 = 1
    for ( int i = 1; i <= power; i++ )
        m_mul_intNint32( l_n3, base, intsize3 );

    char I_sn3[ sN3 ];
    intN_to_str( l_n3, intsize3, I_sn3 );
    printf( "%s\n", I_sn3 );
    
    
    int factor = 1111;
	double bits = 0;
	for ( int i = 2; i <= factor; i++ )
	{
			bits+=log2(i);
	}
	
printf( "Pocet bitu pro %d!: %f\n",factor, bits );            
    printf( "Pocet dekadickych radu %d!: %f\n",factor,bits/ log2( 10 )  );
	int N4 = ceil(bits);
int sN4 = ceil(bits/log2( 10 ))	;
	printf("Pocet bitu INT %d\n",N4);
    printf("Pocet dek. radu INT %d\n",sN4);
	int intsize4 = ceil(N4/(double)(sizeof(int)*8));
	printf("Pocet INTů INT %d\n",intsize4);
	
    

    
    
    int l_n4[ intsize4 ];
    bzero( l_n4, sizeof( l_n4 ) );
	char I_sn4[ sN4 ];
    m_add_intNint32( l_n4,1,N );
	
    printf("I4:  ");
    for ( int i = intsize4 - 1; i >= 0; i-- )
        printf( "%08X ", l_n4[ i ] );
    printf( "\n" );
    intN_to_str( l_n4, intsize4, I_sn4 );
    printf("I4 STR: %s\n",I_sn4);	
	
	for ( int i = 2; i <= factor; i++ )
	{
		m_mul_intNint32( l_n4, i, intsize4 );	
	}
	
    printf("FACTOR:  ");
    for ( int i = intsize4 - 1; i >= 0; i-- )
        printf( "%08X ", l_n4[ i ] );
    printf( "\n" );
    intN_to_str( l_n4, intsize4, I_sn4 );
    printf("FACTOR STR: %s\n",I_sn4);	
	
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
