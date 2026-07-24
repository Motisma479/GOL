#pragma once
#include <chrono>
#include "Core/Types.hpp"
#include "Cell.hpp"
#include "Chunk.hpp"
#include "Camera.hpp"

#include "UI/Button.hpp"
#include "UI/Slider.hpp"

class App
{
public:
	App(s32 _width, s32 _height, const char* _name);
	~App();

	void Update();
private:
	s32 width, height;
	bool debugEnable = false;
	GOL::Camera cam;
	u32 camRefresh = 0;

	std::unordered_map<ChunkPos,std::unique_ptr<Chunk>, ChunkPosHash>chunks;
	std::unordered_map<ChunkPos,std::unique_ptr<Chunk>, ChunkPosHash>edit;

	std::vector<DrawChunkData> drawData;
	u32 golBuffer;
	Shader golShader;

	Mesh golMesh;          //the instanced plane;
	Material matInstances; //the instanced Material;
	std::vector<Matrix> golMatrix;//unused but required for the instanced function

	bool autoMode = false;

	std::chrono::high_resolution_clock::time_point preFrameTime;
	f32 deltaTime;
	//used for the debug
	f32 DT;
	f32 minDT;
	f32 maxDT;
	//-----------------

	void PlaceCell(s32 _x, s32 _y);
	void CreateCross(s32 _x, s32 _y);

	void UpdateGOL();
	void UpdateUI();

	void RenderGOL();
	void RenderUI();

	//button
	Button more;
	bool moreToggle = false;
	Button gridButton;
	bool showGrid = true;
	Button next;
	Button playPause;
	Button reset;
	Slider playRateSlider;
	f32 playRate;

	bool uiHovered = false;
};