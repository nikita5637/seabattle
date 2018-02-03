#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define fact_x 2
#define fact_y 1
#define FIELD_SIZE 15//max 18
#define COUNT_SHIPS 15//для 1 - 1, 2 - 3, 3 - 6, 4 - 10, 5 - 15, 6 - 21, 7 - 28, 8 - 36
#define MAX_SHIP_LENGTH 5
#define SYMBOL_DECK char(176)
#define SYMBOL_NOT_VISITED "."
#define SYMBOL_VISITED " "
#define SYMBOL_KILL_DECK char(15)
using namespace std;
struct POSITION
{
	unsigned short int x, y;
};
struct GOTOXYPOSITION
{
	unsigned short int x, y, factor_x, factor_y;
};
struct cell
{
	bool visited, deck;
};
enum direct {Left = 75, Right = 77, Up = 72, Down = 80};
void gotoxy(POSITION position, GOTOXYPOSITION pos)
{
  COORD scrn;    
  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
  scrn.X = pos.x + position.x * pos.factor_x;
  scrn.Y = pos.y + position.y * pos.factor_y;
  SetConsoleCursorPosition(hOuput,scrn);
}
class PLAYER
{
protected:
	bool orientation_ship;
	GOTOXYPOSITION gotoxyposition;
	POSITION begin, end;
	unsigned short int count_ships;
	void ship_selection()
	{
		for (unsigned short i = MAX_SHIP_LENGTH ; i >= 1 ; i--)
			for (unsigned short j = 1 ; j <= MAX_SHIP_LENGTH + 1 - i ; j++)
				while ((this->count_ships < COUNT_SHIPS) && (!installation_ship(i)));				
	}
	void auto_installation_ship(unsigned short int i)
	{
		if (this->orientation_ship)
			do
			{
				this->begin.x = rand() % FIELD_SIZE;
				this->begin.y = rand() % (FIELD_SIZE - i + 1);
				this->end.x = this->begin.x;
				this->end.y = this->begin.y + i - 1;
			}
			while (check_place());	
		else
			do
			{
				this->begin.x = rand() % (FIELD_SIZE - i + 1);
				this->begin.y = rand() % FIELD_SIZE;
				this->end.x = this->begin.x + i - 1;
				this->end.y = this->begin.y;
			}
			while (check_place());
	}
	virtual bool installation_ship(unsigned short int i)
	{
		return 0;
	}
	bool check_place()
	{
		POSITION tmp;
		if (orientation_ship)
		{
			tmp.x = begin.x;
			for (unsigned short int j = begin.y ; j <= end.y ; j++)
			{
				tmp.y = j;
				if (count_arround_deck(tmp))
					return true;
			}
		}
		else
		{
			tmp.y = begin.y;
			for (unsigned short int j = begin.x ; j <= end.x ; j++)
			{
				tmp.x = j;
				if (count_arround_deck(tmp))
					return true;
			}
		}
		if (check(this->begin))
			return true;
		return false;
	}
	bool shot(POSITION position)
	{
		gotoxy(position, gotoxyposition);
		if (check(position))
		{
			cout<<SYMBOL_KILL_DECK;
			FIELD[position.x][position.y].deck = false;
			return true;
		}
		cout<<SYMBOL_VISITED;
		return false;
	}
	void check_killed_ships()
	{
		for (unsigned short int i = 0; i < COUNT_SHIPS ; i++)
			if (array_ships[i][0].x != MAXUINT16)
				for (unsigned short int j = 0; j < MAX_SHIP_LENGTH; j++)
				{
					if (this->array_ships[i][j].x != MAXUINT16)
						if (this->FIELD[this->array_ships[i][j].x][this->array_ships[i][j].y].deck)
							break;
					if (j == MAX_SHIP_LENGTH - 1)
					{
						for (unsigned short int k = 0 ; k < MAX_SHIP_LENGTH ; k++)
							if (this->array_ships[i][k].x != MAXUINT16)
								print_symbol_visited_around_deck(this->array_ships[i][k]);
						for (unsigned short int k = 0 ; k < MAX_SHIP_LENGTH ; k++)
						{
							this->array_ships[i][k].x = MAXUINT16;
							this->array_ships[i][k].y = MAXUINT16;
						}	
						this->count_ships--;
					}
				}
	}
	unsigned short int count_arround_deck(POSITION position)
	{
		if (!position.x && !position.y)
			return actions_around_deck("rdl", position, false);
		if (position.x < FIELD_SIZE - 1 && !position.y)
			return actions_around_deck("rdllu", position, false);
		if ((position.x == FIELD_SIZE - 1) && (!position.y))
			return actions_around_deck("dlu", position, false);
		if ((!position.x) && (position.y == FIELD_SIZE - 1))
			return actions_around_deck("urd", position, false);
		if ((!position.x) && (position.y < FIELD_SIZE - 1))
			return actions_around_deck("urddl", position, false);
		if ((position.x < FIELD_SIZE - 1) && (position.y < FIELD_SIZE - 1))
			return actions_around_deck("lurrddll", position, false);
		if ((position.x == FIELD_SIZE - 1) && (position.y < FIELD_SIZE - 1))
			return actions_around_deck("dluur", position, false);
		if ((position.x == FIELD_SIZE - 1) && (position.y == FIELD_SIZE - 1))
			return actions_around_deck("lur", position, false);
		if ((position.x < FIELD_SIZE - 1) && (position.y == FIELD_SIZE - 1))
			return actions_around_deck("lurrd", position, false);
		return 0;
	}
	bool check(POSITION position)
	{
		if (this->FIELD[position.x][position.y].deck)
			return true;
		return false;
	};
	void print_symbol_visited_around_deck(POSITION position)
	{
		if (!position.x && !position.y)
		{
			actions_around_deck("rdl", position, true);
			return;
		}
		if (position.x < FIELD_SIZE - 1 && !position.y)
		{
			actions_around_deck("rdllu", position, true);
			return;
		}
		if ((position.x == FIELD_SIZE - 1) && (!position.y))
		{
			actions_around_deck("dlu", position, true);
			return;
		}
		if ((!position.x) && (position.y == FIELD_SIZE - 1))
		{
			actions_around_deck("urd", position, true);
			return;
		}
		if ((!position.x) && (position.y < FIELD_SIZE - 1))
		{
			actions_around_deck("urddl", position, true);
			return;
		}
		if ((position.x < FIELD_SIZE - 1) && (position.y < FIELD_SIZE - 1))
		{
			actions_around_deck("lurrddll", position, true);
			return;
		}
		if ((position.x == FIELD_SIZE - 1) && (position.y < FIELD_SIZE - 1))
		{
			actions_around_deck("dluur", position, true);
			return;
		}
		if ((position.x == FIELD_SIZE - 1) && (position.y == FIELD_SIZE - 1))
		{
			actions_around_deck("lur", position, true);
			return;
		}
		if ((position.x < FIELD_SIZE - 1) && (position.y == FIELD_SIZE - 1))
		{
			actions_around_deck("lurrd", position, true);
			return;
		}
	}
	unsigned short int actions_around_deck(char * route, POSITION position, bool print) 
	{
		unsigned short int i = 0, count = 0;
		while (route[i] != '\0') 
		{
	        switch(route[i])
			{
				case 'l' :
				{
					position.x--; 
					break;
				}
				case 'u' : 
				{
					position.y--;
					break;
				}
				case 'd' : 
				{
					position.y++;
					break;
				}
				case 'r' :
				{
					position.x++;
					break;
				}
			}
			if (print)
			{
				if (!this->FIELD[position.x][position.y].visited)
				{
					this->FIELD[position.x][position.y].visited = true;
					gotoxy(position, gotoxyposition);	
					cout<<SYMBOL_VISITED;
				}
			}
			else
				if (check(position))
					count++;		
			i++;
		}
		return count;
	}
public:
	cell FIELD[FIELD_SIZE][FIELD_SIZE];
	POSITION array_ships[COUNT_SHIPS][MAX_SHIP_LENGTH];
	unsigned short int count()
	{
		return this->count_ships;
	}
};
#endif