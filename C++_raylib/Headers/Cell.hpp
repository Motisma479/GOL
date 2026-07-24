#pragma once
#include <vector>
#include "Core/Types.hpp"

class Cell
{
public:
	Cell(s32 _x, s32 _y);

	s32 x;
	s32 y;
	u8 around;
	u8 aroundToCheck;

	void IsNextTo(Cell& _cell);
	bool CheckAround(Cell& _cell);
	void ValidateToCheck();
	std::vector<std::pair<s32, s32>> GetToCheck();

};