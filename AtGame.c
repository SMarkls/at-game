#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

void setcur(int x, int y) // fucntion, which refresh play field
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


int main()
{
	/*
	TODO:
	 * изменяемый размер поля			[A; B] A+rand()%(B - A + 1)
	 * случайная генерация стен
	 */


	srand(time(NULL));
	int dx, dy; // delta x and delta y, generates in range [-1; 1]
	int x, y; // current coordinates of marker
	int ax, ay; // coordinaes of point
	int ox, oy; // previous coordinates of marker
	int counter = 0; // count of collecteed points
	int selector; // chooses which coordinate should change 0 - x, 1 - y
	char key; // key entered
	char field[10][21]; // initializing playing field  10 21
	ax = 1 + rand() % (21 - 1);
	ay = 1 + rand() % (10 -1);
	y = 1 + rand() % (10 - 1);
	x = 1 + rand() % (21 - 1);
	while (x == ax && y == ay) { 
		ay = 1 + rand() % (10 - 1);
		ax = 1 + rand() % (21 - 1);
	}
	do {

		sprintf(field[0], "####################");
		sprintf(field[10], "####################");
		for (int i = 1; i < 10; i++)
			sprintf(field[i], "#                  #");
		field[y][x] = '@'; // marker
		field[ay][ax] = '*'; // point
		dx = -1 + rand() % (1 + 1 + 1);
		dy = -1 + rand() % (1 + 1 + 1);
		selector = rand() % 2;
		ox = ax;
		oy = ay;
		if (selector==1) ay += dy;
		else ax += dx;
		if (field[ay][ax] == '#') {
			ax = ox;
			ay = oy;
		}
		setcur(0, 0);
		printf("For exit press Q...\nUse WASD to move.\n");
		for (int i = 0; i < 11; i++)
			printf("%s\n", field[i]);
		ox = x;
		oy = y;
		printf("Points collected: %d\n", counter);
		key = _getch();
		if (key == 'w') y--;
		if (key == 's') y++;
		if (key == 'a') x--;
		if (key == 'd') x++;
		if (field[y][x] == '#') {
			x = ox;
			y = oy;
		}
		if (field[y][x] == '*') {
			counter++;
			ax = rand() * 1.0 / RAND_MAX * 17 + 1;
			ay = rand() * 1.0 / RAND_MAX * 8 + 1; 
			while (x == ax && y == ay) {
				y = rand() * 1.0 / RAND_MAX * 8 + 1;
				x = rand() * 1.0 / RAND_MAX * 17 + 1;
			}
		}
		if (ax == x && ay == y) {
			counter++;
			ax = rand() * 1.0 / RAND_MAX * 17 + 1;
			ay = rand() * 1.0 / RAND_MAX * 8 + 1;
		}
	} while (key != 'q');

	return 0;
}