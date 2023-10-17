//Game of life header file
#include <stddef.h>
#include <chrono>
#define GOLsizeX 72
#define GOLsizeY 72

class world
{
public:
    world();
    ~world();
    bool data [GOLsizeX][GOLsizeY];
    bool getValue(int x, int y);
    world operator=(world w);
    bool updateCell(int x, int y);
};



class GOL
{
public:
    GOL();
    ~GOL();
    bool update(int delay);
    void terminalPrint();
    void changeCell(int x, int y);
    bool isFinished;
private:
    world i_world;
    bool shouldUpdate;
    std::chrono::system_clock::time_point waitStart;
};