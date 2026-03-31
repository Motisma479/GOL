#include "App.hpp"

#include "rlgl.h"
#include "raymath.h"

#include <iostream>
#include <unordered_map>

#include <string>


void App::CreateCross(s32 _x, s32 _y)
{
    PlaceCell(_x,_y);
    PlaceCell(_x-1,_y);
    PlaceCell(_x+1,_y);
    PlaceCell(_x,_y-1);
    PlaceCell(_x,_y+1);
}

void App::PlaceCell(s32 _x, s32 _y)
{
    s32 chunkX = _x < 0 ? (((_x - 7) / 8)) : (_x / 8);
    s32 chunkY = _y < 0 ? (((_y - 7) / 8)) : (_y / 8);
    
    s32 relX = _x - (8 * chunkX);
    s32 relY = _y - (8 * chunkY);

    u64 data = (u64)1 << (relX + 8 * relY);

    //std::cout << "Chunk: [" << chunkX << "; " << chunkY << "];\nRelatifCord: [" << relX << "; " << relY << "]\n";

    auto itC = chunks.find({ chunkX, chunkY });
    if ((itC != chunks.end()))
    {
        itC->second.get()->data ^= data;
    }
    else
    {
        chunks.emplace(std::make_pair<ChunkPos, std::unique_ptr<Chunk>>({ chunkX,chunkY }, std::make_unique<Chunk>(chunkX, chunkY, data))).first->second.get()->DoLinks(chunks);
        edit.emplace(std::make_pair<ChunkPos, std::unique_ptr<Chunk>>({ chunkX,chunkY }, std::make_unique<Chunk>(chunkX, chunkY, 0))).first->second.get()->DoLinks(edit);
    }
}

Mesh GenGolPlane(float width, float height)
{
    Mesh mesh = { 0 };


    Vector3 vertices[4] =
    {
        {0,0,0},
        {0,8,0},
        {8,8,0},
        {8,0,0}
    };

    

    // Normals definition
    Vector3 normals[4] =
    {
        { 0.0f, 0.0f, 1.0f },
        { 0.0f, 0.0f, 1.0f },
        { 0.0f, 0.0f, 1.0f },
        { 0.0f, 0.0f, 1.0f }
    };

    // TexCoords definition
    Vector2 texcoords[4] =
    {
        {0,0},
        {0,1},
        {1,1},
        {1,0}
    };

    // Triangles definition (indices)
    int numFaces = 1;
    int triangles[6] =
    {
        0,1,3,
        1,2,3
    };
    

    mesh.vertexCount = 4;
    mesh.triangleCount = numFaces * 2;
    mesh.vertices = (float*)RL_MALLOC(mesh.vertexCount * 3 * sizeof(float));
    mesh.texcoords = (float*)RL_MALLOC(mesh.vertexCount * 2 * sizeof(float));
    mesh.normals = (float*)RL_MALLOC(mesh.vertexCount * 3 * sizeof(float));
    mesh.indices = (unsigned short*)RL_MALLOC(mesh.triangleCount * 3 * sizeof(unsigned short));

    // Mesh vertices position array
    for (int i = 0; i < mesh.vertexCount; i++)
    {
        mesh.vertices[3 * i] = vertices[i].x;
        mesh.vertices[3 * i + 1] = vertices[i].y;
        mesh.vertices[3 * i + 2] = vertices[i].z;
    }

    // Mesh texcoords array
    for (int i = 0; i < mesh.vertexCount; i++)
    {
        mesh.texcoords[2 * i] = texcoords[i].x;
        mesh.texcoords[2 * i + 1] = texcoords[i].y;
    }

    // Mesh normals array
    for (int i = 0; i < mesh.vertexCount; i++)
    {
        mesh.normals[3 * i] = normals[i].x;
        mesh.normals[3 * i + 1] = normals[i].y;
        mesh.normals[3 * i + 2] = normals[i].z;
    }

    // Mesh indices array initialization
    for (int i = 0; i < mesh.triangleCount * 3; i++) mesh.indices[i] = triangles[i];


    // Upload vertex data to GPU (static mesh)
    UploadMesh(&mesh, false);

    return mesh;
}

App::App(s32 _width, s32 _height, const char* _name)
{
    width = _width; height = _height;
    InitWindow(_width, _height, _name);
    cam.Init(-25.6f, -14.4f, 20.0f);

    chunks.emplace(std::make_pair<ChunkPos, std::unique_ptr<Chunk>>({0,0}, std::make_unique<Chunk>(0, 0, 0)));
    edit.emplace(std::make_pair<ChunkPos, std::unique_ptr<Chunk>>({ 0,0 }, std::make_unique<Chunk>(0, 0, 0)));


    for (int i = 0; i < 50; i++)
        for (int j = 0; j < 50; j++)
            CreateCross( i * 10, j * 10);

    auto get = [](int x, int y, std::unordered_map<ChunkPos, std::unique_ptr<Chunk>, ChunkPosHash>& chunks) -> Chunk*
    {
        auto it = chunks.find({ x, y });
        return (it != chunks.end()) ? it->second.get() : nullptr;
    };

    for (auto& [pos, chunk] : chunks)
    {
        std::unique_ptr<Chunk>& editableChunk = edit.at(pos);

        chunk->DoLinks(chunks);
        editableChunk->DoLinks(edit);

        if (cam.CanRender(pos.x, pos.y))
            drawData.push_back(chunk->drawData);
    }

    golShader = LoadShaderFromMemory(
        "#version 430\n\
        in vec3 vertexPosition;\
        in vec2 vertexTexCoord;\
        in vec3 vertexNormal;\
        in vec4 vertexColor;\
        uniform mat4 mvp;\
        out vec2 fragTexCoord;\
        out vec4 fragColor;\
        flat out uvec2 data;\
        struct Chunk\
        {\
            ivec2 pos;\
            uvec2 data;\
        };\
        layout(std430, binding = 0) buffer ChunkBuffer\
        {\
            Chunk chunks[];\
        };\
        void main()\
        {\
            Chunk c = chunks[gl_InstanceID];\
            fragTexCoord = vertexTexCoord;\
            fragColor = vertexColor;\
            data = c.data;\
            vec2 worldPos = (c.pos * 8.0 +  vertexPosition.xy);\
            gl_Position = mvp * vec4(worldPos, 0.0, 1.0);\
        }",


        "#version 430\n\
        in vec2 fragTexCoord;\
        in vec4 fragColor;\
        flat in uvec2 data;\
        uniform sampler2D texture0;\
        uniform vec4 colDiffuse;\
        out vec4 finalColor;\
        uint getBit(int index)\
        {\
            if (index < 32)\
                return (data.x >> index) & 1u;\
            else\
                return (data.y >> (index - 32)) & 1u;\
        }\
        void main()\
        {\
            vec4 texelColor = texture(texture0, fragTexCoord);\
            ivec2 pixel = ivec2(floor(fragTexCoord * 8.0));\
            int bitIndex = pixel.y * 8 + pixel.x;\
            bool alive = getBit(bitIndex) == 1u;\
            finalColor =  alive ? vec4(0.0,0.0,0.0,1.0) : vec4(1.0) ;\
        }"
    );
    u32 maxChunkPerScreen = (_width / 16) * (_height / 16); // 16 because the min zoom is x2
    golBuffer = rlLoadShaderBuffer(maxChunkPerScreen * sizeof(DrawChunkData), drawData.data(), RL_STATIC_DRAW);
    rlBindShaderBuffer(golBuffer, 0);

    more.Init(width - 38, height - 38, 30, 30);
    next.Init(8, 8, 30, 30);
    playPause.Init(46, 8, 30, 30);
    reset.Init(84, 8, 30, 30);
    playRateSlider.Init(8, 46, 107, 16, 1000, 0);
    gridButton.Init(8, _height - 38, 30, 30);

    golMesh = GenGolPlane(8, 8);
    matInstances = LoadMaterialDefault();
    matInstances.shader = golShader;

    preFrameTime = std::chrono::high_resolution_clock::now();
    DT = 0;
    minDT = 100000000;
    maxDT = 0;
}

App::~App()
{
    CloseWindow();
}

void App::Update()
{   
    while (!WindowShouldClose())
    {
        std::chrono::high_resolution_clock::time_point frameTime = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration<f32, std::milli>(frameTime - preFrameTime).count();
        preFrameTime = frameTime;

        static f32 timer = 0;
        timer += deltaTime;
        if (timer >= 500.0f)
        {
            DT = deltaTime;
            f32 alpha = 0.05f;
            timer -= 500.0f;
        }
        minDT = deltaTime < minDT ? deltaTime : minDT;
        maxDT = deltaTime > maxDT ? deltaTime : maxDT;

        //DEBUG
        if (IsKeyPressed(KEY_F3))
        {
            debugEnable = !debugEnable;
            SetWindowTitle("Conway's Game of Life (C++ raylib Edition)");
        }
        if (debugEnable)
        {
            SetWindowTitle(TextFormat("Conway's Game of Life (C++ raylib Edition) | [zoom: %f ] [FPS: %.2f/%.2fms min:%.2fms max%.2fms]", cam.GetZoom(), 1000/DT, DT, minDT, maxDT));
        }
        
        cam.Update(!uiHovered);
        camRefresh+=deltaTime;
        if (cam.IsMoving() && camRefresh >= 5.f)
        {
            drawData.clear();
            for (auto& [pos, chunk] : chunks)
            {
                if (cam.CanRender(pos.x, pos.y))
                    drawData.push_back(chunk->drawData);
            }
            rlUpdateShaderBuffer(golBuffer, drawData.data(), drawData.size() * sizeof(DrawChunkData), 0);
            camRefresh -= 5.f;
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            Vector2 worldMouse = cam.ScreenPosToWorlPos(GetMousePosition());
            int cellX = std::floor(worldMouse.x);
            int cellY = std::floor(worldMouse.y);

            PlaceCell(cellX, cellY);
            drawData.clear();
            for (auto& [pos, chunk] : chunks)
            {
                if (cam.CanRender(pos.x, pos.y))
                    drawData.push_back(chunk->drawData);
            }
            rlUpdateShaderBuffer(golBuffer, drawData.data(), drawData.size() * sizeof(DrawChunkData), 0);
        }

        UpdateUI();


        if (autoMode)
        {
            static f32 golTimer = 0;
            golTimer += deltaTime;
            if (golTimer >= playRate)
            {
                UpdateGOL();
                golTimer -= playRate;
            }
        }
        //UpdateGOL(update); //-------------------------------------------------------------------------------------------------

        //draw-------------------------
        
        BeginDrawing();
        if(debugEnable)
            ClearBackground(GREEN);
        else
            ClearBackground(WHITE);

        cam.BegingContext();

        RenderGOL();

        cam.EndContext();


        RenderUI();
        
        DrawCircleV(GetMousePosition(), 2, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
}

void App::UpdateGOL()
{   
    drawData.clear();
    std::queue<ChunkPos> markedForDelete;
    std::queue<ChunkPos> markedForAddition;//maybe using this will solve the probleme?

    for (auto& [pos, chunk] : chunks)
    {
        std::unique_ptr<Chunk>& editableChunk = edit.at(pos);
        chunk->CreateNewChunks(markedForAddition);
        chunk->Update(editableChunk);
        if (editableChunk->ShouldDelete())
        {
            markedForDelete.push(pos);
        }
        //else if(editableChunk->data != 0 && cam.CanRender(pos.x, pos.y))
        else if(cam.CanRender(pos.x, pos.y))
            drawData.push_back(editableChunk->drawData);
    }

    while (markedForDelete.size() != 0)
    {
        ChunkPos pos = markedForDelete.front();

        chunks.erase(pos);
        edit.erase(pos);

        markedForDelete.pop();
    }

    while (markedForAddition.size() != 0)
    {
        ChunkPos pos = markedForAddition.front();

        Chunk* existC = Chunk::Get(pos, chunks);
        Chunk* existE = Chunk::Get(pos, edit);

        if (!existC)
        {
            existC = chunks.emplace(pos, std::make_unique<Chunk>(pos.x, pos.y, 0)).first->second.get();
            existE = edit.emplace(pos, std::make_unique<Chunk>(pos.x, pos.y, 0)).first->second.get();
        }

        existC->DoLinks(chunks);
        existE->DoLinks(edit);

        existC->Update(edit.at(pos));
        //if (existE->data != 0 && cam.CanRender(pos.x, pos.y))
        if (cam.CanRender(pos.x, pos.y))
            drawData.push_back(existE->drawData);

        markedForAddition.pop();
    }

    chunks.swap(edit);

    rlUpdateShaderBuffer(golBuffer, drawData.data(), drawData.size() * sizeof(DrawChunkData), 0);
    return;
}

void App::UpdateUI()
{
    uiHovered = false;
    s32 x = GetMouseX(); s32 y = GetMouseY();

    playRateSlider.Update(x,y);
    uiHovered |= playRateSlider.Hovered();
    playRate = playRateSlider.Result();
    
    next.Update(x, y);
    uiHovered |= next.Hovered();
    if (next.Pressed())
    {
        UpdateGOL();
    }

    playPause.Update(x, y);
    uiHovered |= playPause.Hovered();
    if (playPause.Pressed())
    {
        autoMode = !autoMode;
    }

    reset.Update(x, y);

    more.Update(x, y);
    uiHovered |= more.Hovered();
    if (more.Pressed())
    {
        moreToggle = !moreToggle;
    }

    gridButton.Update(x, y);
    if (gridButton.Pressed())
    {
        showGrid = !showGrid;
    }
}

void App::RenderGOL()
{
    golMatrix.clear();
    for (const auto& i : drawData) golMatrix.push_back(MatrixUnit);

    BeginShaderMode(golShader);

    DrawMeshInstanced(golMesh, matInstances, golMatrix.data(), drawData.size());

    EndShaderMode();
    return;
}

void App::RenderUI()
{
    cam.BegingContext();

    //draw a grid centered on the camera
    if (showGrid && cam.GetZoom() > 5)
    {
        Vector2 m = cam.GetMinWorld();
        Vector2 M = cam.GetMaxWorld();
        if (debugEnable)
        {
            for (s32 i = m.x; i < M.x; i++)
                if (i % 8 == 0)
                    DrawLineEx({ (f32)i, m.y }, { (f32)i, M.y }, 0.32, RED);
                else
                    DrawLine(i, m.y, i, M.y, BLACK);
            for (s32 j = m.y; j < M.y; j++)
                if (j % 8 == 0)
                    DrawLineEx({ m.x, (f32)j }, { M.x, (f32)j }, 0.32, RED);
                else
                    DrawLine(m.x, j, M.x, j, BLACK);
        }
        else
        {
            for (s32 i = m.x; i < M.x; i++)
                DrawLine(i, m.y, i, M.y, BLACK);
            for (s32 j = m.y; j < M.y; j++)
                DrawLine(m.x, j, M.x, j, BLACK);
        }

    }
    
    cam.EndContext();

    next.RenderWithTexture(1, WHITE, { 255,212,212,255 });
    if(autoMode)
        playPause.RenderWithTexture(5, { 255,0,0,255 }, { 255,160,160,255 });
    else
        playPause.RenderWithTexture(4, { 0,255,0,255 }, { 160,255,160,255 });

    reset.RenderWithTexture(6, { 66,112,255,255 }, { 128,159,255,255 });

    playRateSlider.Render();

    more.RenderWithTexture(2, WHITE, { 255,212,212,255 });
    if (moreToggle)
    {
        DrawRectangle(width - 246, height - 168, 200, 160, DARKGRAY);
        DrawRectangle(width - 241, height - 163, 190, 150, LIGHTGRAY);
        DrawText(TextFormat("Chunks: %i", chunks.size()), width - 236, height - 160, 20, BLACK);
        DrawText(TextFormat("Draw: %i", drawData.size()), width - 236, height - 140, 20, BLACK);

        DrawText(TextFormat("ver: %s", GOL_VERSION), width - 236, height - 30, 19, BLACK);
    }

    gridButton.RenderWithTexture(3, WHITE, { 255,212,212,255 });

    if (debugEnable)
    {
        DrawRectangleRounded({ (float)GetMouseX() + 25, (float)GetMouseY() - 40, 210,80 }, 0.25, 10, DARKBLUE);
        DrawRectangleRounded({ (float)GetMouseX() + 30, (float)GetMouseY() - 35, 200,70 }, 0.25, 10, SKYBLUE);


        DrawTextEx(GetFontDefault(), "Mouse:",
            Vector2Add(GetMousePosition(), { 35, -30 }), 20, 2, BLACK);
        DrawTextEx(GetFontDefault(), TextFormat("[%i, %i]", GetMouseX(), GetMouseY()),
            Vector2Add(GetMousePosition(), { 115, -30 }), 20, 2, BLACK);

        Vector2 worldMouse = cam.ScreenPosToWorlPos(GetMousePosition());
        int cellX = std::floor(worldMouse.x);
        int cellY = std::floor(worldMouse.y);
        DrawTextEx(GetFontDefault(), "Cell:",
            Vector2Add(GetMousePosition(), { 35, -10 }), 20, 2, BLACK);
        DrawTextEx(GetFontDefault(), TextFormat("[%i, %i]", cellX, cellY),
            Vector2Add(GetMousePosition(), { 115, -10 }), 20, 2, BLACK);

        int chunkX = cellX < 0 ? (((cellX - 7) / 8)) : (cellX / 8);
        int chunkY = cellY < 0 ? (((cellY - 7) / 8)) : (cellY / 8);

        DrawTextEx(GetFontDefault(), "Chunk:",
            Vector2Add(GetMousePosition(), { 35, 10 }), 20, 2, BLACK);
        DrawTextEx(GetFontDefault(), TextFormat("[%i, %i]", chunkX, chunkY),
            Vector2Add(GetMousePosition(), { 115, 10 }), 20, 2, BLACK);
    }

   
    {
        //reload
        //if (GetMousePosition().x > 0 && GetMousePosition().x < 100 && GetMousePosition().y > 0 && GetMousePosition().y < 100)
        //    DrawTexturePro(img, { 0,0,16,16 }, { 0, 0, 100, 100 }, { 0,0 }, 0, );
        //else
        //    DrawTexturePro(img, {0,0,16,16}, { 0, 0, 100, 100 }, { 0,0 }, 0, );

    }
}