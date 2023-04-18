#include "UIComponent.h"
#include "GameObject.h"
#include <cassert>
namespace dae
{
	void UIComponent::Update()
	{
	}
	void UIComponent::Render()
	{
	}
	void UIComponent::OnEvent(Event e)
	{
		switch (e)
		{
		case dae::Observer::Event::PlayerDied:
			m_HealthComp->ReduceLives();
			m_TextRender->SetText("Lives: " + std::to_string(m_HealthComp->GetLives()));
			break;
		case dae::Observer::Event::ScoreChanged:
			m_TextRender->SetText("Score: " + std::to_string(m_ScoreComp->GetScore()));
			break;
		default:
			break;
		}
	}
	UIComponent::TextCompPtr UIComponent::GetTextureComp() const
	{
		return m_TextRender;
	}
	UIComponent::UIComponent(GameObjectPtr owner, HealtCompPtr targetLives) : Component(owner)
	{
		m_TextRender = owner->GetComponent<RenderTextComponent>();
		m_HealthComp = targetLives;
		assert(m_TextRender != nullptr && "Text render component was nullptr");
		assert(m_HealthComp != nullptr && "Health Component was nullptr");
		m_TextRender->SetText("Lives: " + std::to_string(m_HealthComp->GetLives()));
		m_HealthComp->BindOnHealthChanged(this);
	}
	UIComponent::UIComponent(GameObjectPtr owner, ScoreComponent* targetScore) : Component(owner)
	{
		m_TextRender = owner->GetComponent<RenderTextComponent>();
		m_ScoreComp = targetScore;
		assert(m_TextRender != nullptr && "Text render component was nullptr");
		assert(m_ScoreComp != nullptr && "Score Component was nullptr");
		m_TextRender->SetText("Score: " + std::to_string(m_ScoreComp->GetScore()));
		m_ScoreComp->BindOnScoreChanged(this);
	}

	UIComponent::~UIComponent()
	{
	}

}
