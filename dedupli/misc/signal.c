#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void *handler(){
	printf("Woken\n");
}


/**Handle a signal*/
struct sigaction handleSignal(int signal, void* handler){
	
	struct sigaction new, old;

	/*Setting new handler*/
	new.sa_handler=handler;
	sigemptyset(&new.sa_mask);
	new.sa_flags=0;
	
	/*backup old one*/
	int ret=sigaction(signal,NULL,&old);
	if(ret==-1){
		perror("Cannot backup old handler");
		exit(EXIT_FAILURE);
	}
	
	/*Changing teh handler for the given signal*/
	ret=sigaction(signal,&new,NULL);
	if(ret==-1){
		perror("Cannot change the handler");
		exit(EXIT_FAILURE);
	}	
	return old;
}


int main(){
	handleSignal(SIGCONT,handler);

	printf("a\n");
	raise(SIGSTOP);
	
	printf("b\n");

	return 0;
}


