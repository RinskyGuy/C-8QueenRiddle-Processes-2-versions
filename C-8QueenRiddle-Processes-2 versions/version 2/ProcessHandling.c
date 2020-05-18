/*
 * ProcessHandling.c
 *
 *  Created on: 22 Nov 2019
 *      Author: Ido Zada (203531058) & Guy Rinsky (205701907)
 */



#include <stdlib.h>
#include <stdio.h>
#include "ProcessHandling.h"
#include <string.h>
#include <math.h>
int checkRowQueen(char *arr) {
	int rows = SIZE;
	int colls = SIZE;
	char *p = arr;
	char c;
	int i, j;
	int qCounter = 0;

	for (i = 0; i < rows; i++) {
		check isCheck = NEGATIVE;
		for (j = 0; j < colls; j++) {
			c = *p;
			if (c == 'Q') { //Checking if there is a queen
				qCounter++;
				if (isCheck == NEGATIVE) { //Checks if a queen has never been identified
					isCheck = POSITIVE; // //There is one queen
				} else {
					return 0; //There is more than one queen return 0
				}
			}
			p++;
		}
		if(qCounter != 1){
			return 0;
		}
		qCounter = 0;
	}
	return 1;
}

int checkColQueen(char *arr) {
	int rows = SIZE;
	int colls = SIZE;
	char *p = arr;
	char *k = arr;
	char c;
	int i, j;
	int qCounter = 0;
	for (j = 0; j < colls; j++) {
		check isCheck = NEGATIVE;
		for (i = 0; i < rows; i++) {
			c = *p;
			if (c == 'Q') { //Checking if there is a queen
				qCounter++;
				if (isCheck == NEGATIVE) { //Checks if a queen has never been identified
					isCheck = POSITIVE; // //There is one queen
				} else {
					return 0; //There is more than one queen return 0
				}
			}
			p += 8;
		}
		k++;
		p = k;
		if(qCounter != 1){
			return 0;
		}
		qCounter = 0;
	}

	return 1;
}

int fixChessBoard(char* chess, char* fix_chess) {
	int i, j = 0;
	for (i = 0; i < NUMBER_OF_CHARS && j <= 63; i++) {
		if (('a' <= *(chess + i) && *(chess + i) <= 'z')
				|| ('A' <= *(chess + i) && *(chess + i) <= 'P')
				|| ('R' <= *(chess + i) && *(chess + i) <= 'Z')) {
			return -1;
		}
		if ((*(chess + i) == 'Q') || (*(chess + i) == '.')) {
			*(fix_chess + j) = *(chess + i);
			j++;
		}
	}
	if (counter(fix_chess) == NUMBER_OF_FIX_CHARS) {
		return 0;
	} else
		return -1;

}

int Check_Diaganol_Left(char* chess) {
	int diag_check[13] = { 0 }, row, col, place;
	for (row = 0; row < SIZE; row++) {
		for (col = 0; col < SIZE; col++) {
			if (*(chess + (row * SIZE + col)) == 'Q') {
				place = col - 1 + row - 1;
				if (diag_check[place]) {
					return 0;
				}
				diag_check[place] = 1;
			}

		}
	}
	return 1;
}

//Rotate's the board 90 degrees counter clockwise
void Rotate(char* matrix,char* s) {
	strcpy(s,matrix);
	int i;
	int j;
	for (i = 0; i < SIZE; i++) {
		for (j = i; j < SIZE - i - 1; j++) {
			char temp = *(s + i * SIZE + j);
			char* topLeft = (s + i * SIZE + j);
			char* topRight = (s + j * SIZE + SIZE - 1 - i);
			char* downRight = (s + (SIZE - 1 - i) * SIZE + SIZE - 1 - j);
			char* downLeft = (s + (SIZE - 1 - j) * SIZE + i);
			swapRound(topLeft, topRight, downRight, downLeft, &temp);
		}
	}
}
//Swap's between the values of the edges to rotate the matrix
void swapRound(char* tL, char* tR, char* dR, char* dL, char* temp) {
		*tL = *tR;
		*tR = *dR;
		*dR = *dL;
		*dL = *temp;
}
//Check's the amount  of the chars 'Q' and '.' in the matrix
int counter(char* fix_chess) {
	int i;
	int counter = 0;
	for (i = 0; i < NUMBER_OF_FIX_CHARS; i++) {
		if ((*(fix_chess + i) == 'Q') || (*(fix_chess + i) == '.')) {
			counter++;
		}
	}
	return counter;
}

int chess_is_legal(char* chess, char type) {
	check c;
	char temp[NUMBER_OF_FIX_CHARS];
	switch (type) {
	case 0:
		c = checkRowQueen(chess);
		if (c == POSITIVE) {
			return 1;
		}
		break;
	case 1:
		c = checkColQueen(chess);
		if (c == POSITIVE) {
			return 1;
		}
		break;
	case 2:
		c = Check_Diaganol_Left(chess);
		if (c == POSITIVE) {
			return 1;
		}
		break;
	case 3:
		Rotate(chess,temp);
		c = Check_Diaganol_Left(temp);
		if (c == POSITIVE) {
			return 1;
		}
		break;
	}
	return 0;

}

