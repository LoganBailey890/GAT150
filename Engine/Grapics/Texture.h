#pragma once
#include "Resource/Resource.h"
#include "Math/Vector2.h"
#include<SDL.h>

namespace nc
{
	class Texture : public Resource
	{
	public:
		bool Load(const std::string& name,void* data) override;
		Vector2 Getsize()const;


		friend class Render;

	private:
		SDL_Texture* textur{ nullptr };
		SDL_Renderer* renderer{ nullptr };

	};
}