#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdio.h>
#if _WIN32
#include <Windows.h>
#else
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
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

    inline void SetCurPos(short x, short y)
    {
#if _WIN32
        SetConsoleCursorPosition(handle,{x ,y });
#else
        printf("\033[%d;%dH", y, x);
#endif
    }

    inline void GetCurPos(short* x, short* y)
    {
#if _WIN32
        GetConsoleScreenBufferInfo(handle, &cbsi);
        (*x) = cbsi.dwCursorPosition.X;
        (*y) = cbsi.dwCursorPosition.Y;
#else
        char buf[8];
        struct termios save,raw;
        tcgetattr(0,&save);
        cfmakeraw(&raw); tcsetattr(0,TCSANOW,&raw);
        if (isatty(fileno(stdin))) 
        {
            write(1,"\033[6n",4);
            read (0 ,buf ,sizeof(buf));
            sscanf(buf,"\033[%hd;%hdR",y,x);
        }
        tcsetattr(0,TCSANOW,&save);
        (*y)--;
        (*x)--;
#endif
    }

    inline void GetTermSize(short* rows, short* columns)
    {
#if _WIN32
        CONSOLE_SCREEN_BUFFER_INFO cbsi;
        GetConsoleScreenBufferInfo(handle, &cbsi);
        *rows = cbsi.srWindow.Bottom - cbsi.srWindow.Top + 1;
        *columns = cbsi.srWindow.Right - cbsi.srWindow.Left + 1;
#else
        struct winsize w;
        ioctl(0, TIOCGWINSZ, &w);
        (*rows) = w.ws_row;
        (*columns) = w.ws_col;
#endif
    }

    inline void SetTermSize(short rows, short columns)
    {
#if _WIN32
        CONSOLE_SCREEN_BUFFER_INFO cbsi;
        GetConsoleScreenBufferInfo(handle, &cbsi);
        cbsi.dwSize.X = columns;
        cbsi.dwSize.Y = rows;
        SetConsoleScreenBufferSize(handle, cbsi.dwSize);
#else
        struct winsize w;
        w.ws_row = rows+1;
        w.ws_col = columns+1;
        ioctl(0, TIOCSWINSZ, &w);
#endif
    }

    //put you at 0,0 without overwriting the buffer
    inline void NewPage()
    {
        short a,b,x,y;
        GetTermSize(&a,&b);
        GetCurPos(&x,&y);
        for(int i = 0; i < a; i++)
        {
            printf("\n");
        }
    }
};

#endif // TERMINAL_H