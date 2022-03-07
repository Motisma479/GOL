//Game of life header file
#include <stddef.h>
#define GOLsizeX 100
#define GOLsizeY 100
class GOL
{
private:
    bool world [GOLsizeX][GOLsizeY];
    size_t frameCounter;
    size_t previousframeChecked;
    size_t previousTime;
    int fps;
public:
    GOL();
    ~GOL();
    void update(int delay);
    int getFPS();
    bool isFinished;
};


void printFPS(GOL currentWorld);