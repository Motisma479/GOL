/*
#include <iostream>

#define COLOR_ALIVE "159;223;76"
#define COLOR_DEAD "37;27;44"
#include "GOL.hpp"

#include "Gen_Shape.hpp"
#include "Utils.hpp"

int main()
{
#if WIN32 //Use for Windows 10- to support ansi color
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif

    GOL<32, 16> gol;

    for(const auto& i : genShape_1(0, 0))
    {
        gol.changeCell(i[0], i[1]);
    }
    for(const auto& i : genShape_2(8, 6))
    {
        gol.changeCell(i[0], i[1]);
    }

    for(const auto& i : genShape_2(16, 6))
    {
        gol.changeCell(i[0], i[1]);
    }

    gol.terminalPrint(); //Print the first time
    while (gol.isFinished == false)
    {
        if(gol.update(100))
            gol.terminalPrint();
    }

    gol.~GOL();

    PAUSE;

    return 0;
}
*/
#include <raylib.h>

int main(void)
{ 
    const int screenWidth = 1024;
    const int screenHeight = 576;

    InitWindow(screenWidth, screenHeight, "Conway's Game of Life (C++ raylib Edition)");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        
        //Render
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(WHITE);

            DrawText("Comming soon...", 10, 511, 60, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseWindow();

    return 0;
}