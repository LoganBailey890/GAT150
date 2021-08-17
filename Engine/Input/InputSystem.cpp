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

	InputSystem::eKeyState nc::InputSystem::GetButtonState(int id)
	{
		eKeyState state = eKeyState::Idle;

		bool keyDown = isButtonDown(id);

		bool prevKeyDown = IsPrevButtonDown(id);


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

		prevmouseButtonState = mouseButtonState;
		int x, y;
		Uint32 buttons = SDL_GetMouseState(&x, &y);
		mousePosition = nc::Vector2{ x,y };
		mouseButtonState[0] = buttons & SDL_BUTTON_LMASK; //buttons[0001] & [0RML]
		mouseButtonState[1] = buttons & SDL_BUTTON_MMASK; //buttons[0010] & [0RML]
		mouseButtonState[2] = buttons & SDL_BUTTON_RMASK; //buttons[0100] & [0RML]


	
	}

}
