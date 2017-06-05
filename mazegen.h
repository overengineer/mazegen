#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>


char error_msg[500];

#define X 4
#define SIZE (2<<X)+1
#define VER 0
#define HOR 1
#define DARKNESS '.'
#define PATH 	' '
#define HWALL 	'#'
#define VWALL 	'|'
#define AVA		'o'
#define FINISH	'E'

char map[SIZE][SIZE];


void wall(int dir, int where, int from, int to);
void divide(int dir, int lux, int luy, int rdx, int rdy);
void mazegen(void);
int iswall(char c);

int yAvatar=1, xAvatar=1;

void mazegen()
{

	srand((unsigned int)time(NULL));
	//outer walls
	wall(VER, 0, 0, SIZE - 1);
	wall(VER, SIZE - 1, 0, SIZE - 1);
	wall(HOR, 0, 0, SIZE - 1);
	wall(HOR, SIZE - 1, 0, SIZE - 1);

	//recursively generate maze
	divide(VER, 0, 0, SIZE - 1, SIZE - 1);
}

void divide(int dir, int lux, int luy, int rdx, int rdy)
{
	//	getch();
	//	mazeprint();
	if (dir == VER) {
		//check base case
		if (rdy - luy<3) {
			return;
		}
		//divide the cell
		int divx = lux + (rdx - lux) / 2;
		wall(VER, divx, luy + 1, rdy - 1);
		//recursive call
		divide(HOR, lux, luy, divx, rdy);
		divide(HOR, divx, luy, rdx, rdy);
		//open a hole
		int rany;
		do {
			rany = luy + rand() % (rdy - luy);
		} while (iswall(map[rany][divx - 1]) || iswall(map[rany][divx + 1]));
		map[rany][divx] = PATH;


	}
	else {
		//check base case
		if (rdx - lux<4) {
			return;
		}
		//divide the cell
		int divy = luy + (rdy - luy) / 2;
		wall(HOR, divy, lux + 1, rdx - 1);

		//recursive call
		divide(VER, lux, luy, rdx, divy);
		divide(VER, lux, divy, rdx, rdy);
		//open a hole
		int ranx;
		do {
			ranx = lux + rand() % (rdx - lux);
		} while (iswall(map[divy - 1][ranx]) || iswall(map[divy + 1][ranx]));
		map[divy][ranx] = PATH;


	}
}

void wall(int dir, int where, int from, int to)
{
	if (dir == HOR)
		for (;from <= to;map[where][from++] = VWALL);
	else
		for (;from <= to;map[from++][where] = HWALL);
}

int iswall(char c)
{
	return (int)(c == HWALL || c == VWALL);
}

