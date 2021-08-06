#include "Engine.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

int main(int, char**)
{

	nc::Engine engine;
	engine.Startup();

	engine.Get<nc::Render>()->Create("GAT150", 800, 600);

	nc::Scene scene;
	scene.engine = &engine;

	nc::setFilePath("../Resources");

	std::shared_ptr<nc::Texture> texture = engine.Get<nc::ResourceSystem>()->Get<nc::Texture>("kim.png", engine.Get<nc::Render>());

	for (size_t i = 0; i < 10; i++)
	{
		nc::Transform transform{nc::Vector2{nc::RandomRange(0,800),nc::RandomRange(0,600) }, nc::RandomRange(0,360), 1.0f};
		std::unique_ptr<nc::Actor> actor = std::make_unique<nc::Actor>(transform,texture);

		scene.AddActor(std::move(actor));

	}


	

	bool quite = false;
	SDL_Event event;
	while (!quite)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quite = true;
			break;
		}

		engine.Update(0);
		quite = (engine.Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eKeyState::Pressed);
		scene.Update(0);
		
		engine.Get<nc::Render>()->BeginFrame();

		scene.Draw(engine.Get<nc::Render>());


		engine.Get<nc::Render>()->EndFrame();

		
	}
	
	
	SDL_Quit();

	return 0;
}

