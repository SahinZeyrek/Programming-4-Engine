#pragma once
#include "State/MenuState.h"
#include "GameObject.h"
namespace dae
{
	class HighScoreMenu final : public MenuState
	{
	public:
		HighScoreMenu() = default;
		void SetTitle(GameObject* title);
		virtual void OnEnter() override;
		virtual void OnExit() override;
	private:
		GameObject* m_Title;
	};
}


