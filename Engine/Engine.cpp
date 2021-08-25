#include "Engine.h"

namespace nc
{
	void Engine::Startup()
	{
		systems.push_back(std::make_unique<EventSystem>());
		systems.push_back(std::make_unique<Render>());
		systems.push_back(std::make_unique<ResourceSystem>());
		systems.push_back(std::make_unique<InputSystem>());
		systems.push_back(std::make_unique<ParticleSystem>());
		systems.push_back(std::make_unique<AudioSystem>());
		//audio system

		for (auto& system : systems)
		{
			system->Startup();
		}
		
		REGISTER_CLASS(Actor)
		REGISTER_CLASS(SpriteComponent)
		REGISTER_CLASS(SpriteAnimationComponent)
		REGISTER_CLASS(PhisicsComponenet)
	}
	void Engine::Shutdown()
	{
		std::for_each(systems.begin(), systems.end(), [](auto& system) { system->Shutdown(); });
	}
	void Engine::Update()
	{
		time.Tick();
		std::for_each(systems.begin(), systems.end(), [this](auto& system) { system->Update(this->time.deltaTime); });
	}
	void Engine::Draw(Render* render)
	{
		std::for_each(systems.begin(), systems.end(), [render](auto& system) { if(dynamic_cast<GraphicsSystem*>(system.get())) dynamic_cast<GraphicsSystem*>(system.get())->Draw(render); });

	}
	
}