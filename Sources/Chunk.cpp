#include "Chunk.hpp"

#include <bitset>
#include <bit>

Chunk::Chunk(s32 _x, s32 _y, u64 _data) : x(_x), y(_y), data(_data),
up(nullptr), down(nullptr), right(nullptr), left(nullptr), upRight(nullptr), downRight(nullptr), upLeft(nullptr), downLeft(nullptr),
life(0) {}

Chunk::~Chunk()
{
    if (up)
    {
        up->down = nullptr;
    }

    if (down)
    {
        down->up = nullptr;
    }

    if (right)
    {
        right->left = nullptr;
    }

    if (left)
    {
        left->right = nullptr;
    }

    if (upRight)
    {
        upRight->downLeft = nullptr;
    }

    if (downLeft)
    {
        downLeft->upRight = nullptr;
    }

    if (downRight)
    {
        downRight->upLeft = nullptr;
    }

    if (upLeft)
    {
        upLeft->downRight = nullptr;
    }

}

void Chunk::Update(std::unique_ptr<Chunk>& _edit)
{
    _edit->data = data;
    _edit->life = life;
    for (u32 i = 0; i < 64; ++i)
    {
        u8 around = 0;
        if (i == 0)
        {
            if (upLeft)
            {
                around |= ((upLeft->data >> 63) & 1) << 0;
            }
            if (up)
            {
                around |= ((up->data >> 56) & 1) << 1 |
                    ((up->data >> 57) & 1) << 2;
            }
            if (left)
            {
                around |= ((left->data >> 7) & 1) << 3 |
                    ((left->data >> 15) & 1) << 5;
            }

            around |= ((data >> i + 1) & 1) << 4 |
                ((data >> i + 8) & 1) << 6 |
                ((data >> i + 9) & 1) << 7;
        }
        else if (i <= 6)
        {
            if (up)
            {
                around |= ((up->data >> 55 + i) & 1) << 0 |
                    ((up->data >> 56 + i) & 1) << 1 |
                    ((up->data >> 57 + i) & 1) << 2;
            }

            around |= ((data >> i - 1) & 1) << 3 |
                ((data >> i + 1) & 1) << 4 |
                ((data >> i + 7) & 1) << 5 |
                ((data >> i + 8) & 1) << 6 |
                ((data >> i + 9) & 1) << 7;
        }
        else if (i == 7)
        {
            if (up)
            {
                around |= ((up->data >> 62) & 1) << 0 |
                    ((up->data >> 63) & 1) << 1;
            }
            if (upRight)
            {
                around |= ((upRight->data >> 56) & 1) << 2;
            }
            if (right)
            {
                around |= ((right->data >> 0) & 1) << 4 |
                    ((right->data >> 8) & 1) << 7;
            }

            around |= ((data >> i - 1) & 1) << 3 |
                ((data >> i + 7) & 1) << 5 |
                ((data >> i + 8) & 1) << 6;
        }
        else if (i == 8 || i == 16 || i == 24 || i == 32 || i == 40 || i == 48)
        {
            if (left)
            {
                around |= ((left->data >> i - 1) & 1) << 0 |
                    ((left->data >> i+7) & 1) << 3 |
                    ((left->data >> i+15) & 1) << 5;
            }
            around |= ((data >> i - 8) & 1) << 1 |
                ((data >> i - 7) & 1) << 2 |
                ((data >> i + 1) & 1) << 4 |
                ((data >> i + 8) & 1) << 6 |
                ((data >> i + 9) & 1) << 7;
        }
        else if (i == 15 || i == 23 || i == 31 || i == 39 || i == 47 || i == 55)
        {
            if (right)
            {
                around |= ((right->data >> i - 15) & 1) << 2 |
                    ((right->data >> i - 7) & 1) << 4 |
                    ((right->data >> i + 1) & 1) << 7;
            }
            
            around |= ((data >> i - 9) & 1) << 0 |
                ((data >> i - 8) & 1) << 1 |
                ((data >> i - 1) & 1) << 3 |
                ((data >> i + 7) & 1) << 5 |
                ((data >> i + 8) & 1) << 6;
        }
        else if (i == 56)
        {
            if (left)
            {
                around |= ((left->data >> 55) & 1) << 0 |
                    ((left->data >> 63) & 1) << 3;
            }
            if (downLeft)
            {
                around |= ((downLeft->data >> 7) & 1) << 5;
            }
            if (down)
            {
                around |= ((down->data >> 0) & 1) << 6 |
                    ((down->data >> 1) & 1) << 7;
            }
            

            around |= ((data >> i - 8) & 1) << 1 |
                ((data >> i - 7) & 1) << 2 |
                ((data >> i + 1) & 1) << 4;
        }
        else if (i > 56 && i < 63)
        {   
            around |= ((data >> i - 9) & 1) << 0 |
                ((data >> i - 8) & 1) << 1 |
                ((data >> i - 7) & 1) << 2 |
                ((data >> i - 1) & 1) << 3 |
                ((data >> i + 1) & 1) << 4;
                

            if (down)
            {
                around |= ((down->data >> 0 + (i - 57)) & 1) << 5 |
                    ((down->data >> 1 + (i - 57)) & 1) << 6 |
                    ((down->data >> 2 + (i - 57)) & 1) << 7;
            }
        }
        else if (i == 63)
        {
            if (right)
            {
                around |= ((right->data >> 48) & 1) << 2 |
                    ((right->data >> 56) & 1) << 4;
            }

            if (down)
            {
                around |= ((down->data >> 6) & 1) << 5 |
                    ((down->data >> 7) & 1) << 6;
            }
            if (downRight)
            {
                around |= ((downRight->data >> 0) & 1) << 7;
            }
            

            around |= ((data >> i - 9) & 1) << 0 |
                ((data >> i - 8) & 1) << 1 |
                ((data >> i - 1) & 1) << 3;
        }
        else
        {
            around = ((data >> i - 9) & 1) << 0 |
                ((data >> i - 8) & 1) << 1 |
                ((data >> i - 7) & 1) << 2 |
                ((data >> i - 1) & 1) << 3 |
                ((data >> i + 1) & 1) << 4 |
                ((data >> i + 7) & 1) << 5 |
                ((data >> i + 8) & 1) << 6 |
                ((data >> i + 9) & 1) << 7;
        }
        u8 aroundNum = std::popcount(around);

        if (aroundNum == 3)
            _edit->data |= (u64)1 << i;

        if (aroundNum < 2 || aroundNum > 3)
            _edit->data &= ~((u64)1 << i);
    }

    if (_edit->data == 0 && (x != 0 || y != 0 )) _edit->life++;
    else _edit->life = 0;
}


//Must be executed from the edited list
void Chunk::CreateNewChunks(std::queue<ChunkPos>& _toAdd)
{
    bool createUpLeft = ((data >> 0) & 1);
    bool createUpRight = ((data >> 7) & 1);
    bool createDownLeft = ((data >> 56) & 1);
    bool createDownRight = ((data >> 63) & 1);

    bool createUp = false;
    if (((data >> 0) & 1) && ((data >> 1) & 1) && (upLeft && ((upLeft->data >> 63) & 1) || left && ((left->data >> 7) & 1))) createUp = true;
    if (((data >> 6) & 1) && ((data >> 7) & 1) && (upRight && ((upRight->data >> 56) & 1) || right && ((right->data >> 0) & 1))) createUp = true;
    u8 u = ((data >> 0) & 1) |
        ((data >> 1) & 1) << 1 |
        ((data >> 2) & 1) << 2 |
        ((data >> 3) & 1) << 3|
        ((data >> 4) & 1) << 4|
        ((data >> 5) & 1) << 5|
        ((data >> 6) & 1) << 6|
        ((data >> 7) & 1) << 7;
    if (u & (u >> 1) & (u >> 2))
    {
        createUp = true;
    }

    bool createLeft = false;
    if (((data >> 0) & 1) && ((data >> 8) & 1) && (upLeft && ((upLeft->data >> 63) & 1) || up && ((up->data >> 56) & 1))) createLeft = true;
    if (((data >> 48) & 1) && ((data >> 56) & 1) && (downLeft && ((downLeft->data >> 7) & 1) || down && ((down->data >> 0) & 1))) createLeft = true;
    u8 l = ((data >> 0) & 1) | 
        ((data >> 8 ) & 1) << 1 |
        ((data >> 16) & 1) << 2 |
        ((data >> 24) & 1) << 3 |
        ((data >> 32) & 1) << 4 |
        ((data >> 40) & 1) << 5 |
        ((data >> 48) & 1) << 6 |
        ((data >> 56) & 1) << 7;
    if (l & (l >> 1) & (l >> 2))
    {
        createLeft = true;
    }

    bool createRight = false;
    if (((data >> 7) & 1) && ((data >> 15) & 1) && (upRight && ((upRight->data >> 56) & 1) || up && ((up->data >> 63) & 1))) createRight = true;
    if (((data >> 55) & 1) && ((data >> 63) & 1) && (downRight && ((downRight->data >> 0) & 1) || down && ((down->data >> 7) & 1))) createRight = true;
    u8 r = ((data >> 7 ) & 1) |
        ((data >> 15) & 1) << 1 |
        ((data >> 23) & 1) << 2 |
        ((data >> 31) & 1) << 3 |
        ((data >> 39) & 1) << 4 |
        ((data >> 47) & 1) << 5 |
        ((data >> 55) & 1) << 6 |
        ((data >> 64) & 1) << 7;
    if (r & (r >> 1) & (r >> 2))
    {
        createRight = true;
    }

    bool createDown = false;
    if (((data >> 56) & 1) && ((data >> 57) & 1) && ((downLeft && ((downLeft->data >> 7) & 1)) || (left && ((left->data >> 63) & 1)))) createDown = true;
    if (((data >> 62) & 1) && ((data >> 63) & 1) && ((downRight && ((downRight->data >> 0) & 1)) || (right && ((right->data >> 56) & 1)))) createDown = true;
    u8 d = ((data >> 56) & 1) |
        ((data >> 57) & 1) << 1 |
        ((data >> 58) & 1) << 2 |
        ((data >> 59) & 1) << 3 |
        ((data >> 60) & 1) << 4 |
        ((data >> 61) & 1) << 5 |
        ((data >> 63) & 1) << 6 |
        ((data >> 63) & 1) << 7;
    if (d & (d >> 1) & (d >> 2))
    {
        createDown = true;
    }

    if (createUp)
    {
        if (!up)
        {
            s32 nX = x;
            s32 nY = y - 1;

            _toAdd.push({ nX, nY });
        }
    }
    if (createDown)
    {
        if (!down)
        {
            s32 nX = x;
            s32 nY = y + 1;

            _toAdd.push({ nX, nY });
        }
    }
    if (createLeft)
    {
        if (!left)
        {
            s32 nX = x - 1;
            s32 nY = y;

            _toAdd.push({ nX, nY });
        }
    }
    if (createRight)
    {
        if (!right)
        {
            s32 nX = x + 1;
            s32 nY = y;

            _toAdd.push({ nX, nY });
        }
    }

    
    if (createUpLeft)
    {
        if (!upLeft)
        {
            s32 nX = x - 1;
            s32 nY = y - 1;

            _toAdd.push({ nX, nY });
        }
    }
    if (createUpRight)
    {
        if (!upRight)
        {
            s32 nX = x + 1;
            s32 nY = y - 1;

            _toAdd.push({ nX, nY });
        }
    }
    if (createDownLeft)
    {
        if (!downLeft)
        {
            s32 nX = x - 1;
            s32 nY = y + 1;

            _toAdd.push({ nX, nY });
        }
    }
    if (createDownRight)
    {
        if (!downRight)
        {
            s32 nX = x + 1;
            s32 nY = y + 1;

            _toAdd.push({ nX, nY });
        }
    }
    
}

bool Chunk::ShouldDelete()
{
    return life > 10; //return true if the life keep increasing for 100 update
}

Chunk* Chunk::Get(ChunkPos _xy, std::unordered_map<ChunkPos, std::unique_ptr<Chunk>, ChunkPosHash>& _chunks)
{
    auto it = _chunks.find(_xy);
    return (it != _chunks.end()) ? it->second.get() : nullptr;
}

void Chunk::DoLinks(std::unordered_map<ChunkPos, std::unique_ptr<Chunk>, ChunkPosHash>& _target)
{

    Chunk* cUL = Get({ x - 1, y - 1 }, _target);
    if (cUL) cUL->downRight = this;

    Chunk* cU = Get({ x, y - 1 }, _target);
    if (cU) cU->down = this;

    Chunk* cUR = Get({ x + 1, y - 1 }, _target);
    if (cUR) cUR->downLeft = this;

    Chunk* cL = Get({ x - 1, y }, _target);
    if (cL) cL->right = this;

    Chunk* cR = Get({ x + 1, y }, _target);
    if (cR) cR->left = this;

    Chunk* cDL = Get({ x - 1, y + 1 }, _target);
    if (cDL) cDL->upRight = this;

    Chunk* cD = Get({ x, y + 1 }, _target);
    if (cD) cD->up = this;

    Chunk* cDR = Get({ x + 1, y + 1 }, _target);
    if (cDR) cDR->upLeft = this;

    upLeft = cUL;   up = cU;   upRight = cUR;
    left = cL;                 right = cR;
    downLeft = cDL; down = cD; downRight = cDR;
}