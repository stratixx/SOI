#include <stdio.h>
#include <lib.h>
#include "../inc/main.h"

/*int get_subpriority(void);*/
void set_subpriority( int );
int main_child(int);
void fork_child(int);

int main (int argc, char* argv[])
{
	int normal = 2;
	int background = 3;

	/* Brak argumentu */
	if(argc <= 2)
	{
		printf("Two argument needed!\n"); 
		return -1;
	}

	normal = atoi(argv[1]);
	background = atoi(argv[2]);

	for(;background>0; --background)
		fork_child(PSPRI_BACKGROUND);
	for(;normal>0; --normal)
		fork_child(PSPRI_NORMAL);

	return 0;
} 

int main_child(int subpriority)
{
	int n = 5;
	long unsigned k;
	char * normal = 	"NORMAL    ";
	char * background = "BACKGROUND";
	char * wsk = subpriority==1?normal:background;

	printf("__%s start: PID=%d;__\n", wsk, getpid());

	for(n=0;n<50;++n)
	{
		printf("__%s loop : PID=%d;__\n", wsk, getpid());
		for(k=0; k<(1000000/subpriority); ++k);
	}

	printf("__%s end  : PID=%d;__\n", wsk, getpid());
	return 0;
}

void fork_child(int subpriority)
{
	int res=1;
	if( fork()==0 )
	{
		set_subpriority(subpriority); /* new subpriority to child */
		exit(main_child(subpriority));
	}
	/* only parrent will return from function */
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
