#include <stdio.h>

extern void compile(char * );

int	main(int argc, char * argv[]){
	if(argc == 1) compile("Test.pl0");
    else if(argc == 2)  compile(argv[1]); 
	else  printf("Syntax error \n");
 	return 0;
}
