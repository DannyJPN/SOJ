//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// daniel.krupa.st@vsb.cz,  VSB-TUO
//
// Empty project
//
//***************************************************************************

#include <stdio.h>
#include <string.h>


void move_mem( void *t_dest, void *t_str, int t_len );
void removenum(char*arr);
int str_comp(char* s1,char* s2);
int occurrence_count(int*arr,int num,int len);
// Variables
//
int main()
{

    char nazdar[ 128 ] = "Ahoj programatori!";
char numstr [] = "9J4 chc1 d0m!!!";

	int result = str_comp(nazdar,numstr);
	int arr[11] = {4,5,7,8,4,2,1,5,4,2,1};
	printf("<%s> - <%s>  = %d\n",nazdar,numstr,result);
    for(int i = 0;i<11;i++)
	{printf("%d,",arr[i]);}
	printf("\n");
	int search = 1;
	printf("Number  %d contained %d x\n",search,occurrence_count(arr,search,11));
	
	
	move_mem( nazdar, nazdar+2, strlen( nazdar )  +1);
    //memcpy( nazdar+2, nazdar, strlen( nazdar )  +1);
	printf( "move '%s'\n", nazdar );
	removenum(numstr);
	printf( "numstr '%s'\n", numstr );
	
   
}

