#ifndef TERMINAL_H
#define TERMINAL_H

#if _WIN32
#include <Windows.h>
#endif

struct Terminal 
{
    HANDLE handle;
    CONSOLE_SCREEN_BUFFER_INFO cbsi;

    inline void Init()
    {
#if _WIN32
        handle = GetStdHandle(STD_OUTPUT_HANDLE);
        if (GetConsoleScreenBufferInfo(handle, &cbsi))
            cbsi.dwCursorPosition;
#endif
    }

    inline void goAt(short x, short y)
    {
#if _WIN32
        SetConsoleCursorPosition(handle,{x ,y });
#endif
    }
};

#endif // TERMINAL_H