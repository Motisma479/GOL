#pragma once
#include <raylib.h>
#include "Types.hpp"

namespace GOL
{
	class Camera
	{
	private:
		Camera2D rcam;
	public:
		void Init(f32 _targetX, f32 _targetY, f32 _zoom);
		void Update();
		void BegingContext();
		void EndContext();
		
		bool CanRender(s32 _x, s32 _y);
	};
}