#pragma once
#include <cstdint> 

#if _WIN32

#include<Windows.h>
#include<conio.h>

#define PAUSE [] () -> void {\
    std::cout << "Press any key to continue...";\
    _getch();\
} ()

#else

#include<unistd.h>
#include <termios.h>

#define PAUSE [] () -> void {\
    std::cout << "Press any key to continue...";\
    auto getch = [] () -> int32_t {\
        struct termios oldt, newt;\
        int32_t ch;\
        tcgetattr(STDIN_FILENO, &oldt);\
        newt = oldt;\
        newt.c_lflag &= ~(ICANON | ECHO);\
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);\
        ch = getchar();\
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);\
        std::cout << "\n";\
        return ch;\
    };\
    getch();\
} ()

#endif