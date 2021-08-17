#pragma once

//#include"../Engine/Audio/AudioSystem.h"

//input
#include "Input/InputSystem.h"

//core
#include "Core/FileSystem.h"
#include "Core/Timer.h"
#include "Core/Utilites.h"

//graphics
#include "Grapics/Render.h"
#include "Grapics/Texture.h"
#include "Grapics/Particalsystem.h"
#include "Graphics/Font.h"

//Math
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Random.h"
#include "Math/MathUtilis.h"
#include "Math/Transform.h"
#include "Audio/AudioSystem.h"


#include "Object/Actor.h"
#include "Object/Scene.h"

//framework
#include "FrameWork/EventSystem.h"
#include "Resource/ResorceSystem.h"

#include <vector>
#include <memory>
#include<algorithm>
namespace nc
{
	class Engine
	{
	public:
		void Startup();
		void Shutdown();

		void Update();
		void Draw(Render* render);

		template<typename T>
		T* Get();
	public:
		FrameTimer time;
	private:
		std::vector<std::unique_ptr<System>> systems;
	};
	template<typename T>
	inline T* Engine::Get()
	{
		for (auto& system : systems)
		{
			if (dynamic_cast<T*>(system.get())) return dynamic_cast<T*>(system.get());
		}
		return nullptr;
	}
}