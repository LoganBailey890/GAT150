#pragma once
#include "GraphicsComponent.h"
#include <memory>

namespace nc
{
	class Texture;
	class SpriteComonent :public GraphicsComponent
	{
	public:
		void Update() override;
		void Draw(Render* render) override;

	public:
		std::shared_ptr<Texture> textue;
	};
}