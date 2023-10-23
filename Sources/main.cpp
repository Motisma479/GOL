#include <iostream>

#define COLOR_ALIVE "159;223;76"
#define COLOR_DEAD "37;27;44"
#include "GOL.hpp"

#include "Gen_Shape.hpp"
#include "Utils.hpp"

int main()
{
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