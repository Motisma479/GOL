#include "UI/Slider.hpp"
#include <raylib.h>
#include <raymath.h>
#include <algorithm>
//f32 Lerp(f32 a, f32 b, f32 l)
//{
//    return (1 - l) * a + l * b;
//}

void Slider::Init(s32 _x, s32 _y, s32 _width, s32 _height, f32 _min, f32 _max)
{
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	
	min = _min;
	max = _max;
    lerpValue = 0.5f;
    res = Lerp(min, max, lerpValue);
}

void Slider::Update(s32 _cursorX, s32 _cursorY)
{
    state &= ~(1 << 1);
    f32 xOff = Lerp(x, width - (height / 2), lerpValue);


    if ((_cursorX >= xOff && _cursorX <= (xOff + height)) && (_cursorY >= y && _cursorY <= (y + height)))
    {
        state |= 1;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            state |= 1 << 1;
        }

        if ((state >> 1) & 1)
        {
            Vector2 delta = GetMouseDelta();
            SetMousePosition(xOff+height/2+delta.x, y + height / 2);

            //rcam.target = Vector2Add(rcam.target, delta);
            lerpValue += (delta.x / (width - (height / 2)));
            lerpValue = std::clamp(lerpValue, 0.0f, 1.0f);

            res = Lerp(min, max, lerpValue);
        }
    }
    else
    {
        state = 0;
    }
}

void Slider::Render()
{
	DrawRectangleRounded({ (f32)x-2,(f32)y-2,(f32)width+4,(f32)height+4 }, 1, 1, BLACK);
	DrawRectangleRounded({ (f32)x,(f32)y,(f32)width,(f32)height }, 1, 1, GRAY);

    // = ;

	//DrawRectangle(x, y, width, height, RED);
	//DrawRectangle(x, y, height, height, BLUE);
    
	//DrawRectangleRoundedLinesEx({ (f32)x,(f32)y,(f32)width,(f32)height }, 1, 1, 2, BLACK);
	//DrawRectangleRoundedLinesEx({ (f32)x,(f32)y,(f32)width,(f32)height }, 1, 1, 2, BLACK);
    f32 xOff = Lerp(x, width - (height / 2), lerpValue);
    if ((state) & 1)
    {
        DrawRectangleRounded({ (f32)xOff - 4,(f32)y - 4,(f32)height + 8,(f32)height + 8 }, 1, 1, BLACK);
        if ((state >> 1) & 1)
            DrawRectangleRounded({ (f32)xOff - 2,(f32)y - 2,(f32)height + 4,(f32)height + 4 }, 1, 1, SKYBLUE);
        else
            DrawRectangleRounded({ (f32)xOff - 2,(f32)y - 2,(f32)height + 4,(f32)height + 4 }, 1, 1, LIGHTGRAY);
    }
    else
    {
        DrawRectangleRounded({ (f32)xOff - 2,(f32)y - 2,(f32)height + 4,(f32)height + 4 }, 1, 1, BLACK);
        DrawRectangleRounded({ (f32)xOff,(f32)y,(f32)height,(f32)height }, 1, 1, LIGHTGRAY);
    }
}

f32 Slider::Result()
{
	return res;
}

bool Slider::Hovered()
{
    return ((state >> 0) & 1);
}