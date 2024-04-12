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

░░░░░░░░░░░░░░░░░░░░░░░░░░
░░░░░░░░░░██████░░░░░░░░░░
░░░░░░██████████████░░░░░░
░░░░██████████████████░░░░
░░░░██████████████████░░░░
░░██████████████████████░░
░░██████████████████████░░
░░██████████████████████░░
░░░░██████████████████░░░░
░░░░██████████████████░░░░
░░░░░░██████████████░░░░░░
░░░░░░░░░░██████░░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░░░░
coordinates start from top left of the shape.

*/
std::vector<std::array<int, 2>> genShape_4(int x, int y)
{
    std::vector<std::array<int, 2>> coordinates;

    coordinates.push_back({ x + 4 , y      });
    coordinates.push_back({ x + 5 , y      });
    coordinates.push_back({ x + 6 , y      });

    coordinates.push_back({ x + 2 , y + 1  });
    coordinates.push_back({ x + 3 , y + 1  });
    coordinates.push_back({ x + 4 , y + 1  });
    coordinates.push_back({ x + 5 , y + 1  });
    coordinates.push_back({ x + 6 , y + 1  });
    coordinates.push_back({ x + 7 , y + 1  });
    coordinates.push_back({ x + 8 , y + 1  });
 
    coordinates.push_back({ x + 1 , y + 2  });
    coordinates.push_back({ x + 2 , y + 2  });
    coordinates.push_back({ x + 3 , y + 2  });
    coordinates.push_back({ x + 4 , y + 2  });
    coordinates.push_back({ x + 5 , y + 2  });
    coordinates.push_back({ x + 6 , y + 2  });
    coordinates.push_back({ x + 7 , y + 2  });
    coordinates.push_back({ x + 8 , y + 2  });
    coordinates.push_back({ x + 9 , y + 2  });

    coordinates.push_back({ x + 1 , y + 3  });
    coordinates.push_back({ x + 2 , y + 3  });
    coordinates.push_back({ x + 3 , y + 3  });
    coordinates.push_back({ x + 4 , y + 3  });
    coordinates.push_back({ x + 5 , y + 3  });
    coordinates.push_back({ x + 6 , y + 3  });
    coordinates.push_back({ x + 7 , y + 3  });
    coordinates.push_back({ x + 8 , y + 3  });
    coordinates.push_back({ x + 9 , y + 3  });

    coordinates.push_back({ x     , y + 4  });
    coordinates.push_back({ x + 1 , y + 4  });
    coordinates.push_back({ x + 2 , y + 4  });
    coordinates.push_back({ x + 3 , y + 4  });
    coordinates.push_back({ x + 4 , y + 4  });
    coordinates.push_back({ x + 5 , y + 4  });
    coordinates.push_back({ x + 6 , y + 4  });
    coordinates.push_back({ x + 7 , y + 4  });
    coordinates.push_back({ x + 8 , y + 4  });
    coordinates.push_back({ x + 9 , y + 4  });
    coordinates.push_back({ x + 10, y + 4  });

    coordinates.push_back({ x     , y + 5  });
    coordinates.push_back({ x + 1 , y + 5  });
    coordinates.push_back({ x + 2 , y + 5  });
    coordinates.push_back({ x + 3 , y + 5  });
    coordinates.push_back({ x + 4 , y + 5  });
    coordinates.push_back({ x + 5 , y + 5  });
    coordinates.push_back({ x + 6 , y + 5  });
    coordinates.push_back({ x + 7 , y + 5  });
    coordinates.push_back({ x + 8 , y + 5  });
    coordinates.push_back({ x + 9 , y + 5  });
    coordinates.push_back({ x + 10, y + 5  });

    coordinates.push_back({ x     , y + 6  });
    coordinates.push_back({ x + 1 , y + 6  });
    coordinates.push_back({ x + 2 , y + 6  });
    coordinates.push_back({ x + 3 , y + 6  });
    coordinates.push_back({ x + 4 , y + 6  });
    coordinates.push_back({ x + 5 , y + 6  });
    coordinates.push_back({ x + 6 , y + 6  });
    coordinates.push_back({ x + 7 , y + 6  });
    coordinates.push_back({ x + 8 , y + 6  });
    coordinates.push_back({ x + 9 , y + 6  });
    coordinates.push_back({ x + 10, y + 6  });

    coordinates.push_back({ x + 1 , y + 7  });
    coordinates.push_back({ x + 2 , y + 7  });
    coordinates.push_back({ x + 3 , y + 7  });
    coordinates.push_back({ x + 4 , y + 7  });
    coordinates.push_back({ x + 5 , y + 7  });
    coordinates.push_back({ x + 6 , y + 7  });
    coordinates.push_back({ x + 7 , y + 7  });
    coordinates.push_back({ x + 8 , y + 7  });
    coordinates.push_back({ x + 9 , y + 7  });

    coordinates.push_back({ x + 1 , y + 8  });
    coordinates.push_back({ x + 2 , y + 8  });
    coordinates.push_back({ x + 3 , y + 8  });
    coordinates.push_back({ x + 4 , y + 8  });
    coordinates.push_back({ x + 5 , y + 8  });
    coordinates.push_back({ x + 6 , y + 8  });
    coordinates.push_back({ x + 7 , y + 8  });
    coordinates.push_back({ x + 8 , y + 8  });
    coordinates.push_back({ x + 9 , y + 8  });

    coordinates.push_back({ x + 2 , y + 9  });
    coordinates.push_back({ x + 3 , y + 9  });
    coordinates.push_back({ x + 4 , y + 9  });
    coordinates.push_back({ x + 5 , y + 9  });
    coordinates.push_back({ x + 6 , y + 9  });
    coordinates.push_back({ x + 7 , y + 9  });
    coordinates.push_back({ x + 8 , y + 9  });

    coordinates.push_back({ x + 4 , y + 10 });
    coordinates.push_back({ x + 5 , y + 10 });
    coordinates.push_back({ x + 6 , y + 10 });

    return coordinates;
}
/*-----------------------------------------------------------------------------*/
/*

░░░░░░░░░░░░░░░░░░
░░░░██░░░░░░░░░░░░
░░░░░░░░██░░░░░░░░
░░████░░░░██████░░
░░░░░░░░░░░░░░░░░░
coordinates start from top left of the shape.

*/
std::vector<std::array<int, 2>> genShape_5(int x, int y)
{
    std::vector<std::array<int, 2>> coordinates;

    coordinates.push_back({ x + 1 , y });

    coordinates.push_back({ x + 3 , y + 1 });
    
    coordinates.push_back({ x     , y + 2 });
    coordinates.push_back({ x + 1 , y + 2 });
    coordinates.push_back({ x + 4 , y + 2 });
    coordinates.push_back({ x + 5 , y + 2 });
    coordinates.push_back({ x + 6 , y + 2 });

    return coordinates;
}