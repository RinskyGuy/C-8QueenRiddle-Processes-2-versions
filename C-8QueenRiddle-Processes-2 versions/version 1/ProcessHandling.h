/*
 * ProcessHandling.h
 *
 *  Created on: 22 Nov 2019
 *      Author: Ido Zada (203531058) & Guy Rinsky (205701907)
 */

#ifndef PROCESSHANDLING_H_
#define PROCESSHANDLING_H_

#define NUM_OF_PROCESS 4

#define NUMBER_OF_CHARS 1000
#define NUMBER_OF_FIX_CHARS 64


#define SIZE 8

typedef enum {
	NEGATIVE, POSITIVE
} check;


int checkRowQueen(char *arr);
int checkColQueen(char *arr);
int counter(char* fix_chess);
int Check_Diaganol_Left(char* chess);
void Rotate(char* matrix,char* s);
void swapRound(char* tL, char* tR, char* dR, char* dL, char* temp);
int chess_is_legal(char* chess , char type);

int fixChessBoard(char* chess, char* fix_chess);




#endif /* PROCESSHANDLING_H_ */
