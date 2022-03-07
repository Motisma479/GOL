//Game of life code file
#include "GOL.hpp"
#include <time.h>
#include <iostream>


world::world(){
    for (int x = 0; x < GOLsizeX; x++)
    {
        for (int y = 0; y < GOLsizeY; y++)
        {
            data [x][y] = false;
        } 
    }
}
world::~world(){}
int world::getValue(int x, int y){
    if (x < 0 || x > GOLsizeX-1 || y < 0 || y > GOLsizeY-1)
        return 0;
    return (int)data[x][y];
}
world world::operator=(world w){
    for (int x = 0; x < GOLsizeX; x++)
    {
        for (int y = 0; y < GOLsizeY; y++)
        {
            data[x][y] = w.data[x][y];
        }
    }
    return *this;
}
bool world::updateCell(int x, int y){
    int livingArround=0;
    
    livingArround += getValue(x-1,y);
    livingArround += getValue(x+1,y);
    livingArround += getValue(x,y-1);
    livingArround += getValue(x,y+1);
    livingArround += getValue(x-1,y-1);
    livingArround += getValue(x+1,y-1);
    livingArround += getValue(x-1,y+1);
    livingArround += getValue(x+1,y+1);

    if (data[x][y] == true)
    {
        if (livingArround<2 || livingArround>3)
        {
            return false;
        }
    }
    else
    {
        if (livingArround==3)
        {
             return true;
        }
    }
    return data[x][y];
}

GOL::GOL(){
    frameCounter = 0;
    previousframeChecked = 0;
    previousTime = time(NULL);
    fps = 0;
    previousFrameUpdate = 60;
    isFinished = false;
}
GOL::~GOL(){}
void GOL::update(float delay){
    frameCounter++;
    if (previousTime != (size_t)time(NULL))
    {
        previousTime = time(NULL);
        fps = frameCounter - previousframeChecked;
        previousframeChecked = frameCounter;
    }
    
    if (frameCounter >= previousFrameUpdate + (delay*fps))
    {
        previousFrameUpdate = frameCounter;
        //creat a world for change
        world tempWorld;
        tempWorld = i_world;

        //cells work
        for (int y = 0; y < GOLsizeX; y++)
        {
            for (int x = 0; x < GOLsizeY; x++)
            {
                tempWorld.data[x][y]=i_world.updateCell(x,y);
            }
        }
        
        //add change
        i_world = tempWorld;
    }
}
void GOL::terminalPrint(){
    for (int y = 0; y < GOLsizeX; y++)
    {
        for (int x = 0; x < GOLsizeY; x++)
        {
            if (i_world.data [x][y])
                std::cout<<"⬛";
            else
                std::cout<<"⬜";
        } 
        std::cout<<std::endl;
    }
}
void GOL::changeCell(int x, int y){
    if(i_world.data [x][y])
        i_world.data [x][y] = false;
    else
        i_world.data [x][y] = true;
}
int GOL::getFPS(){
    return fps;
}


void printFPS(GOL currentWorld){
    std::cout<<currentWorld.getFPS()<<std::endl;
}