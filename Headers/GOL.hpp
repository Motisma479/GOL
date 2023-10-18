//Game of life header file
#include <chrono>
#include <iostream>
#include <string>
#include <bitset>
#include "terminal.h"

#ifndef COLOR_ALIVE
#define COLOR_ALIVE "0;0;0"
#endif

#ifndef COLOR_DEAD
#define COLOR_DEAD "255;255;255"
#endif

#define __COLOR_ALIVE__ "\033[48;2;"COLOR_ALIVE"m"
#define __COLOR_DEAD__ "\033[48;2;"COLOR_DEAD"m"

template <int size_x, int size_y>
class GOL
{
public:
    bool isFinished;

    GOL()
    {
        isFinished = false;
        terminal.Init();

        for(int x = 0; x < size_x; x++)
        {
            for (int y = 0; y < size_y; y++)
            {
                data.set(x+y*size_x, false);
            }
        }

        shouldUpdate = true;
        firstUpdate = true;
    }
    ~GOL()
    {

    }

    bool update(int delay)
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
            //copy data to tempData
            auto tempData = std::bitset<size_x*size_y>(data);

            //cells work
            for (int x = 0; x < size_x; x++)
            {
                for (int y = 0; y < size_y; y++)
                {
                    tempData.set(x+y*size_x, updateCell(x,y));
                }
            }
            
            //copy tempData to data
            data = tempData;

            waitStart = std::chrono::system_clock::now();
            shouldUpdate = false;
            return true;
        }
        if (waitStart + std::chrono::milliseconds(delay) >= std::chrono::system_clock::now())
            return false;   
        shouldUpdate = true;
        return false;
    }
    void terminalPrint()
    {
        terminal.goAt(0,0);
        for (int y = 0; y < size_y; y++)
        {
            for (int x = 0; x < size_x; x++)
            {
                if (data[x+y*size_x])
                    std::cout<< __COLOR_ALIVE__ << "  "; //color: 0, 0, 0 by default
                else
                    std::cout<< __COLOR_DEAD__ << "  "; // color: 255, 255, 255 by default
            } 
            std::cout<<std::endl;
        }
    }
    void changeCell(int x, int y)
    {
        data.flip(x+y*size_x);
    }

private:
    Terminal terminal;
    std::bitset<size_x*size_y> data;

    bool shouldUpdate;
    bool firstUpdate;
    std::chrono::system_clock::time_point waitStart;
    
    bool getValue(int x, int y)
    {
        if (x < 0) x += size_x;
        if (y < 0) y += size_y;
        if (x > size_x-1) x -= size_x;
        if (y > size_y-1) y -= size_y;
        return data[x+y*size_x];
    }
    bool updateCell(int x, int y)
    {
        int livingArround=0;

        livingArround += getValue(x-1,y+1);
        livingArround += getValue(x,y+1);
        livingArround += getValue(x+1,y+1);
        livingArround += getValue(x-1,y);

        livingArround += getValue(x+1,y);
        livingArround += getValue(x-1,y-1);
        livingArround += getValue(x,y-1);
        livingArround += getValue(x+1,y-1);

        
        if (data[x+y*size_x])
        {
            if (livingArround<2 || livingArround>3)
                return false;
        }
        else
        {
            if (livingArround==3)
                return true;
        }
        return data[x+y*size_x];
    }
};