//Game of life code file
#include "GOL.hpp"
#include <iostream>

GOL::GOL(int size_x, int size_y)
{
    isFinished = false;
    terminal.Init();
    sizeX = size_x;
    sizeY = size_y;
    data = new bool[size_x * size_y];
    tempData = new bool[size_x * size_y];
    for(int x = 0; x < size_x; x++)
    {
        for (int y = 0; y < size_y; y++)
        {
            *(tempData + x + y * size_y) = *(data + x + y * size_y) = false;
        }
    }

    shouldUpdate = true;
    firstUpdate = true;
}
GOL::~GOL()
{
    delete[] data;
    delete[] tempData;
}
bool GOL::update(int delay)
{
    if(firstUpdate)
    {
        waitStart = std::chrono::system_clock::now();
        shouldUpdate = false;
        firstUpdate = false;
        return true;
    }
    if (shouldUpdate)
    {
        
        for (int x = 0; x < sizeX; x++)
        {
            for (int y = 0; y < sizeY; y++)
            {
            *(tempData + x + y * sizeY) = *(data + x + y * sizeY);
            }
        }

        //cells work
        for (int x = 0; x < sizeX; x++)
        {
            for (int y = 0; y < sizeY; y++)
            {
                *(tempData + x + y * sizeY)=updateCell(x,y);
            }
        }
        
        //add change
        for (int x = 0; x < sizeX; x++)
        {
            for (int y = 0; y < sizeY; y++)
            {
            *(data + x + y * sizeY) = *(tempData + x + y * sizeY);
            }
        }
        
        waitStart = std::chrono::system_clock::now();
        shouldUpdate = false;
        return true;
    }
    if (waitStart + std::chrono::milliseconds(delay) >= std::chrono::system_clock::now())
        return false;   
    shouldUpdate = true;
    return false;
}
void GOL::terminalPrint(){
    terminal.goAt(0,0);
    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            if (*(data + x + y * sizeY))
                std::cout<<"\033[48;2;0;0;0m" << "  "; //color: 0, 0, 0
            else
                std::cout<<"\033[48;2;255;255;255m" << "  "; // color: 255, 255, 255
        } 
        std::cout<<std::endl;
    }
}
void GOL::changeCell(int x, int y){
    if(*(data + x + y * sizeY))
        *(data + x + y * sizeY) = false;
    else
        *(data + x + y * sizeY) = true;
}

bool GOL::getValue(int x, int y){
    if (x < 0) x += sizeX;
    if (y < 0) y += sizeY;
    if (x > sizeX-1) x -= sizeX;
    if (y > sizeY-1) y -= sizeY;
    return *(data + x + y * sizeY);
}

bool GOL::updateCell(int x, int y){
    int livingArround=0;

    livingArround += getValue(x-1,y+1);
    livingArround += getValue(x,y+1);
    livingArround += getValue(x+1,y+1);
    livingArround += getValue(x-1,y);

    livingArround += getValue(x+1,y);
    livingArround += getValue(x-1,y-1);
    livingArround += getValue(x,y-1);
    livingArround += getValue(x+1,y-1);

    
    if (*(data + x + y * sizeY) == true)
    {
        if (livingArround<2 || livingArround>3)
        {
            return false;
        }
    }
    else
    {
        if (livingArround==3)
            return true;
    }
    return *(data + x + y * sizeY);
}