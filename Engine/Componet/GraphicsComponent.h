#pragma once
#include "Component.h"

namespace nc
{
	class Render;
	class GraphicsComponent : public Component
	{
	public:
		virtual void Draw(Render* render) = 0;
	};
}