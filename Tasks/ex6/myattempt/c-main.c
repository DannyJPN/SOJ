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

// Variables
//
long longsum( int* nums, int N );
long longaverage( int* nums, int N );


unsigned long long qwordbitset(char*bits,int size);
long changenibbles(long num);
void pos_neg(long *nums,int size,int* counts);
void changecase(char* chars,int upper);


int main()
{
    int N = 10;
    char cs[ 10 ] = "aaaaAAaaa";
   int numbers[10] = {45,-8,4,-5,-7,-8,5,5,1,2};
   long longnumbers[10] = {45,-8,4,-5,-7,-8,5,5,1,2};
   
   long nib = 0x1F751312ABCDEF14;
   int upper=1;
   char bits[10] = {3,1,63,62,61,2,0,60,15,16};
   int counts[2] = {0,0};
   printf("START\n");
   pos_neg(longnumbers,N,counts);
   printf( "P: %d N: %d\n",counts[0],counts[1] );   
   for(int i = 0;i<N;i++)
   {
	printf("%d,",numbers[i]);   
	}
   printf( " : %d\n", longsum( numbers, N) );
    printf( "Qword : %016llx\n", qwordbitset( bits, N) );
    printf( "%016lx : %016lx\n",nib, changenibbles( nib ) );
   printf( "%s : ",cs );
   changecase( cs,upper);
   printf( "%s \n",cs);
    
    
}
