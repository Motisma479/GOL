#include "GOL.hpp"
#include <time.h>

#include <iostream>

GOL newWorld;

int main()
{
                    newWorld.changeCell(21,18);     
    newWorld.changeCell(20,19);  newWorld.changeCell(22,19);
    newWorld.changeCell(20,20);  newWorld.changeCell(22,20);   
    newWorld.changeCell(20,21);  newWorld.changeCell(22,21);
                    newWorld.changeCell(21,22);

    while (newWorld.isFinished == false)
    {
        for (int i = 0; i < 200; i++)
        {
            std::cout<<std::endl;
        }
        newWorld.update(0.5);
        printFPS(newWorld);
        newWorld.terminalPrint();


        timespec time = {0};
        time.tv_nsec = long(1000000000 / 60);
        nanosleep(&time, NULL);
    }

    return 0;
}