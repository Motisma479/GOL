#include "UI/Button.hpp"
#include <iostream>

Texture Button::buttonTextureAtlas = Texture();

void Button::Init(s32 _x, s32 _y, s32 _width, s32 _height)
{
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    
    if (!IsTextureValid(buttonTextureAtlas))
    {
        buttonTextureAtlas = LoadTexture("Resources/buttonAtlas.png");
    }
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

 }

void Button::RenderWithTexture(u32 texureOffId, Color color, Color colorHovered)
{
    const u32 column = buttonTextureAtlas.width / 16;
    const u32 xImg = texureOffId % column;
    const u32 yImg = texureOffId / column;
    const f32 off = 4.f / 5;
    f32 nw = width * off;
    f32 nh = height * off;

    //if (GetMousePosition().x > 0 && GetMousePosition().x < 100 && GetMousePosition().y > 0 && GetMousePosition().y < 100)
        //else
    Render();
    if ((state) & 1)
    {
        f32 nw = width * off + 5;
        f32 nh = height * off + 5;
        DrawTexturePro(buttonTextureAtlas, { xImg * 16.f, yImg * 16.f, 16, 16 }, { (f32)x + (width - nw) / 2, (f32)y + (height - nh) / 2, nw, nh }, { 0,0 }, 0, colorHovered);
    }
    else
    {
        DrawTexturePro(buttonTextureAtlas, { xImg * 16.f, yImg * 16.f ,16,16 }, { (f32)x + (width - nw) / 2, (f32)y + (height - nh) / 2, nw, nh }, { 0,0 }, 0, color);
    }
}

bool Button::Pressed()
{
    return (state >> 2) & 1;
}

bool Button::Hovered()
{
    return ((state >> 0) & 1);
}