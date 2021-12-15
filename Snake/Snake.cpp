#include <iostream>
#include <cstdlib>//librarie pentru a putea reseta ecranul (dar nu o vom folosi pentru ca folosim windows.h)
#include <windows.h>
#include <conio.h>//librarie "console input output" ajuta la miscarea sarpelui pe tabla prin apasarea tastelor
#include <ctime>

#include "Snake.h"
#include "Food.h"


#define Width 50
#define Height 25

using namespace std;

void DrawBoard(Snake snake,Food food)
{
    COORD snake_pos = snake.Get_Pos();
    COORD food_pos = food.Get_Pos();
    for (int i = 0; i < Height; i++)
    {
        cout << "\t\t#";
        for (int j = 0; j < Width - 2; j++)
        {
            if (i == 0 || i == Height - 1)
                cout << "#";
            else if (i == snake_pos.Y && j == snake_pos.X)
                cout << "0";
            else if (i == food_pos.Y && j == food_pos.X)
                cout << "$";
            else
            {
                bool ok = false;
                for (int k = 1; k < snake.Get_Len(); k++)
                    if (snake.Get_TailX(k) == j && snake.Get_TailY(k) == i)
                    {
                        cout << "o"; 
                        ok = true;
                    }

                if (ok == false)
                    cout << " ";
            }
        }
        cout << "#\n";
    }
}

void cls()
{
    // Get the Win32 handle representing standard output.
    // This generally only has to be done once, so we make it static.
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD topLeft = { 0, 0 };

    // std::cout uses a buffer to batch writes to the underlying console.
    // We need to flush that to the console because we're circumventing
    // std::cout entirely; after we clear the console, we don't want
    // stale buffered text to randomly be written out.
    cout.flush();

    // Figure out the current width and height of the console window
    if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
        // TODO: Handle failure!
        abort();
    }
    DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

    DWORD written;

    // Flood-fill the console with spaces to clear it
    //FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

    // Reset the attributes of every character to the default.
    // This clears all background colour formatting, if any.
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

    // Move the cursor back to the top left for the next sequence of writes
    SetConsoleCursorPosition(hOut, topLeft);
}

void Game(Snake snake,Food food)
{
    srand(time(NULL));//face posibila generarea pozitii diferite
    food.Change_Pos();
    bool game_over = false;
    while (game_over == false)
    {
        snake.Tail();
        DrawBoard(snake,food);
        if (_kbhit())
        {
            switch (_getch())
            {
                case 'w': snake.Change_Direction('u'); break;
                case 's': snake.Change_Direction('d'); break;
                case 'a': snake.Change_Direction('l'); break;
                case 'd': snake.Change_Direction('r'); break;
            }
        }
        snake.Move();
        if (snake.eaten(food.Get_Pos()) == true)
        {
            food.Change_Pos();
            snake.Grow();
        }
        if (snake.Collide() == true)
            game_over = true;
        cout << "\t\tScore: " << snake.Get_Len();
        //cls();
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });//functia aprtine librariei widnows.h si ajuta la a nu avea flickering can se da refresh la compilator
    }

}

int main()
{
    Snake snake({ Width / 2,Height / 2 }, 1);
    Food food;
    snake.Set_TailX();
    snake.Set_TailY();
    Game(snake,food);
    return 0;
}

