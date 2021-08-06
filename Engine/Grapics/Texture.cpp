#include "Texture.h"
#include "Render.h"
#include "Math/Vector2.h"
#include <SDL_image.h>
#include <iostream>

namespace nc 
{

	bool nc::Texture::Load(const std::string& name,void* data)
	{

		renderer = static_cast<Render*>(data)->renderer;
		// load surface
		SDL_Surface* surface = IMG_Load(name.c_str());
		if (surface == nullptr)
		{
			std::cout << "IMG_Load Error: " << SDL_GetError() << std::endl;
			return false;
		}
		// create texture
		textur = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		if (textur == nullptr)
		{
			std::cout << "SDL_CreateTextrureFormSurface Error: " << SDL_GetError() << std::endl;
			return false;
		}

		return false;
	}


	Vector2 Texture::Getsize() const
	{
		SDL_Point point;
		SDL_QueryTexture(textur, nullptr, nullptr, &point.x, &point.y);

		return Vector2{point.x, point.y};
	}

}
