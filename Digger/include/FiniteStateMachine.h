#pragma once
#include <memory>
#include <vector>
#include "State/MenuState.h"
#include "State/HighScoreMenu.h"
#include "State/MainMenuState.h"
#include "Singleton.h"
#include <stack>

namespace dae
{
	class FiniteStateMachine final : public Singleton<FiniteStateMachine>
	{
	public:
		void Push(MenuState* state);
		void Pop();
		MenuState* GetState();
		std::unique_ptr<HighScoreMenu>highscoreState
		{std::make_unique<HighScoreMenu>()};
		std::unique_ptr<MainMenuState>mainMenuState
		{ std::make_unique<MainMenuState>() };
	private:
		//shout out to slides
		std::stack<MenuState*> m_Stack;
		friend class Singleton<FiniteStateMachine>;
		~FiniteStateMachine();
		FiniteStateMachine() = default;
		std::vector<std::unique_ptr<MenuState>> m_States;
	};
}

