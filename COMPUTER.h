#include "Player.h"
class COMPUTER : public PLAYER
{
private:
	POSITION position_for_smart_shot;
	unsigned short int smart_direct;
	bool smart_move, certain_direction;
	unsigned short int count_diagonal()
	{
		unsigned short int count = 0;
		for (unsigned short int i = 0 ; i < FIELD_SIZE ; i++)
			for (unsigned short int j = 0 ; j < FIELD_SIZE ; j++)
				if (i % 2)
				{
					if (j % 2)
						if (!this->FIELD[i][j].visited)
							count++;
				}
				else
				{
					if (!(j % 2))
						if (!this->FIELD[i][j].visited)
							count++;
				}					
		return count;
	}
	void smart_position()
	{
		if (this->smart_direct == 1)
		{
			if (this->position_for_smart_shot.y)
			{
				this->position_for_smart_shot.y--;
				return;
			}
			this->smart_direct = (rand() % 4) + 1;
		}
		if (this->smart_direct == 2)
		{
			if (this->position_for_smart_shot.y < FIELD_SIZE - 1)
			{
				this->position_for_smart_shot.y++;
				return;
			}
			this->smart_direct = (rand() % 4) + 1;
		}
		if (this->smart_direct == 3)
		{
			if (this->position_for_smart_shot.x)
			{
				this->position_for_smart_shot.x--;
				return;
			}
			this->smart_direct = (rand() % 4) + 1;;
		}
		if (this->smart_direct == 4)
		{
			if (this->position_for_smart_shot.x < FIELD_SIZE - 1)
			{
				this->position_for_smart_shot.x++;
				return;
			}
			this->smart_direct = (rand() % 4) + 1;
		}
	}
	bool installation_ship(unsigned short int i)
 	{
		this->orientation_ship = rand() % 2;//0 - horizontal, 1 - vertical
		unsigned short int k = 0;
		auto_installation_ship(i);
		if (this->orientation_ship)
		{
			for (unsigned short j = this->begin.y ; j <= this->end.y ; j++)
			{
				this->FIELD[this->begin.x][j].deck = true;
				this->array_ships[this->count_ships][k].x = this->begin.x;
				this->array_ships[this->count_ships][k].y = j;
				k++;
			}	
		}		
		else
		{
			for (unsigned short j = this->begin.x ; j <= this->end.x ; j++)
			{
				this->FIELD[j][this->begin.y].deck = true;
				this->array_ships[this->count_ships][k].x = j;
				this->array_ships[this->count_ships][k].y = this->begin.y;
				k++;
			}
		}	
		this->count_ships++;
		return true;
	}
public:
	COMPUTER(GOTOXYPOSITION pos)
	{
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
		this->smart_move = false;
		this->smart_direct = 1;
		this->certain_direction = false;
	}	
	bool step()
	{
		unsigned short int tmp_count_ships = this->count_ships;
		if (this->smart_move)
		{
			do
			{
				smart_position();
				if (this->FIELD[this->position_for_smart_shot.x][this->position_for_smart_shot.y].visited)
				{
					this->position_for_smart_shot = this->begin;
					if (this->certain_direction)
					{
						this->smart_direct = (rand() % 4) + 1;
					}
					else
					{
						if (this->certain_direction)
						{
							if (this->smart_direct == 1)
							{
								this->smart_direct = 2;
								return false;
							}
							else
								if (this->smart_direct == 2)
								{
									this->smart_direct = 1;
									return false;
								}
								else
								if (this->smart_direct == 3)
								{
									this->smart_direct = 4;
									return false;
								}
								else
									if (this->smart_direct == 4)
									{
										this->smart_direct = 3;
										return false;
									}
						}
						else
						{
							this->smart_direct = (rand() % 4) + 1;
						}
					}
				}
			}
			while (this->FIELD[this->position_for_smart_shot.x][this->position_for_smart_shot.y].visited);
			this->FIELD[position_for_smart_shot.x][position_for_smart_shot.y].visited = true;
			if (shot(position_for_smart_shot))
			{	
				this->certain_direction = true;
				check_killed_ships();
				if (this->count_ships < tmp_count_ships)
				{
					this->smart_move = false;
					this->certain_direction = false;
				}
				return true;
			}
			else
			{
				this->position_for_smart_shot = this->begin;
				if (this->certain_direction)
				{
					if (this->smart_direct == 1)
					{
						this->smart_direct = 2;
						return false;
					}
					if (this->smart_direct == 2)
					{
						this->smart_direct = 1;
						return false;
					}
					if (this->smart_direct == 3)
					{
						this->smart_direct = 4;
						return false;
					}
					if (this->smart_direct == 4)
					{
						this->smart_direct = 3;
						return false;
					}
				}
			}
		}
		else
		{
			do
			{
				bool z = rand() % 2;
				if (z)
				{
					if (count_diagonal())
					{
						bool q = rand() % 2;
						if (q)
							do
							{
								this->begin.x = rand() % FIELD_SIZE;
								this->begin.y = rand() % FIELD_SIZE;
							}
							while ((begin.x % 2) || (begin.y % 2));
						else
							do
							{
								this->begin.x = rand() % FIELD_SIZE;
								this->begin.y = rand() % FIELD_SIZE;
							}
							while (!(begin.x % 2) || !(begin.y % 2));
					}
					else
					{
						this->begin.x = rand() % FIELD_SIZE;
						this->begin.y = rand() % FIELD_SIZE;
					}
				}
				else
				{
					this->begin.x = rand() % FIELD_SIZE;
					this->begin.y = rand() % FIELD_SIZE;
				}
			}
			while (this->FIELD[this->begin.x][this->begin.y].visited);
			this->FIELD[begin.x][begin.y].visited = true;
			if (shot(begin))
			{		
				this->smart_move = true;
				this->position_for_smart_shot = begin;
				check_killed_ships();
				if (this->count_ships < tmp_count_ships)
					this->smart_move = false;
				return true;
			}
		}		
		return false;
	}
};