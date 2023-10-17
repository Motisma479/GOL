#include "GOL.hpp"
#include <iostream>

int main()
{
    std::system("chcp 65001");
    GOL newWorld;

    //-------------------------------------------------------------
    /*

      ██
    ██  ██
    ██  ██
    ██  ██
      ██

    */
    newWorld.changeCell(21,18);        
    newWorld.changeCell(20,19);
    newWorld.changeCell(22,19);
    newWorld.changeCell(20,20);
    newWorld.changeCell(22,20);   
    newWorld.changeCell(20,21);
    newWorld.changeCell(22,21);
    newWorld.changeCell(21,22);
    //-------------------------------------------------------------
    while (newWorld.isFinished == false)
    {
        if(newWorld.update(500))
        {
            newWorld.terminalPrint();
        }
 
    //std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}