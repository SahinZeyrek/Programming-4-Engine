#include "State/HighScoreMenu.h"

#include "RenderTextureComponent.h"
namespace dae
{
	void HighScoreMenu::SetTitle(GameObject* title)
	{
		m_Title = title;
	}

	void HighScoreMenu::OnEnter()
	{
		m_Title->SetIsActive(true);
	}

	void HighScoreMenu::OnExit()
	{
		m_Title->SetIsActive(false);
	}

}

