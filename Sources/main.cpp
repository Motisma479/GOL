#define COLOR_ALIVE "159;223;76"
#define COLOR_DEAD "37;27;44"
#include "GOL.hpp"
#include <iostream>
#include "Gen_Shape.hpp"

int main()
{
    std::system("chcp 65001");
    GOL<60, 29> gol;

    for(const auto& i : genShape_1(30, 13))
    {
        gol.changeCell(i[0], i[1]);
    }

    for(const auto& i : genShape_1(0, 13))
    {
        gol.changeCell(i[0], i[1]);
    }

    gol.terminalPrint(); //Print the first time
    while (gol.isFinished == false)
    {
        if(gol.update(100))
            gol.terminalPrint();
    }

    system("pause");

    return 0;
}