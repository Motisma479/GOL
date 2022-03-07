//Game of life header file
#include <stddef.h>
#define GOLsizeX 75
#define GOLsizeY 75

class world
{
public:
    world();
    ~world();
    bool data [GOLsizeX][GOLsizeY];
    int getValue(int x, int y);
    world operator=(world w);
    bool updateCell(int x, int y);
};



class GOL
{
public:
    GOL();
    ~GOL();
    void update(float delay);
    void terminalPrint();
    void changeCell(int x, int y);
    int getFPS();
    bool isFinished;
private:
    world i_world;
    size_t frameCounter;
    size_t previousframeChecked;
    size_t previousTime;
    size_t previousFrameUpdate;
    int fps;
};


void printFPS(GOL currentWorld);