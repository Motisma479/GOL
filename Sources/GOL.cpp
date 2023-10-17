//Game of life code file
#include "GOL.hpp"
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
bool world::getValue(int x, int y){
    if (x < 0) x += GOLsizeX;
    if (y < 0) y += GOLsizeY;
    if (x > GOLsizeX-1) x -= GOLsizeX;
    if (y > GOLsizeY-1) y -= GOLsizeY;
    return data[x][y];
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

    livingArround += getValue(x-1,y+1);
    livingArround += getValue(x,y+1);
    livingArround += getValue(x+1,y+1);
    livingArround += getValue(x-1,y);

    livingArround += getValue(x+1,y);
    livingArround += getValue(x-1,y-1);
    livingArround += getValue(x,y-1);
    livingArround += getValue(x+1,y-1);

    
    if (data[x][y] == true)
    {
        if (livingArround<2 || livingArround>3)
            return false;
    }
    else
    {
        if (livingArround==3)
            return true;
    }
    return data[x][y];
}

GOL::GOL(){
    shouldUpdate = true;
    isFinished = false;
}
GOL::~GOL(){}
bool GOL::update(int delay){
    if (shouldUpdate)
    {
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

        waitStart = std::chrono::system_clock::now();
        shouldUpdate = false;
        return true;
    }
    if (waitStart + std::chrono::milliseconds(delay) >= std::chrono::system_clock::now())
        return false;   
    shouldUpdate = true;
    //*( ( char* ) NULL ) = 0;

}
void GOL::terminalPrint(){
    for (int y = 0; y < GOLsizeX; y++)
    {
        for (int x = 0; x < GOLsizeY; x++)
        {
            if (i_world.data [x][y])
                std::cout<<"  ";
            else
                std::cout<<"\xe2\x96\x88\xe2\x96\x88";
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