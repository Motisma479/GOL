#pragma once
#include <raylib.h>
#include "Core/Types.hpp"

namespace GOL
{
	class Camera
	{
	private:
		Camera2D rcam;
		bool move;
	public:
		void Init(f32 _targetX, f32 _targetY, f32 _zoom);
		void Update();
		f32 GetZoom();
		f32 GetTargetX();
		f32 GetTargetY();

		Vector2 GetMinWorld();
		Vector2 GetMaxWorld();

		void BegingContext();
		void EndContext();
		
		bool CanRender(s32 _x, s32 _y);
		bool IsMoving();
		Vector2 ScreenPosToWorlPos(Vector2 _pos);
	};
}