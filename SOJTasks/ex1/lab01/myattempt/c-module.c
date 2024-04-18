#include <stdio.h>

 
extern int	g_size;
extern int	g_top;
extern int	g_arr[];



void push(int val)
{
	if(g_top < g_size-1)
	{
		g_top++;
		g_arr[g_top]=val;	
	}
}
int pop()
{
	int retval;
	if(g_top >= 0)
	{
		retval=		g_arr[g_top];
		g_top--;
		return retval;	
	}

}

int peek()
{
if(g_top >0)
{		return g_arr[g_top];	}
else return -123456;
	

}


  
