#include <SDL.h>
#include "Keyboard.h"
#include <iostream>
namespace dae
{
	class Keyboard::kbImpl
	{
		Uint8* previousState{};
		const Uint8* currentState{};

		int index;
	public:
		kbImpl()
		{
			previousState = static_cast<Uint8*>(malloc(SDL_NUM_SCANCODES * sizeof(Uint8)));
			currentState = SDL_GetKeyboardState(nullptr);
		}

		void Update()
		{

			memcpy(previousState, SDL_GetKeyboardState(nullptr), SDL_NUM_SCANCODES);


		}
		~kbImpl()
		{
			free(previousState);
		}
		bool IsDownThisFrame(SDL_Scancode key) const
		{
			return (currentState[key] && !previousState[key]);
		}

		bool IsUpThisFrame(SDL_Scancode key) const
		{
			return (!currentState[key] && previousState[key]);
		}

		bool IsPressed(SDL_Scancode key) const
		{
			return currentState[key];
		}
	    
	};

	void Keyboard::Update()
	{
		pImpl->Update();
	}

	bool Keyboard::IsDown(SDL_Scancode key) const
	{
		return pImpl->IsDownThisFrame(key);
	}

	bool Keyboard::IsUp(SDL_Scancode key) const
	{
		return pImpl->IsUpThisFrame(key);
	}

	bool Keyboard::IsPressed(SDL_Scancode key) const
	{
		return pImpl->IsPressed(key);
	}

	Keyboard::Keyboard()
	{
		pImpl = new kbImpl();
	}

	Keyboard::~Keyboard()
	{
		delete pImpl;
	}
}