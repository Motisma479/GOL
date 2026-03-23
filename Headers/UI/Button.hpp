#pragma once
#include "Core/Types.hpp"

class Button
{
private:
	u8 state = 0;
	s32 x, y, width, height;
public:
	void Init(s32 _x, s32 _y, s32 _width, s32 _height);
	void Update(s32 _cursorX, s32 _cursorY);
	void Render();
	
	bool Pressed();
};