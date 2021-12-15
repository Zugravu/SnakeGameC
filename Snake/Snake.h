#include <Windows.h>

#define Width 50
#define Height 25

class Snake
{
private:
	COORD pos;
	int len;
	int speed;
	char direction;
	int tailX[1000];
	int tailY[10001];
public:
	Snake(COORD position, int sp) : pos(position), speed(sp), len(1), direction('n'){}
	void Change_Direction(char dir) { direction = dir; }
	void Move()
	{
		switch (direction)
		{
			case 'u': pos.Y -= speed; break;
			case 'd': pos.Y += speed; break;
			case 'l': pos.X -= speed; break;
			case 'r': pos.X += speed; break;
		}
	}
	COORD Get_Pos() { return pos; }
	int Get_Len() { return len; }
	int Get_TailX(int i) { return tailX[i]; }
	int Get_TailY(int i) { return tailY[i]; }
	void Set_TailX() { tailX[0] = 0; }
	void Set_TailY() { tailY[0] = 0; }
	bool eaten(COORD food_pos)
	{
		if (pos.X == food_pos.X && pos.Y == food_pos.Y)
			return true;
		return false;
	}
	void Grow()
	{
		len++;

	}
	void Tail()
	{
		int a = tailX[0];
		int b = tailY[0];
		int a1, b1;
		tailX[0] = pos.X;
		tailY[0] = pos.Y;
		for (int i = 1; i < len; i++)
		{
			a1 = tailX[i];
			b1 = tailY[i];
			tailX[i] = a;
			tailY[i] = b;
			a = a1;
			b = b1;
		}
	}
	bool Collide()
	{
		if (pos.X < 1 || pos.X > Width || pos.Y < 1 || pos.Y > Height)
			return true;
		for (int i = 1; i <= len; i++)
		{
			if (tailX[i] == pos.X && tailY[i] == pos.Y)
				return true;
		}
		return false;
	}
};

