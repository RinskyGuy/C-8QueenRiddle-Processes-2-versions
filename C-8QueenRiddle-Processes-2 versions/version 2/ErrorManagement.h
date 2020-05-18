/*
 * ErrorManagement.h
 *
 *  Created on: 22 Nov 2019
 *      Author: Ido Zada (203531058) & Guy Rinsky (205701907)
 */

#ifndef ERRORMANAGEMENT_H_
#define ERRORMANAGEMENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


#define _ERROR_MSG "%s: %s Error! errono: %d\n"

#define PIPE_ERR			0
#define FORK_ERR			1
#define OPEN_ERR			2
#define CLOSE_ERR			3
#define READ_ERR			4
#define WRITE_ERR			5
#define DUP2_ERR			6
#define MMAP_ERR			7
#define MUNAP_ERR			8
#define FILE_N_F_ERR		9
#define BOARD_ERR			10

void check_error(int err, const char* name, char reason){
	const char* MSG[] = {
			"Pipe",
			"Fork",
			"Open",
			"Close",
			"Read",
			"Write",
			"Dup2",
			"Mmap",
			"Munmap",
			"File Not Found",
			"Inappropriate Board --> Terminate"
	};
	if(err >= 0)
		return;
	fprintf(stderr,_ERROR_MSG, name, MSG[(int)reason], errno);
	exit(err);
}


#endif /* ERRORMANAGEMENT_H_ */
