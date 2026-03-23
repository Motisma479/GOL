#include "UI/Button.hpp"
#include <raylib.h>

void Button::Init(s32 _x, s32 _y, s32 _width, s32 _height)
{
    x = _x;
    y = _y;
    width = _width;
    height = _height;
}

void Button::Update(s32 _cursorX, s32 _cursorY)
{
    state &= ~(1 << 2);

    if ((_cursorX >= x && _cursorX <= (x+width)) && (_cursorY >= y && _cursorY <= (y+height)))
    {
        state |= 1 ;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            state |= 1 << 1;
        }

        if ((state >> 1) & 1 && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            state &= ~(1 << 1);
            state |= 1 << 2;
        }
    }
    else
    {
        state = 0;
    }
}

void Button::Render()
{
    if ((state) & 1)
    {
        Color RecColor = LIGHTGRAY;
        if ((state >> 1) & 1)
            RecColor = SKYBLUE;

        DrawRectangleRounded({ (float)x - 2, (float)y - 2, (float)width + 4, (float)height + 4 }, 0.2, 1, RecColor);
        DrawRectangleRoundedLinesEx({ (float)x - 2, (float)y - 2, (float)width + 4, (float)height + 4 }, 0.2, 1, 2, BLACK);
    }
    else
    {
        DrawRectangleRounded({ (float)x, (float)y, (float)width, (float)height }, 0.2, 1, LIGHTGRAY);
        DrawRectangleRoundedLinesEx({ (float)x, (float)y, (float)width, (float)height }, 0.2, 1, 2, BLACK);
    }

    //DrawTexturePro(more, { 0,0,16,16 }, { 10, 10, 32, 32 }, { 0,0 }, 0, { 255,212,212,255 });
    
    //DrawTexturePro(more, { 0,0,16,16 }, { 10, 10, 32, 32 }, { 0,0 }, 0, WHITE);
 }

bool Button::Pressed()
{
    return (state >> 2) & 1;
}