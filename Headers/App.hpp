#pragma once
#include <vector>
#include "Types.hpp"
#include "Cell.hpp"
#include "Camera.hpp"

class App
{
public:
	App(s32 _width, s32 _height, const char* _name);
	~App();

	void Update();
private:
	GOL::Camera cam;
	std::vector<Cell> aliveCells;

	void UpdateGOL(u32 _update);
	void UpdateUI();

	void RenderGOL();
	void RenderUI();

};