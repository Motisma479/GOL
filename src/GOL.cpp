//Game of life code file
#include "GOL.hpp"
#include <time.h>
#include <iostream>

GOL::GOL(){
    for (int x = 0; x < GOLsizeX; x++)
    {
        for (int y = 0; y < GOLsizeY; y++)
        {
            world [x][y] = false;
        } 
    }
    frameCounter = 0;
    previousframeChecked = 0;
    previousTime = time(NULL);
    fps = 0;

    isFinished = false;
}
GOL::~GOL(){}

void GOL::update(int delay){
    frameCounter++;
    if (previousTime != (size_t)time(NULL))
    {
        previousTime = time(NULL);
        fps = frameCounter - previousframeChecked;
        previousframeChecked = frameCounter;
    }
}
int GOL::getFPS(){
    return fps;
}


void printFPS(GOL currentWorld){
    std::cout<<currentWorld.getFPS()<<std::endl;
}