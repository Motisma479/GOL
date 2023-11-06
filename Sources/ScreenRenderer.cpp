#include "ScreenRenderer.hpp"

#include <chrono>

using namespace Maths;

const Vec3 lightDir = Vec3(1, 1, -0.5f).UnitVector();
const Vec3 lightCol = Vec3(0.5f, 0.5f, 0.5f).UnitVector();
const float smoothness = 1024.0f;

ScreenRenderer::ScreenRenderer(IVec2 resIn) : res(resIn)
{
    pixelCount = res.x * res.y;
    imageData = new unsigned int[pixelCount];
}

void ScreenRenderer::DrawScreen()
{
    for (s32 i = 0; i <= pixelCount; i++)
    {
        Color4 col = Color4(255,0,0);
        unsigned int c = (col.r << 16) + (col.g << 8) + col.b;
        imageData[i] = c;
    }
}
