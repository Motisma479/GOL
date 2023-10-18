#define COLOR_ALIVE "159;223;76"
#define COLOR_DEAD "37;27;44"
#include "GOL.hpp"
#include <iostream>

int main()
{
    std::system("chcp 65001");
    GOL<50, 50> newWorld;

    // //-------------------------------------------------------------
    // /*

    //   ██
    // ██  ██
    // ██  ██
    // ██  ██
    //   ██

    // */
    // newWorld.changeCell(7,5);
    // newWorld.changeCell(6,6);
    // newWorld.changeCell(8,6);
    // newWorld.changeCell(6,7);
    // newWorld.changeCell(8,7);   
    // newWorld.changeCell(6,8);
    // newWorld.changeCell(8,8);
    // newWorld.changeCell(7,9);
    // //-------------------------------------------------------------

    //-------------------------------------------------------------
    /*

      ██
        ██
    ██████

    */
    newWorld.changeCell(7,5);
    newWorld.changeCell(8,6);
    newWorld.changeCell(6,7);
    newWorld.changeCell(7,7);
    newWorld.changeCell(8,7);
    //-------------------------------------------------------------

    // //-------------------------------------------------------------
    // /*
        
    // ██
    // ██████
    //   ██

    // */
    // newWorld.changeCell(7,5);
    // newWorld.changeCell(7,6);
    // newWorld.changeCell(8,6);
    // newWorld.changeCell(9,6);
    // newWorld.changeCell(8,7);
    // //-------------------------------------------------------------

    newWorld.terminalPrint(); //Print the first time
    while (newWorld.isFinished == false)
    {
        if(newWorld.update(50))
            newWorld.terminalPrint();
    }

    system("pause");

    return 0;
}