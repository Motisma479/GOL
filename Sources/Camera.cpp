#include "Camera.hpp"
#include "rlgl.h"
#include "raymath.h"

void GOL::Camera::Init(f32 _targetX, f32 _targetY, f32 _zoom)
{
    rcam = { 0 };
    rcam.target = { _targetX, _targetY };
    rcam.zoom = _zoom;
}

void GOL::Camera::Update()
{
    // Translate based on mouse right click
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f / rcam.zoom);
        rcam.target = Vector2Add(rcam.target, delta);
    }

    // Zoom based on mouse wheel
    float wheel = GetMouseWheelMove();
    if (wheel != 0)
    {
        // Get the world point that is under the mouse
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), rcam);

        // Set the offset to where the mouse is
        rcam.offset = GetMousePosition();

        // Set the target to match, so that the camera maps the world space point
        // under the cursor to the screen space point under the cursor at any zoom
        rcam.target = mouseWorldPos;

        // Zoom increment
        // Uses log scaling to provide consistent zoom speed
        float scale = 0.2f * wheel;
        rcam.zoom = Clamp(expf(logf(rcam.zoom) + scale), 0.125f, 64.0f);
    }
}

void GOL::Camera::BegingContext()
{
	BeginMode2D(rcam);
}

void GOL::Camera::EndContext()
{
	EndMode2D();
}

bool GOL::Camera::CanRender(s32 _x, s32 _y)
{
    Vector2 topLeft = GetScreenToWorld2D({ 0, 0 }, rcam);
    topLeft += {-1, -1};
    Vector2 bottomRight = GetScreenToWorld2D(
        { (float)1024, (float)576 },
        rcam
    );

    return _x >= topLeft.x &&
        _x <= bottomRight.x &&
        _y >= topLeft.y &&
        _y <= bottomRight.y;
}