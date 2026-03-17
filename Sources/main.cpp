#include "App.hpp"
#include <iostream>
#include <bit>
#include <bitset>

int main()
{
	App app(1024, 576, "Conway's Game of Life (C++ raylib Edition)");

	app.Update();

	u8 off = 1;
	u8 test = 1 << off;

	std::cout << std::bitset<8>(test) << std::endl;

	test = (1 << 7) >> off;

	std::cout << std::bitset<8>(test) << std::endl;

	return 0;
}