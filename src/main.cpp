#include "GOL.hpp"
#include <time.h>

GOL newWorld;

int main()
{
    while (newWorld.isFinished == false)
    {
        newWorld.update(1);
        printFPS(newWorld);
        timespec time = {0};
        time.tv_nsec = long(1000000000 / 60);
        nanosleep(&time, NULL);
    }

    return 0;
}