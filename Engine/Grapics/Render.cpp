#include"Render.h"
#include"Math/MathUtilis.h"
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>


namespace nc
{
	void nc::Render::Startup()
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			std::cout << "SDL_inti Error." << SDL_GetError << std::endl;
		}
		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
		TTF_Init();
	}

	void nc::Render::Shutdown()
	{
		IMG_Quit();
		TTF_Quit();
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}

	void nc::Render::Update(float dt)
	{
		
	}

	void nc::Render::Create(const std::string& name, int with, int height)
	{
		window = SDL_CreateWindow(name.c_str(), 100, 100, with, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (window == nullptr)
		{
			std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl; 
			SDL_Quit();
		}

		 renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	}

	void nc::Render::BeginFrame()
	{
		SDL_RenderClear(renderer);
	}

	void nc::Render::EndFrame()
	{
		SDL_RenderPresent(renderer);
	}

	void Render::Draw(std::shared_ptr<nc::Texture> texture, const Vector2& position,float angle,const Vector2& scale)
	{
		Vector2 size = texture->Getsize();
		size = size * scale;
		Vector2 newPosition = position - (size * 0.5f);

		SDL_Rect dest;
		dest.x = static_cast<int>(newPosition.x);
		dest.y = static_cast<int>(newPosition.y);
		dest.w = static_cast<int>(size.x);
		dest.h = static_cast<int>(size.y);

		SDL_RenderCopyEx(renderer, texture->textur, nullptr,&dest,nc::RadToDeg(angle),nullptr,SDL_FLIP_NONE);
	}

	void Render::Draw(std::shared_ptr<nc::Texture> texture, const Transform& transform)
	{
		Vector2 size = texture->Getsize();
		size = size * transform.scale;

		Vector2 newPosition = transform.position - (size * 0.5f);

		SDL_Rect dest;
		dest.x = static_cast<int>(newPosition.x);
		dest.y = static_cast<int>(newPosition.y);
		dest.w = static_cast<int>(size.x);
		dest.h = static_cast<int>(size.y);

		SDL_RenderCopyEx(renderer, texture->textur, nullptr, &dest, nc::RadToDeg(transform.rotation), nullptr, SDL_FLIP_NONE);
	}

}
