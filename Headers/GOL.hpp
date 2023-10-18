//Game of life header file
#include <stddef.h>
#include <chrono>
#include "terminal.h"

class GOL
{
public:
    bool isFinished;

    GOL() = delete;
    GOL(int size_x, int size_y);
    ~GOL();

    bool update(int delay);
    void terminalPrint();
    void changeCell(int x, int y);
private:
    Terminal terminal;
    int sizeX, sizeY;
    bool* data;
    bool* tempData;
    bool shouldUpdate;
    bool firstUpdate;
    std::chrono::system_clock::time_point waitStart;
    
    bool getValue(int x, int y);
    bool updateCell(int x, int y);
};