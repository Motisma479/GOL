//Game of life header file
#pragma once
#include <chrono>
#include <iostream>
#include <string>
#include <bitset>

#ifndef COLOR_ALIVE
#define COLOR_ALIVE 0, 0, 0
#endif

#ifndef COLOR_DEAD
#define COLOR_DEAD 255, 255, 255
#endif

constexpr char ColAl[3] = { COLOR_ALIVE };
constexpr char ColDe[3] = { COLOR_DEAD };

template <int size_x, int size_y>
class GOL
{
public:
    bool isFinished;

    GOL(bool restricted = false)
    {
        isFinished = false;
        
        imageData = new unsigned int[pixelCount];

        //init data
        for(int x = 0; x < size_x; x++)
        {
            for (int y = 0; y < size_y; y++)
            {
                data.set(x+y*size_x, false);
            }
        }

        shouldUpdate = true;
        firstUpdate = true;
        _restricted = restricted;
        hasChanged = false;
    }
    ~GOL()
    {
        delete[] imageData;
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
            auto tempData = std::bitset<size_x * size_y>(data);

            //cells work
            for (int x = 0; x < size_x; x++)
            {
                for (int y = 0; y < size_y; y++)
                {
                    tempData.set(x+y*size_x, updateCell(x,y));
                }
            }
            isFinished = !hasChanged;
            hasChanged = false;
            
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

    void Print()
    {
        //std::cout << std::flush;
        //terminal.SetCurPos(0,0);
        //for (int y = 0; y < size_y; y++)
        //{
        //    for (int x = 0; x < size_x; x++)
        //    {
        //        if (data[x+y*size_x])
        //            std::cout<< __COLOR_ALIVE__ << "  "; //color: 0, 0, 0 by default
        //        else
        //            std::cout<< __COLOR_DEAD__ << "  "; // color: 255, 255, 255 by default
        //    } 
        //    std::cout<<"\n";
        //}
        //std::cout << "\033[0m";
        for (unsigned int i = 0; i <= pixelCount-1; i++)
        {
            unsigned int c = data[i] ? (ColAl[0] << 16) + (ColAl[1] << 8) + ColAl[2] : (ColDe[0] << 16) + (ColDe[1] << 8) + ColDe[2];
            imageData[i] = c;
        }
    }
    const unsigned int* GetImageData()const { return imageData; }

    void changeCell(int x, int y)
    {
        data.flip(x+y*size_x);
    }
    void SetCell(int x, int y, bool value)
    {
        data.set(x+y*size_x, value);
    }

private:
    std::bitset<size_x*size_y> data;

    unsigned int pixelCount = size_x * size_y;
    unsigned int* imageData = nullptr;

    bool shouldUpdate;
    bool firstUpdate;
    std::chrono::system_clock::time_point waitStart;

    bool _restricted;
    bool hasChanged;
    
    bool getValue(int x, int y)
    {
        if(!_restricted)
        {
            if (x < 0) x += size_x;
            if (y < 0) y += size_y;
            if (x > size_x-1) x -= size_x;
            if (y > size_y-1) y -= size_y;
            return data[x+y*size_x];
        }
        else
        {
            if(x < 0 || x >= size_x-1) return false;
            if(y < 0 || y >= size_y-1) return false;
            return data[x+y*size_x];
        }
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
            {
                hasChanged = true;
                return false;
            }
        }
        else
        {
            if (livingArround==3)
            {
                hasChanged = true;
                return true;
            }
        }
        return data[x+y*size_x];
    }
};