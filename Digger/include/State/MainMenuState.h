#pragma once
#include "MenuState.h"
#include "GameObject.h"
namespace dae
{
	class MainMenuState final : public MenuState
	{
	public:
		virtual void OnEnter() override;
		virtual void OnExit() override;
		void SetTitle(GameObject* title);
		MainMenuState() = default;
		MainMenuState(const MainMenuState& other) = delete;
		MainMenuState(MainMenuState&& other) = delete;
		MainMenuState& operator=(const MainMenuState& other) = delete;
		MainMenuState& operator=(MainMenuState&& other) = delete;
	private:
		GameObject* m_Title;
	};
}


