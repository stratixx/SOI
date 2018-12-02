#include <stdio.h>
#include <lib.h>
#include "../inc/main.h"

/*int get_subpriority(void);*/
void set_subpriority( int );

int main (int argc, char* argv[])
{
	int result;
	int n;
	int arg;

	set_subpriority(PSPRI_NONE);
	set_subpriority(PSPRI_NORMAL);
	set_subpriority(PSPRI_BACKGROUND);
	set_subpriority(3);
	set_subpriority(4);

	/* Brak argumentu */
	if(argc == 1)
	{/*
		printf("Argument needed!\n"); 
		return -1;*/
	}
/*
	arg = atoi(argv[1]);
	for(n=0;n<10;n++)
	{
		result = getprocnr(arg+n);
		printf("PID: %d --> index: ", arg+n);
		if(result !=-1) 
			printf("%d\n",result);
		else 
			printf("NOT FOUND!, ERROR: %d\n",errno);
	}
*/
	for(n=0; n<1000000; ++n)
		arg = n;
	return 0;
} 

void set_subpriority( int subpriority )
{
	message msg;
	int result;	
	msg.m1_i2 = subpriority;
	result = _syscall( MM, 80, &msg ); 
	/*printf("set_spri: result=%d; spri_in=%d\n", msg.m_type, subpriority);*/
	/*printf("setpspri: result=%d; m_type=%d; m1_i1=%d; m1_i2=%d; m1_i3=%d;\n", result, msg.m_type, msg.m1_i1, msg.m1_i2, msg.m1_i3 );
*/
}
/*
int get_subpriority(void)
{
	message msg;
	int result;	

	result = _syscall( MM, 79, &msg ); 
	printf("getpspri: result=%d; m_type=%d; m1_i1=%d; m1_i2=%d; m1_i3=%d;\n", result, msg.m_type, msg.m1_i1, msg.m1_i2, msg.m1_i3 );


	return msg.m1_i2;
}
*/
