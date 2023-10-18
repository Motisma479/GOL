#define COLOR_ALIVE "159;223;76"
#define COLOR_DEAD "37;27;44"
#include "GOL.hpp"
#include <iostream>
#include "Gen_Shape.hpp"

int main()
{
    GOL<32, 16> gol(true);

    for(const auto& i : genShape_1(0, 0))
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