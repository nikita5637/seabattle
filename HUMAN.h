#include "Player.h"
class HUMAN : public PLAYER
{
private:
	char c;
	GOTOXYPOSITION tmpposition;
	void print_new_ship(POSITION begin, POSITION end)
	{
		if (this->orientation_ship)	
			for (unsigned short int j = this->begin.y ; j <= this->end.y ; j++)
			{
				begin.y = j;
				gotoxy(begin, this->tmpposition);
				cout<<SYMBOL_DECK;	
			}
		else
			for (unsigned short int j = this->begin.x ; j <= this->end.x ; j++)
			{
				begin.x = j;
				gotoxy(begin, this->tmpposition);
				cout<<SYMBOL_DECK;	
			}
		gotoxy(this->begin, this->tmpposition);
	}
	void clear_old_ship(POSITION begin, POSITION end)
	{
		if (this->orientation_ship)	
			for (unsigned short int j = this->begin.y ; j <= this->end.y ; j++)
			{
				begin.y = j;
				gotoxy(begin, this->tmpposition);
				if (!this->FIELD[begin.x][begin.y].deck)
					cout<<SYMBOL_NOT_VISITED;
			}
		else
			for (unsigned short int j = this->begin.x ; j <= this->end.x ; j++)
			{
				begin.x = j;
				gotoxy(begin, this->tmpposition);
				if (!this->FIELD[begin.x][begin.y].deck)
					cout<<SYMBOL_NOT_VISITED;
			}
		gotoxy(this->begin, this->tmpposition);
	}
	bool installation_ship(unsigned short int i)
 	{
		this->orientation_ship = rand() % 2;
		auto_installation_ship(i);
		do
			do
			{
				if (this->orientation_ship)
				{
					this->end.x = this->begin.x;
					this->end.y = this->begin.y + i - 1;
				}		
				else
				{
					this->end.x = this->begin.x + i - 1;
					this->end.y = this->begin.y;
				}
				this->print_new_ship(begin, end); 
				this->c = _getch();	
				switch (this->c)
				{	
					case '0':
					{
						clear_old_ship(begin, end);
						if (this->orientation_ship)
						{
							if (this->begin.x + i > FIELD_SIZE)
								(this->begin.x = FIELD_SIZE - i);
						}
						else
						{
							if (this->begin.y + i > FIELD_SIZE)
								(this->begin.y = FIELD_SIZE - i);
						}
						this->orientation_ship = !this->orientation_ship;
						break;
					}
					case Up:
						{
							clear_old_ship(begin, end);
							if (this->begin.y > 0)
								this->begin.y--;
							break;
						}
					case Down:
						{
							clear_old_ship(begin, end);
							if (this->orientation_ship)
							{
								if (this->begin.y < FIELD_SIZE - i)
									this->begin.y++;
							}
							else
							{
								if (this->begin.y < FIELD_SIZE - 1)
									this->begin.y++;
							}
							break;
						}
					case Left:
						{
							clear_old_ship(begin, end);
							if (this->begin.x > 0)
								this->begin.x--;
							break;
						}
					case Right:
						{
							clear_old_ship(begin, end);
							if (this->orientation_ship)
							{
								if (this->begin.x < FIELD_SIZE - 1)
									this->begin.x++;
							}
							else
							{
								if (this->begin.x < FIELD_SIZE - i)
									this->begin.x++;
							}
							break;
						}
				}
			}
			while (this->c != ' ');
		while (this->check_place());
		unsigned short int k = 0;
		if (this->orientation_ship)
			for (unsigned short j = this->begin.y ; j <= this->end.y ; j++)
			{
				this->FIELD[this->begin.x][j].deck = true;
				this->array_ships[this->count_ships][k].x = this->begin.x;
				this->array_ships[this->count_ships][k].y = j;
				k++;
			}
		else
			for (unsigned short j = this->begin.x ; j <= this->end.x ; j++)
			{
				this->FIELD[j][this->begin.y].deck = true;
				this->array_ships[this->count_ships][k].x = j;
				this->array_ships[this->count_ships][k].y = this->begin.y;
				k++;
			}
		this->count_ships++;
		return true;
	}
public:
	HUMAN(GOTOXYPOSITION pos)
	{
		this->tmpposition.x = 3;
		this->tmpposition.y = pos.y;
		this->tmpposition.factor_x = pos.factor_x;
		this->tmpposition.factor_y = pos.factor_y;
		this->gotoxyposition.x = pos.x;
		this->gotoxyposition.y = pos.y;
		this->gotoxyposition.factor_x = pos.factor_x;
		this->gotoxyposition.factor_y = pos.factor_y;
		for (unsigned short int i = 0 ; i < FIELD_SIZE ; i++)
			for (unsigned short int j = 0 ; j < FIELD_SIZE ; j++)
			{
				this->FIELD[j][i].deck = false;
				this->FIELD[j][i].visited = false;
			}
		for (unsigned short int i = 0 ; i < COUNT_SHIPS ; i++)
			for (unsigned short int j = 0 ; j < MAX_SHIP_LENGTH ; j++)
			{
				this->array_ships[i][j].x = MAXUINT16;
				this->array_ships[i][j].y = MAXUINT16;
			}
		this->count_ships = 0;
		ship_selection();
		this->begin.x = 0;
		this->begin.y = 0;
	}
	bool step()
	{
		do
			do
			{
				gotoxy(this->begin, this->gotoxyposition);
				this->c = _getch();	
				switch (this->c)
				{	
					case Up:
					{
						if (this->begin.y > 0)
							this->begin.y--;
						break;
					}
					case Down:
					{
						if (this->begin.y < FIELD_SIZE - 1)
							this->begin.y++;
						break;
					}
					case Left:
					{
						if (this->begin.x > 0)
							this->begin.x--;
						break;
					}
					case Right:
					{
						if (this->begin.x < FIELD_SIZE - 1)
							this->begin.x++;
						break;
					}
				}
			}
			while (this->c != ' ');
		while (this->FIELD[this->begin.x][this->begin.y].visited);
		this->FIELD[this->begin.x][this->begin.y].visited = true;
		if (shot(begin))
		{
			check_killed_ships();
			return true;
		}
		return false;
	}
};