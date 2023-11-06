#pragma once
#include <vector>
#include <array>

/*-----------------------------------------------------------------------------*/
/*

░░░░░░░░░░
░░░░██░░░░
░░░░░░██░░
░░██████░░
░░░░░░░░░░
coordinates start from top left of the shape.

*/
std::vector<std::array<int, 2>> genShape_1(int x, int y)
{
    std::vector<std::array<int, 2>> coordinates;

    coordinates.push_back({ x + 1, y });
    coordinates.push_back({ x + 2, y + 1 });
    coordinates.push_back({ x, y + 2 });
    coordinates.push_back({ x + 1, y + 2 });
    coordinates.push_back({ x + 2, y + 2 });

    return coordinates;
}
/*-----------------------------------------------------------------------------*/
/*

░░░░░░░░░░
░░░░██░░░░
░░██░░██░░
░░██░░██░░
░░██░░██░░
░░░░██░░░░
░░░░░░░░░░
coordinates start from top left of the shape.

*/
std::vector<std::array<int, 2>> genShape_2(int x, int y)
{
    std::vector<std::array<int, 2>> coordinates;

    coordinates.push_back({ x + 1, y });
    coordinates.push_back({ x, y + 1 });
    coordinates.push_back({ x + 2, y + 1 });
    coordinates.push_back({ x, y + 2 });
    coordinates.push_back({ x + 2, y + 2 });
    coordinates.push_back({ x, y + 3 });
    coordinates.push_back({ x + 2, y + 3 });
    coordinates.push_back({ x + 1, y + 4 });

    return coordinates;
}
/*-----------------------------------------------------------------------------*/
/*

░░░░░░░░░░
░░██░░░░░░
░░██████░░
░░░░██░░░░
░░░░░░░░░░
coordinates start from top left of the shape.

*/
std::vector<std::array<int, 2>> genShape_3(int x, int y)
{
    std::vector<std::array<int, 2>> coordinates;

    coordinates.push_back({ x, y });
    coordinates.push_back({ x, y + 1 });
    coordinates.push_back({ x + 1, y + 1 });
    coordinates.push_back({ x + 2, y + 1 });
    coordinates.push_back({ x + 1, y + 2 });

    return coordinates;
}
/*-----------------------------------------------------------------------------*/
/*

░░░░░░░░░░░░
░░░░████░░░░
░░████████░░
░░████████░░
░░░░████░░░░
░░░░░░░░░░░░
coordinates start from top left of the shape.

*/
std::vector<std::array<int, 2>> genShape_4(int x, int y)
{
    std::vector<std::array<int, 2>> coordinates;

    coordinates.push_back({ x + 1, y });
    coordinates.push_back({ x + 2, y });
    coordinates.push_back({ x    , y + 1 });
    coordinates.push_back({ x + 1, y + 1 });
    coordinates.push_back({ x + 2, y + 1 });
    coordinates.push_back({ x + 3, y + 1 });
    coordinates.push_back({ x    , y + 2 });
    coordinates.push_back({ x + 1, y + 2 });
    coordinates.push_back({ x + 2, y + 2 });
    coordinates.push_back({ x + 3, y + 2 });
    coordinates.push_back({ x + 1, y + 3 });
    coordinates.push_back({ x + 2, y + 3 });

    return coordinates;
}