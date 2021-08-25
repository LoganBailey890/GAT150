#pragma once
#include "GraphicsComponent.h"
#include <memory>

namespace nc
{
	class Texture;
	class SpriteComponent :public GraphicsComponent
	{
	public:
		void Update() override;
		void Draw(Render* render) override;
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		std::shared_ptr<Texture> texture;

		// Inherited via GraphicsComponent
	};
}