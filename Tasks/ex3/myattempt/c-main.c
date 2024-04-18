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
int charsum( char* chars, int N );
unsigned int dwordbitset(char*bits,int size);
unsigned long long qwordbitset(char*bits,int size);
int changenibbles(int num);
void pos_neg(int *nums,int size,int* counts);
void changecase(char* chars,int upper);


int main()
{
    int N = 10;
    char cs[ 10 ] = "aaaaAAaaa";
   int numbers[10] = {45,-8,4,-5,-7,-8,5,5,1,2};
   int nib = 0x1F751312;
   int upper=1;
   char bits[10] = {3,1,63,62,61,2,0,60,15,16};
   int counts[2] = {0,0};
   pos_neg(numbers,N,counts);
   printf( "P: %d N: %d\n",counts[0],counts[1] );   
   
    printf( "%s : %d\n",cs, charsum( cs, N) );
    printf( "Dword: %016x\n", dwordbitset( bits, N) );
    printf( "Qword : %016llx\n", qwordbitset( bits, N) );
    printf( "%08x : %08x\n",nib, changenibbles( nib ) );
   printf( "%s : ",cs );
   changecase( cs,upper);
   printf( "%s \n",cs);
    
    
}
