#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void sig_handler(int signo)
{
	fprintf(stderr,"Some creative error name :P\n"); 
	exit(1);
}


int main(){

	signal(SIGSEGV,sig_handler);
	
	//your code here :P
	int a[10];
	printf("%d",a[10000000]);




	return 0;
}
