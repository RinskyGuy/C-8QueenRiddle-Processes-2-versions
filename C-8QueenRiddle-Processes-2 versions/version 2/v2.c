/*
 * v2.c
 *
 *  Created on: 29 Nov 2019
 *      Author: Ido Zada (203531058) & Guy Rinsky (205701907)
 */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include "ProcessHandling.h"
#include "ErrorManagement.h"
typedef struct {
	char board[NUMBER_OF_FIX_CHARS];
	int status[NUM_OF_PROCESS];
	int ready_to_start;
	int ready_to_die;
	int ready_for_result[NUM_OF_PROCESS];
} shared_mem;

int main(int argc, const char* argv[]) {
	shared_mem* mem_data;
	char chess[NUMBER_OF_CHARS];
	int i,j;
	int pid[NUM_OF_PROCESS] = { 0 };
	int res,std_in = -1;
	mem_data = (shared_mem*) mmap(NULL, sizeof(shared_mem), PROT_READ | PROT_WRITE,MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	mem_data->ready_to_die = 0;
	mem_data->ready_to_start = 0;
	mem_data->ready_for_result[0] = mem_data->ready_for_result[1] = mem_data->ready_for_result[2] = mem_data->ready_for_result[3] = 0;
	if (mem_data <= 0)
		check_error(-1, argv[0], MMAP_ERR);

	for (i = 0; i < NUM_OF_PROCESS; i++) {

		if (!(pid[i] = fork())) {
			//child
			for (;;) {
				while (!(mem_data->ready_to_start)){
						if(mem_data->ready_to_die)
							exit(0);
				}
				mem_data->status[i] = chess_is_legal(mem_data->board, i);
				mem_data->ready_for_result[i] = 1;
				while(mem_data->ready_to_start);
			}
		}
		//Parent
		check_error(pid[i], argv[0], FORK_ERR);
	}


	if(argc <= 1)
	{
		argc = 2;
		std_in = STDIN_FILENO;
	}
	for(i = 1 ; i < argc ; i++)
	{
		mem_data->ready_for_result[0] = mem_data->ready_for_result[1] = mem_data->ready_for_result[2] = mem_data->ready_for_result[3] = 0;
		if(std_in != STDIN_FILENO && (std_in = open(argv[i],O_RDONLY)) < 0)
		{
			mem_data->ready_to_die = 1;
			check_error(std_in,argv[0],OPEN_ERR);
		}
		if(read(std_in,chess,NUMBER_OF_CHARS) < 0)
		{
			mem_data->ready_to_die = 1;
			check_error(-1,argv[0],READ_ERR);
		}
		check_error(fixChessBoard(chess,mem_data->board),argv[0],BOARD_ERR);
		mem_data->ready_to_start = 1;
		for(j = 0 ; j < NUM_OF_PROCESS ; j++)
					while(!mem_data->ready_for_result[j]);
		mem_data->ready_to_start = 0;
		res = mem_data->status[0] && mem_data->status[1] && mem_data->status[2] && mem_data->status[3];
		printf(res ? "%s is legal\n" : "%s is not legal\n",
				(std_in != STDIN_FILENO) ? argv[i] : "STD_ID");
	}
	mem_data->ready_to_die = 1;
	// Make sure there are no survivors...
	for(i = 0 ; i < NUM_OF_PROCESS ; i++)
		wait(NULL);
	check_error(munmap(mem_data,sizeof(shared_mem)),argv[0],MUNAP_ERR);
	exit(0);

}
