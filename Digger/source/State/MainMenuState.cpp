#include "State/MainMenuState.h"

namespace dae
{
	void MainMenuState::OnEnter()
	{
		m_Title->SetIsActive(true);
	}
	void MainMenuState::OnExit()
	{
		m_Title->SetIsActive(false);
	}

	void MainMenuState::SetTitle(GameObject* title)
	{
		m_Title = title;
	}
}
