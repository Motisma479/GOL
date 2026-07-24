#pragma once
#include "Core/Types.hpp"

class Slider
{
private:
	u8 state = 0;
	s32 x, y, width, height;
	f32 min, max, res;
	f32 lerpValue;
public:
	void Init(s32 _x, s32 _y, s32 _width, s32 _height, f32 _min, f32 _max);
	void Update(s32 _cursorX, s32 _cursorY);
	void Render();

	f32 Result();
	bool Hovered();
};