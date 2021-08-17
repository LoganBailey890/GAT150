#pragma once
#include "Framework/System.h"
#include "Math/Vector2.h"
#include <SDL.h>
#include<vector>
#include<array>

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

		enum class eMouseButton
		{
			left,
			middle,
			right
		};

		eKeyState GetKeyState(int id);
		bool IsKeyDown(int id);
		bool IsPreviousKeyDown(int id);

		const Vector2 GetMousePosition() const { return mousePosition; }
		bool isButtonDown(int id) { return mouseButtonState[id]; }
		bool IsPrevButtonDown(int id) { return prevmouseButtonState[id]; }
		eKeyState GetButtonState(int id);

		// Inherited via System
		virtual void Startup() override;
		virtual void Shutdown() override;
		virtual void Update(float dt) override;

	private:
		std::vector<Uint8>keyboardstate;
		std::vector<Uint8>prevKeyboardState;
		int numKeys;

		Vector2 mousePosition;
		std::array<Uint8,3> mouseButtonState;
		std::array<Uint8,3> prevmouseButtonState;


	};
}