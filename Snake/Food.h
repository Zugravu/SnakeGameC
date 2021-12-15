#pragma once

#include <Windows.h>
#include <cstdlib>//librarie pentru a putea genera numere random

#define Width 50
#define Height 25

class Food
{
private:
	COORD pos;
public:
	Food(){}
	COORD Get_Pos() { return pos; }
	void Change_Pos()
	{
		int x = pos.X;
		int y = pos.Y;
		
		pos.X = (rand() % (Width - 3)) + 1;
		pos.Y = (rand() % (Height - 3)) + 1;
		if(pos.X == x || pos.Y == y)
			Change_Pos();
	}

	
};

