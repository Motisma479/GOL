#include "App.hpp"

#include <iostream>
#include <unordered_map>
#include <bitset>
#include <bit>

App::App(s32 _width, s32 _height, const char* _name)
{
    InitWindow(_width, _height, _name);
    
    cam.Init(-25.6f, -14.4f, 20.0f);
}

App::~App()
{
    CloseWindow();
}

void CreateCross(std::vector<Cell>& cells, s32 x, s32 y)
{
    cells.push_back({ x,y });
    cells.push_back({ x,y-1 });
    cells.push_back({ x,y+1 });
    cells.push_back({ x-1,y });
    cells.push_back({ x+1,y });
}

void App::Update()
{
    //aliveCells.push_back({ 0,0 });
    //aliveCells.push_back({ 1,0 });
    //aliveCells.push_back({ 2,0 });
    //aliveCells.push_back({ 2,-1 });
    //aliveCells.push_back({ 1,-2 });

    //CreateCross(aliveCells, 0, 0);


    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
            CreateCross(aliveCells, i * 10, j * 10);
    

    

    u32 ugol = 0;

    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        cam.Update();
    
        UpdateGOL(ugol);
        ugol++;
        if (ugol > 500) ugol = 0;
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        RenderGOL();

        // Draw mouse reference
        //Vector2 mousePos = GetWorldToScreen2D(GetMousePosition(), camera)
        DrawCircleV(GetMousePosition(), 4, DARKGRAY);
       
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
}


struct PairHash {
    std::size_t operator()(const std::pair<s32, s32>& p) const {
        return std::hash<s32>()(p.first) ^ (std::hash<s32>()(p.second) << 1);
    }
};
void App::UpdateGOL(u32 _update)
{
    if (_update != 500) return;

    //this can be greatly optimised by passing the storage per cell in a storage by zone
    std::unordered_map<std::pair<s32, s32>, std::vector<u32>, PairHash> toCreate;
    std::vector<u32> toDelete;
   
    for (u32 i = 0; i < aliveCells.size(); ++i)
    {
        for (u32 j = i + 1; j < aliveCells.size(); ++j)
        {
            if (aliveCells[i].CheckAround(aliveCells[j]))
                aliveCells[i].IsNextTo(aliveCells[j]);
        }

        aliveCells[i].ValidateToCheck();

        const std::vector<std::pair<s32, s32>>& toCheck = aliveCells[i].GetToCheck();

        for (const auto& tc : toCheck)
        {
            if (auto found = toCreate.find(tc); found != toCreate.end())
            {
                found->second.push_back(i);
            }
            else toCreate.insert(std::make_pair(tc, std::vector<u32>{ i }));
        }

        s32 around = std::popcount(aliveCells[i].around);
        if (around < 2 || around > 3)
            toDelete.push_back(i);

        aliveCells[i].around = 0;
        aliveCells[i].aroundToCheck = 0;
    }


    //do that in the main loop
    for (const auto& tc : toCreate)
    {
        Cell c = { tc.first.first, tc.first.second };

        for (u32 v : tc.second)
        {
            c.IsNextTo(aliveCells[v]);
            aliveCells[v].around = 0;
        }

        s32 around = std::popcount(c.around);
        c.around = 0;
        
        if (around == 3)
            aliveCells.push_back(c);
    }

    u32 presize = aliveCells.size();
    for (const auto& td : toDelete)
    {
        aliveCells.erase(aliveCells.begin() + (td - (presize - aliveCells.size())));
    }
}

void App::UpdateUI()
{

}

void App::RenderGOL()
{
    cam.BegingContext();

    for (const Cell& cell : aliveCells)
    {
        if(cam.CanRender(cell.x, cell.y))
            DrawPixel(cell.x, cell.y, DARKBLUE);
    }

    cam.EndContext();
}

void App::RenderUI()
{

}