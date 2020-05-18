all: clean v1 v2

v1: execute
	gcc -o v1 v1.c ProcessHandling.c
	

execute: 
	gcc -o execute ExecProgram.c ProcessHandling.c 


v2:	
	gcc -o v2 v2.c ProcessHandling.c


clean:
	rm -f v1 v2 execute
