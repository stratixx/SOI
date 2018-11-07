#include <stdio.h>
#include <lib.h>

int getprocnr( int );

int main (int argc, char* argv[])
{
	int result;
	int n;
	int arg;

	/* Brak argumentu */
	if(argc == 1)
	{
		printf("Argument needed!\n"); 
		return -1;
	}

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

	return 0;
} 

int getprocnr( int proc_idx )
{
	message msg;	
	msg.m1_i1 = proc_idx;

	return _syscall( MM, GETPROCNR, &msg ); 
	/* who, syscallnr, message_ptr */
}

