#include <iostream>
#include "HUMAN.h"
#include "COMPUTER.h"
using namespace std;
bool who = rand() % 2;//true - человек, false - компьютер
void print_field()
{
	system("cls");	
	for (unsigned short int i = 1 ; i <= 2 ; i++)
	{
		printf("%s", "   ");
		for (unsigned short int j = 1 ; j <= FIELD_SIZE ; j++)
		{
			printf("%c", char(64 + j));
			if (j != FIELD_SIZE)
				for (unsigned short k = 1 ; k < fact_x ; k++)
					printf("%s", " ");
		}
		if (i == 1)
			for (unsigned short int q = 1 ; q <= fact_x ; q++)
				printf(" ");
	}
	for (unsigned short int i = 1; i <= fact_y ; i++)
		printf("\n");
	for (unsigned short int i = 1 ; i <= FIELD_SIZE ; i++)
	{
		for (unsigned short int z = 1 ; z <= 2 ; z++)
		{
			printf("%2d", i);
			for (unsigned short int j = 1 ; j < FIELD_SIZE ; j++)
			{
				if (j == 1)
				{
					printf("%s", " ");
					printf("%s", SYMBOL_NOT_VISITED);
				}
				for (unsigned short int k = 1 ; k < fact_x ; k++)
					printf("%s", " ");
				printf("%s", SYMBOL_NOT_VISITED);
			}
			if (z == 1)
				for (unsigned short int q = 1 ; q <= fact_x ; q++)
					printf(" ");
		}
		if (i != FIELD_SIZE)
			for (unsigned short int j = 1; j <= fact_y ; j++)
				printf("\n");
	}
}
int main()
{
	srand(unsigned(time(0)));
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0xf0);//3f);
	while (1)
	{
		print_field();
		GOTOXYPOSITION hum, comp;
		hum.x = (3 + (FIELD_SIZE * fact_x) + 1 + 3);
		hum.y = fact_y;
		hum.factor_x = fact_x;
		hum.factor_y = fact_y;
		comp.x = 3;
		comp.y = fact_y;
		comp.factor_x = fact_x;
		comp.factor_y = fact_y;
		HUMAN human(hum);		
		COMPUTER computer(comp);
		for (unsigned short int i = 0 ; i < COUNT_SHIPS ; i++)
			for (unsigned short int j = 0 ; j < MAX_SHIP_LENGTH ; j++)
			{
				unsigned short int x, y;
				x = human.array_ships[i][j].x;
				y = human.array_ships[i][j].y;
				human.array_ships[i][j].x = computer.array_ships[i][j].x;
				human.array_ships[i][j].y = computer.array_ships[i][j].y;
				computer.array_ships[i][j].x = x;
				computer.array_ships[i][j].y = y;
			}
		cell tmp;
		for (unsigned short int i = 0 ; i < FIELD_SIZE ; i++)
			for (unsigned short int j = 0 ; j < FIELD_SIZE ; j++)
			{	
				tmp = human.FIELD[j][i];
				human.FIELD[j][i] = computer.FIELD[j][i];
				computer.FIELD[j][i] = tmp;
			}
		while (human.count() && computer.count())
			if (who)
			{
				if (!human.step())
					who = false;
			}
			else
			{
				Sleep(200);
				if (!computer.step())
					who = true;
			}
		POSITION print_position;
		print_position.x = 0;
		print_position.y = (FIELD_SIZE * fact_y) + 1;
		GOTOXYPOSITION tmpposition;
		tmpposition.x = 0;
		tmpposition.y = 0;
		tmpposition.factor_x = 1;
		tmpposition.factor_y = 1;
		gotoxy(print_position, tmpposition);
		(who) ? printf("%c%c%c%s%c%c%c\n", char(1), char(1), char(1), " YOU WIN!!! ", char(1), char(1), char(1)) : printf("%s\n", "YOU LOSE!:(:(:(");
		Sleep(2000);
		system("pause");
	}
}