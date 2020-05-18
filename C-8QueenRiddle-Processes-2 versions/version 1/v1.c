/*
 * v1.c
 *
 *  Created on: 22 Nov 2019
 *      Author: Ido Zada (203531058) & Guy Rinsky (205701907)
 */


#include <stdio.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "ErrorManagement.h"
#include "ProcessHandling.h"



#define READ 0
#define WRITE 1


const char* TASKS[] = { "0", "1","2", "3"};

int main(int argc, const char* argv[]) {

	int in_pipe[2], out_pipe[SIZE], i, j, results[NUM_OF_PROCESS] = { 0 }, result = 0, pid[NUM_OF_PROCESS] =
			{ 0 };
	char chess[NUMBER_OF_CHARS], fix_chess[NUMBER_OF_FIX_CHARS];

	int std_in = -1;
	check_error(pipe(in_pipe), argv[0], PIPE_ERR);
	for (i = 0; i < NUM_OF_PROCESS; i++) {
		check_error(pipe(out_pipe + i*2),argv[0],PIPE_ERR);


		// Parent
		if ((pid[i] = fork())) {

			check_error(pid[i], argv[0], FORK_ERR);
			check_error(close(out_pipe[i * 2 + READ]), argv[0], CLOSE_ERR);
		}
		//Child
		else {

			check_error(close(in_pipe[READ]), argv[0], CLOSE_ERR);
			check_error(close(out_pipe[i * 2 + WRITE]), argv[0], CLOSE_ERR);
			if (out_pipe[i * 2 + READ] != STDIN_FILENO) {
				check_error(dup2(out_pipe[i * 2 + READ], STDIN_FILENO), argv[0],
				DUP2_ERR);
				check_error(close(out_pipe[i * 2 + READ]), argv[0], CLOSE_ERR);
			}
			if (in_pipe[WRITE] != STDOUT_FILENO) {
				check_error(dup2(in_pipe[WRITE], STDOUT_FILENO), argv[0],
						DUP2_ERR);
				check_error(close(in_pipe[WRITE]), argv[0], CLOSE_ERR);
			}
			execlp("./execute",argv[0],TASKS[i],NULL);
			check_error(-1, argv[0], FILE_N_F_ERR);
		}

	}


	check_error(close(in_pipe[WRITE]),argv[0],CLOSE_ERR);

	if(argc <= 1)
		{
			argc = 2;
			std_in = STDIN_FILENO;
		}
		for(i = 1 ; i < argc ; i++)
		{
			if(std_in != STDIN_FILENO)
				check_error((std_in = open(argv[i],O_RDONLY)),argv[0],OPEN_ERR);
			check_error(read(std_in,chess,NUMBER_OF_CHARS),argv[0],READ_ERR);
			if(std_in > 0)
				check_error(close(std_in),argv[0],CLOSE_ERR);
			check_error(fixChessBoard(chess,fix_chess),argv[0],BOARD_ERR);
			for(j = 0 ; j < NUM_OF_PROCESS ; j++)
				check_error(write(out_pipe[j*2 + WRITE],fix_chess, NUMBER_OF_FIX_CHARS),argv[0],WRITE_ERR);
			for(j = 0 ; j < NUM_OF_PROCESS ; j++)
				check_error(read(in_pipe[READ],results+j,1),argv[0],READ_ERR);
			result = results[0] && results[1] && results[2] && results[3];
			printf(result ? "%s is legal\n" : "%s is not legal\n",
				(std_in != STDIN_FILENO) ? argv[i] : "STDIN");
		}
		for(i = 0 ; i < NUM_OF_PROCESS ; i++)
			check_error(close(out_pipe[i*2 + WRITE]),argv[0],CLOSE_ERR);
		check_error(close(in_pipe[READ]),argv[0],CLOSE_ERR);
	return 0;
}
