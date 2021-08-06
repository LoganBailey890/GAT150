#include"InputSystem.h"
#include "SDL_keyboard.h"
#include <algorithm>
#include <vector>

namespace nc
{

	InputSystem::eKeyState nc::InputSystem::GetKeyState(int id)
	{
		eKeyState state = eKeyState::Idle;

		bool keyDown = IsKeyDown(id);

		bool prevKeyDown = IsPreviousKeyDown(id);


		if (keyDown)
		{
			state = (prevKeyDown) ? eKeyState::Held : eKeyState::Pressed;
		}
		else
		{
			state = (prevKeyDown) ? eKeyState::Release : eKeyState::Idle;
		}

		return state;
	}

	bool nc::InputSystem::IsKeyDown(int id)
	{
		return keyboardstate[id];
	}

	bool nc::InputSystem::IsPreviousKeyDown(int id)
	{
		return prevKeyboardState[id];
	}

	void nc::InputSystem::Startup()
	{
		const Uint8* keyboardStateSDL = SDL_GetKeyboardState(&numKeys);
		keyboardstate.resize(numKeys);
		std::copy(keyboardStateSDL, keyboardStateSDL + numKeys, keyboardstate.begin());
		prevKeyboardState = keyboardstate;
	}

	void nc::InputSystem::Shutdown()
	{
	}

	void nc::InputSystem::Update(float dt)
	{
		prevKeyboardState = keyboardstate;
		const Uint8* keyboardStateSDL = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardStateSDL, keyboardStateSDL + numKeys, keyboardstate.begin());

	
	}

}
