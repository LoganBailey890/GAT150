#pragma once
#include"Resource/ResorceSystem.h"
#include "Grapics/Render.h"
#include"Math/Color.h"
#include<SDL_ttf.h>
#include <cassert>
namespace nc 
{
	class Font : public Resource
	{
	public:
		~Font();

		bool Load(const std::string& name, void* data) override;
		SDL_Surface* CreateSurface(const std::string& text, const nc::Color& color);

	private:
		TTF_Font* font{ nullptr };
		Render* render{ nullptr };


	};
}