//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// daniel.krupa@vsb.cz, Department of Computer Science, VSB-TUO
//
// Empty project
//
//***************************************************************************

#include <stdio.h>
#include <string.h>

 long palindrom(unsigned long num);
int maxdeviation( int *t_array, int t_N );
int isprime(long number);
void onlyprimes(long * nums,int count);
char *no_chars( char *t_str ,char *t_remove);

// Variables
//
int main()
{
	int snums[10] = {11,13,2,4,5,4,7,17,8,9};
	long nums[10] = {11,13,2,4,5,1,7,17,8,9};
	int N= 10;
	char str []="Jachc1 d0m 21 a rychl3";
	char torem []= "acd";
	unsigned long num = 0x8000000000000001;
	long prime = 32;
	
	
	
	printf("%016lX : %016lX\n",num,palindrom(num));
	printf("Maxdev = %d \n",maxdeviation(snums,N));
	
	printf("%lu prime = %d\n",prime,isprime(prime));
	for(int i = 0;i < N;i++)
	{
			printf("%lu,",nums[i]);
	}printf("\n");
	onlyprimes(nums,N);
	for(int i = 0;i < N;i++)
	{
			printf("%lu,",nums[i]);
	}printf("\n");
	printf("%s  ->",str);
	
	printf(" -%s-\n",no_chars(str,torem));
	//printf(" %d\n",(int)no_chars(str,torem));
	
}
