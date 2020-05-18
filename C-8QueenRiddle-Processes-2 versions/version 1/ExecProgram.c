/*
 * ExecProgram.c
 *
 *  Created on: 22 Nov 2019
 *      Author: Ido Zada (203531058) & Guy Rinsky (205701907)
 */




#include <sys/unistd.h>

#include "ProcessHandling.h"
#include "ErrorManagement.h"

#define RES_OK 0b1111111110

#define CHESS_SIZE 64


int main(int args, const char* argv[])
{
	char res,i;
	for(res = 0;;)
	{
		char chess[CHESS_SIZE] = {0};
		check_error((i = read(STDIN_FILENO, chess, CHESS_SIZE)),argv[0],READ_ERR);
		if(i == 0)
			return 0;
		res = args > 1 ? chess_is_legal(chess,*(argv[1])-'0') : 0;
		check_error(write(STDOUT_FILENO,&res,1),argv[0],WRITE_ERR);
	}
	return 0;
}
