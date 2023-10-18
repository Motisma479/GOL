#include "GOL.hpp"
#include <iostream>

int main()
{
    std::system("chcp 65001");
    GOL newWorld(17,16);
    //-------------------------------------------------------------
    /*

      ██
    ██  ██
    ██  ██
    ██  ██
      ██

    */
    newWorld.changeCell(7,5);
    newWorld.changeCell(6,6);
    newWorld.changeCell(8,6);
    newWorld.changeCell(6,7);
    newWorld.changeCell(8,7);   
    newWorld.changeCell(6,8);
    newWorld.changeCell(8,8);
    newWorld.changeCell(7,9);

    //newWorld.changeCell(0,0);
    //newWorld.changeCell(0,15);
    //newWorld.changeCell(16,0);
    //newWorld.changeCell(16,15);
    //-------------------------------------------------------------
    while (newWorld.isFinished == false)
    {
        if(newWorld.update(1000))
            newWorld.terminalPrint();
    }

    return 0;
}