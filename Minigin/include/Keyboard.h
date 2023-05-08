#pragma once
namespace dae
{
	class Keyboard final
	{
	public:
		void Update();
		bool IsDown(SDL_Scancode key) const;
		bool IsUp(SDL_Scancode key)	 const;
		bool IsPressed(SDL_Scancode key) const;

		Keyboard();
		~Keyboard();
		Keyboard(const Keyboard& other) = delete;
		Keyboard(Keyboard&& other) = delete;
		Keyboard& operator=(const Keyboard& other) = delete;
		Keyboard& operator=(Keyboard&& other) = delete;
	private:
		class kbImpl;
		kbImpl* pImpl;
	};
}


