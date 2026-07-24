#include "Cell.hpp"

//u8 used; == 0b00000000
// 000  012  (x-1)(x)(x+1)  (y-1)(y-1)(y-1)
// 0 0  3 4  (x-1)   (x+1)  (y)       (y)
// 000  567  (x-1)(x)(x+1)  (y+1)(y+1)(y+1)

Cell::Cell(s32 _x, s32 _y) :x(_x), y(_y), around(0), aroundToCheck(0) {}

void Cell::IsNextTo(Cell& _cell)
{
    bool result = _cell.x >= x-1 &&
        _cell.x <= x+1 &&
        _cell.y >= y-1 &&
        _cell.y <= y+1 ;

    if (result)
    {
        u8 off = 0;

        if(_cell.x == x-1)
            off = (_cell.y == y-1 ? 0 : _cell.y == y ? 3 : 5);
        else if (_cell.x == x)
            off = (_cell.y == y - 1 ? 1 : 6);
        else
            off = (_cell.y == y - 1 ? 2 : _cell.y == y ? 4 : 7);

        around |= 1 << off;

        _cell.around |= 128 >> off;
    }
}

bool Cell::CheckAround(Cell& _cell)
{
    bool result = _cell.x >= x - 2 &&
        _cell.x <= x + 2 &&
        _cell.y >= y - 2 &&
        _cell.y <= y + 2;

    if (!result) return false;

    if (_cell.y == y - 2 && _cell.x == x - 2)
    {
        aroundToCheck |= 1;
        _cell.aroundToCheck |= 128 >> 0;
        return true;
    }

    if (_cell.y == y - 2 && _cell.x == x + 2)
    {
        aroundToCheck |= 1 << 2;
        _cell.aroundToCheck |= 128 >> 2;
        return true;
    }

    if (_cell.y == y + 2 && _cell.x == x - 2)
    {
        aroundToCheck |= 1 << 5;
        _cell.aroundToCheck |= 128 >> 5;
        return true;
    }
    if (_cell.y == y + 2 && _cell.x == x + 2)
    {
        aroundToCheck |= 1 << 7;
        _cell.aroundToCheck |= 128 >> 7;
        return true;
    }
   


    if (_cell.y == y - 2)
    {
        if (_cell.x == x - 1)
        {
            aroundToCheck |= 1 | 1 << 1;
            _cell.aroundToCheck |= 128 >> 0 | 128 >> 1;
        }
        else if (_cell.x == x + 1)
        {
            aroundToCheck |= 1 << 1 | 1 << 2;
            _cell.aroundToCheck |= 128 >> 0 | 128 >> 2;
        }
        else
        {
            aroundToCheck |= 1 | 1 << 1 | 1 <<2;
            _cell.aroundToCheck |= 128 >> 0 | 128 >> 1 | 128 >> 2;
        }
    }

    if (_cell.y == y + 2)
    {
        if (_cell.x == x - 1)
        {
            aroundToCheck |= 1 << 5 | 1 << 6;
            _cell.aroundToCheck |= 128 >> 5 | 128 >> 6;
        }
        else if (_cell.x == x + 1)
        {
            aroundToCheck |= 1 << 6 | 1 << 7;
            _cell.aroundToCheck |= 128 >> 6 | 128 >> 7;
        }
        else
        {
            aroundToCheck |= 1 << 5 | 1 << 6 | 1 << 7;
            _cell.aroundToCheck |= 128 >> 5 | 128 >> 6 | 128 >> 7;
        }
    }

    if (_cell.x == x - 2)
    {
        if (_cell.y == y - 1)
        {
            aroundToCheck |= 1 | 1 << 3;
            _cell.aroundToCheck |= 128 >> 0 | 128 >> 3;
        }
        else if (_cell.y == y + 1)
        {
            aroundToCheck |= 1 << 3 | 1 << 5;
            _cell.aroundToCheck |= 128 >> 3 | 128 >> 5;
        }
        else
        {
            aroundToCheck |= 1 | 1 << 3 | 1 << 5;
            _cell.aroundToCheck |= 128 >> 0 | 128 >> 3 | 128 >> 5;
        }
    }

    if (_cell.x == x + 2)
    {
        if (_cell.y == y - 1)
        {
            aroundToCheck |= 1 << 2 | 1 << 4;
            _cell.aroundToCheck |= 128 >> 2 | 128 >> 4;
        }
        else if (_cell.y == y + 1)
        {
            aroundToCheck |= 1 << 4 | 1 << 7;
            _cell.aroundToCheck |= 128 >> 4 | 128 >> 7;
        }
        else
        {
            aroundToCheck |= 1 << 2 | 1 << 4 | 1 << 7;
            _cell.aroundToCheck |= 128 >> 2 | 128 >> 4 | 128 >> 7;
        }
    }


    return true;
}

void Cell::ValidateToCheck()
{
    aroundToCheck &= ~around;
    
    if (!((around >> 0) & 1) && ((around >> 1) & 1) && ((around >> 3) & 1)) aroundToCheck |= 1;
    
    if (!((around >> 1) & 1) && (((around >> 0) & 1) + ((around >> 2) & 1) + ((around >> 3) & 1) + ((around >> 4) & 1)) >= 2) aroundToCheck |= 1 << 1;//
    //if (!((around >> 1) & 1) && ((around >> 0) & 1) && ((around >> 2) & 1)) aroundToCheck |= 1 << 1;//

    if (!((around >> 2) & 1) && ((around >> 1) & 1) && ((around >> 4) & 1)) aroundToCheck |= 1 << 2;
    
    if (!((around >> 3) & 1) && (((around >> 0) & 1) + ((around >> 5) & 1) + ((around >> 1) & 1) + ((around >> 6) & 1)) >= 2) aroundToCheck |= 1 << 3;//
    //if (!((around >> 3) & 1) && ((around >> 0) & 1) && ((around >> 5) & 1)) aroundToCheck |= 1 << 3;//
    if (!((around >> 4) & 1) && (((around >> 2) & 1) + ((around >> 7) & 1) + ((around >> 1) & 1) + ((around >> 6) & 1)) >= 2) aroundToCheck |= 1 << 4;//
    //if (!((around >> 4) & 1) && ((around >> 2) & 1) && ((around >> 7) & 1)) aroundToCheck |= 1 << 4;//
    
    if (!((around >> 5) & 1) && ((around >> 3) & 1) && ((around >> 6) & 1)) aroundToCheck |= 1 << 5;
    
    if (!((around >> 6) & 1) && (((around >> 5) & 1) + ((around >> 7) & 1) + ((around >> 3) & 1) + ((around >> 4) & 1)) >= 2) aroundToCheck |= 1 << 6;//
    //if (!((around >> 6) & 1) && ((around >> 5) & 1) && ((around >> 7) & 1)) aroundToCheck |= 1 << 6;//
    
    if (!((around >> 7) & 1) && ((around >> 6) & 1) && ((around >> 4) & 1)) aroundToCheck |= 1 << 7;
}

std::vector<std::pair<s32, s32>> Cell::GetToCheck()
{
    std::vector<std::pair<s32, s32>> result = {};
    result.reserve(8);

    if (((aroundToCheck >> 0) & 1))
        result.push_back(std::make_pair(x - 1, y - 1));
    if (((aroundToCheck >> 1) & 1)) 
        result.push_back(std::make_pair(x , y - 1));
    if (((aroundToCheck >> 2) & 1)) 
        result.push_back(std::make_pair(x + 1, y - 1));
    if (((aroundToCheck >> 3) & 1)) 
        result.push_back(std::make_pair(x - 1, y ));
    if (((aroundToCheck >> 4) & 1)) 
        result.push_back(std::make_pair(x + 1, y ));
    if (((aroundToCheck >> 5) & 1)) 
        result.push_back(std::make_pair(x - 1, y + 1));
    if (((aroundToCheck >> 6) & 1)) 
        result.push_back(std::make_pair(x, y + 1));
    if (((aroundToCheck >> 7) & 1)) 
        result.push_back(std::make_pair(x + 1, y + 1));

    return result;
}