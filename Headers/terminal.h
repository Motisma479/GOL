#ifndef TERMINAL_H
#define TERMINAL_H

#if _WIN32
#include <Windows.h>
#endif

struct Terminal 
{
    inline void Init()
    {
#if _WIN32
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO cbsi;
#endif
    }

};

#endif // TERMINAL_H