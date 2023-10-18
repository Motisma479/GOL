#ifndef TERMINAL_H
#define TERMINAL_H

#if _WIN32
#include <Windows.h>
#else
#include <stdio.h>
#endif

struct Terminal 
{
#if _WIN32
    HANDLE handle;
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
#endif

    inline void Init()
    {
#if _WIN32
        handle = GetStdHandle(STD_OUTPUT_HANDLE);
        if (GetConsoleScreenBufferInfo(handle, &cbsi))
            cbsi.dwCursorPosition;
#endif
        return;
    }

    inline void goAt(short x, short y)
    {
#if _WIN32
        SetConsoleCursorPosition(handle,{x ,y });
#else
        printf("\033[%d;%dH", y, x);
#endif
    }
};

#endif // TERMINAL_H