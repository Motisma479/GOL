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
    s32 chunkX = _x < 0 ? (((_x - 8) / 8)) : (_x / 8);
    s32 chunkY = _y < 0 ? (((_y - 8) / 8)) : (_y / 8);
    
    s32 relX = _x - (8 * chunkX);
    s32 relY = _y - (8 * chunkY);

    u64 data = (u64)1 << (relX + 8 * relY);

    //std::cout << "Chunk: [" << chunkX << "; " << chunkY << "];\nRelatifCord: [" << relX << "; " << relY << "]\n";

    auto itC = chunks.find({ chunkX, chunkY });
    if ((itC != chunks.end()))
    {
        itC->second.get()->data |= data;
        //auto itE = chunks.find({ chunkX, chunkY });
        //itE->second.get()
    }
    else
    {
        chunks.emplace(std::make_pair<ChunkPos, std::unique_ptr<Chunk>>({ chunkX,chunkY }, std::make_unique<Chunk>(chunkX, chunkY, data)));
        edit.emplace(std::make_pair<ChunkPos, std::unique_ptr<Chunk>>({ chunkX,chunkY }, std::make_unique<Chunk>(chunkX, chunkY, 0)));
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
    InitWindow(_width, _height, _name);
    cam.Init(-25.6f, -14.4f, 20.0f);


    //chunks.emplace(std::make_pair<ChunkPos, std::unique_ptr<Chunk>>({-1,0}, std::make_unique<Chunk>(-1, 0, 584388742947276800)));
    //chunks.emplace(std::make_pair<ChunkPos, std::unique_ptr<Chunk>>({-1,0}, std::make_unique<Chunk>(-1, 0, 7918829344391168)));
    //chunks.emplace(std::make_pair<ChunkPos, std::unique_ptr<Chunk>>({-1,0}, std::make_unique<Chunk>(-1, 0, 2017684381581188096)));
    chunks.emplace(std::make_pair<ChunkPos, std::unique_ptr<Chunk>>({0,0}, std::make_unique<Chunk>(0, 0, 0)));
    edit.emplace(std::make_pair<ChunkPos, std::unique_ptr<Chunk>>({ 0,0 }, std::make_unique<Chunk>(0, 0, 0)));
    //edit.emplace(std::make_pair<ChunkPos, std::unique_ptr<Chunk>>({ -1,0 }, std::make_unique<Chunk>(-1, 0, 0)));


    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
            CreateCross(i * 16 + 3 ,j * 16 + 4);

    /*PlaceCell(11, 4);
    PlaceCell(12, 4);
    PlaceCell(12, 6);
    PlaceCell(13, 4);
    PlaceCell(13, 5);*/
    //PlaceCell(11, 4);
    //PlaceCell(11, 6);
    //PlaceCell(12, 3);
    //PlaceCell(13, 3);
    //PlaceCell(14, 3);
    //PlaceCell(15, 3);
    //PlaceCell(15, 4);
    //PlaceCell(15, 5);
    //PlaceCell(14, 6);


    auto get = [](int x, int y, std::unordered_map<ChunkPos, std::unique_ptr<Chunk>, ChunkPosHash>& chunks) -> Chunk*
    {
        auto it = chunks.find({ x, y });
        return (it != chunks.end()) ? it->second.get() : nullptr;
    };

    for (auto& [pos, chunk] : chunks)
    {
        std::unique_ptr<Chunk>& editableChunk = edit.at(pos);

        chunk->upLeft = get(pos.x - 1, pos.y - 1, chunks);
        chunk->up = get(pos.x, pos.y - 1, chunks);
        chunk->upRight = get(pos.x + 1, pos.y - 1, chunks);
        chunk->left = get(pos.x - 1, pos.y, chunks);
        chunk->right = get(pos.x + 1, pos.y, chunks);
        chunk->downLeft = get(pos.x - 1, pos.y + 1, chunks);
        chunk->down = get(pos.x, pos.y + 1, chunks);
        chunk->downRight = get(pos.x + 1, pos.y + 1, chunks);

        editableChunk->upLeft = get(pos.x - 1, pos.y - 1, edit);
        editableChunk->up = get(pos.x, pos.y - 1, edit);
        editableChunk->upRight = get(pos.x + 1, pos.y - 1, edit);
        editableChunk->left = get(pos.x - 1, pos.y, edit);
        editableChunk->right = get(pos.x + 1, pos.y, edit);
        editableChunk->downLeft = get(pos.x - 1, pos.y + 1, edit);
        editableChunk->down = get(pos.x, pos.y + 1, edit);
        editableChunk->downRight = get(pos.x + 1, pos.y + 1, edit);

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

    button.Init(8, 8, 30, 30);

    golMesh = GenGolPlane(8, 8);
    matInstances = LoadMaterialDefault();
    matInstances.shader = golShader;
}

App::~App()
{
    CloseWindow();
}

void App::Update()
{   
    //Texture img = LoadTexture("Resources/grays.png");
    //Texture img = LoadTexture("Resources/but1.png");
    //Texture img = LoadTexture("Resources/but2.png");
    //Texture img = LoadTexture("Resources/pla.png");
    //Texture img = LoadTexture("Resources/pse.png");
    //more = LoadTexture("Resources/more.png");

    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        //DEBUG
        if (IsKeyPressed(KEY_F3))
        {
            debugEnable = !debugEnable;
            SetWindowTitle("Conway's Game of Life (C++ raylib Edition)");
        }
        if (debugEnable)
        {
            SetWindowTitle(TextFormat("Conway's Game of Life (C++ raylib Edition) [zoom: %f ]", cam.GetZoom()));
        }
        
        cam.Update();
        /*camRefresh++;
        if (cam.IsMoving() && camRefresh > 30)
        {
            drawData.clear();
            for (auto& [pos, chunk] : chunks)
            {
                if (cam.CanRender(pos.x, pos.y))
                    drawData.push_back(chunk->drawData);
            }
            rlUpdateShaderBuffer(golBuffer, drawData.data(), drawData.size() * sizeof(DrawChunkData), 0);
            camRefresh = 0;
        }*/


        UpdateUI();

        UpdateGOL(update);
        
        BeginDrawing();
        ClearBackground(WHITE);

        cam.BegingContext();

        RenderGOL();

        //draw a grid centered on the camera
        if (cam.GetZoom() > 5)
        {
            Vector2 m = cam.GetMinWorld();
            Vector2 M = cam.GetMaxWorld();
            for (int i = m.x; i < M.x; i++)
                DrawLine(i, m.y, i, M.y, BLACK);
            for (int j = m.y; j < M.y; j++)
                DrawLine(m.x, j, M.x, j, BLACK);

        }

        cam.EndContext();

        // Draw mouse reference
        //Vector2 mousePos = GetWorldToScreen2D(GetMousePosition(), camera)
        DrawCircleV(GetMousePosition(), 2, DARKGRAY);
        
        {
        //reload
        //if (GetMousePosition().x > 0 && GetMousePosition().x < 100 && GetMousePosition().y > 0 && GetMousePosition().y < 100)
        //    DrawTexturePro(img, { 0,0,16,16 }, { 0, 0, 100, 100 }, { 0,0 }, 0, { 128,159,255,255 });
        //else
        //    DrawTexturePro(img, {0,0,16,16}, { 0, 0, 100, 100 }, { 0,0 }, 0, { 66,112,255,255 });

        //play
        //if (GetMousePosition().x > 0 && GetMousePosition().x < 100 && GetMousePosition().y > 0 && GetMousePosition().y < 100)
        //    DrawTexturePro(img, { 0,0,16,16 }, { 0, 0, 100, 100 }, { 0,0 }, 0, { 160,255,160,255 });
        //else
        //    DrawTexturePro(img, {0,0,16,16}, { 0, 0, 100, 100 }, { 0,0 }, 0, { 0,255,0,255 });

        //pause
        //if (GetMousePosition().x > 0 && GetMousePosition().x < 100 && GetMousePosition().y > 0 && GetMousePosition().y < 100)
        //    DrawTexturePro(img, { 0,0,16,16 }, { 0, 0, 128, 128 }, { 0,0 }, 0, { 255,160,160,255 });
        //else
        //    DrawTexturePro(img, {0,0,16,16}, { 0, 0, 128, 128 }, { 0,0 }, 0, { 255,0,0,255 });

        //button
        //if (GetMousePosition().x > 0 && GetMousePosition().x < 100 && GetMousePosition().y > 0 && GetMousePosition().y < 100)
        //    DrawTexturePro(img, { 0,0,16,16 }, { 0, 0, 100, 100 }, { 0,0 }, 0, { 255,212,212,255 });
        //else
        //    DrawTexturePro(img, {0,0,16,16}, { 0, 0, 100, 100 }, { 0,0 }, 0, WHITE);
        }

        RenderUI();

        if (debugEnable)
        {
            DrawRectangleRounded({ (float)GetMouseX() + 25, (float)GetMouseY() -40, 210,80}, 0.25, 10, DARKBLUE);
            DrawRectangleRounded({ (float)GetMouseX() + 30, (float)GetMouseY() -35, 200,70}, 0.25, 10, SKYBLUE);


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

            int chunkX = cellX < 0 ? (((cellX -8) / 8)) : (cellX / 8);
            int chunkY = cellY < 0 ? (((cellY -8) / 8)) : (cellY / 8);

            DrawTextEx(GetFontDefault(), "Chunk:",
                Vector2Add(GetMousePosition(), { 35, 10 }), 20, 2, BLACK);
            DrawTextEx(GetFontDefault(), TextFormat("[%i, %i]", chunkX, chunkY),
                Vector2Add(GetMousePosition(), { 115, 10 }), 20, 2, BLACK);
        }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
}


void App::UpdateGOL(u32 _update)
{
    if (!_update) return;
    
    drawData.clear();
    std::queue<ChunkPos> markedForDelete;
    std::queue<ChunkPos> markedForAddition;//maybe using this will solve the probleme?

    for (auto& [pos, chunk] : chunks)
    {
        if (pos.x == 0 && pos.y == 16)
        {
            int a = 0;
            a++;
        }
        std::unique_ptr<Chunk>& editableChunk = edit.at(pos);
        chunk->Update(editableChunk);
        editableChunk->CreateNewChunks(markedForAddition);
        if (editableChunk->ShouldDelete())
        {
            markedForDelete.push(pos);
        }
        else if(editableChunk->data != 0 && cam.CanRender(pos.x, pos.y))
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
        if (existE->data != 0 && cam.CanRender(pos.x, pos.y))
            drawData.push_back(existE->drawData);

        markedForAddition.pop();
    }

    chunks.swap(edit);

    rlUpdateShaderBuffer(golBuffer, drawData.data(), drawData.size() * sizeof(DrawChunkData), 0);
    //update = 0;
    return;
}

void App::UpdateUI()
{
    button.Update(GetMouseX(), GetMouseY());

    if (button.Pressed())
    {
        update = 1;
        std::cout << "drawn chunk: " << drawData.size() << "\n";
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
    button.Render();


    //more button
    /*if (GetMousePosition().x > 0 && GetMousePosition().x < 100 && GetMousePosition().y > 0 && GetMousePosition().y < 100)
    {
        DrawRectangleRounded({ 8, 8, 36, 36 }, 0.2, 1, LIGHTGRAY);
        DrawRectangleRoundedLinesEx({ 8, 8, 36, 36 }, 0.2, 1,2, BLACK);

        DrawTexturePro(more, { 0,0,16,16 }, { 10, 10, 32, 32 }, { 0,0 }, 0, { 255,212,212,255 });
    }
    else
    {
        DrawRectangleRounded({ 10, 10, 32, 32 }, 0.2, 1, LIGHTGRAY);
        DrawRectangleRoundedLinesEx({ 10, 10, 32, 32 }, 0.2, 1, 2, BLACK);

        DrawTexturePro(more, { 0,0,16,16 }, { 10, 10, 32, 32 }, { 0,0 }, 0, WHITE);
    }*/
}