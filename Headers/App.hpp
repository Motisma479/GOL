#pragma once
#include <unordered_map>
#include "Core/Types.hpp"
#include "Cell.hpp"
#include "Chunk.hpp"
#include "Camera.hpp"
#include "UI/Button.hpp"

class App
{
public:
	App(s32 _width, s32 _height, const char* _name);
	~App();

	void Update();
private:
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

	u32 update = 0;

	void PlaceCell(s32 _x, s32 _y);
	void CreateCross(s32 _x, s32 _y);

	void UpdateGOL(u32 _update);
	void UpdateUI();

	void RenderGOL();
	void RenderUI();


	Texture more;
	Button button;
};