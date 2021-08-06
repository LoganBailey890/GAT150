#pragma once
#include "Framework/System.h"
#include <SDL_stdinc.h>
#include<vector>

namespace nc
{
	class InputSystem : public System 
	{
	public:
		enum class eKeyState
		{
			Idle,
			Pressed,
			Held,
			Release
		};

		eKeyState GetKeyState(int id);
		bool IsKeyDown(int id);
		bool IsPreviousKeyDown(int id);

		// Inherited via System
		virtual void Startup() override;
		virtual void Shutdown() override;
		virtual void Update(float dt) override;

	private:
		std::vector<Uint8>keyboardstate;
		std::vector<Uint8>prevKeyboardState;
		int numKeys;


	};
}