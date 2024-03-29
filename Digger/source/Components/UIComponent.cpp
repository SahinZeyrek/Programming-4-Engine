#include "UIComponent.h"
#include "GameObject.h"
#include <cassert>
#include <fstream>
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
		case Event::PlayerDamaged:
			m_HealthComp->TakeDamage(5);
			break;
		case Event::PlayerDied:
			m_HealthComp->ReduceLives();
			m_TextRender->SetText("Lives: " + std::to_string(m_HealthComp->GetLives()));
			break;
		case Event::ScoreChanged:
			m_TextRender->SetText("Score: " + std::to_string(m_ScoreComp->GetScore()));
			break;
		case Event::ItemPickedUp:
			m_ScoreComp->AddScore(25);
			m_ScoreComp->IncrementCounter();
			break;
		case Event::AllItemsPickedUp:
			{
				std::ofstream os{ "../Data/HighScores.txt" ,std::ios::app };
				if (os.is_open())
				{
					std::string name = "Cheater";
					os << name << "|" << m_ScoreComp->GetScore() * 5000.f << '\n';

				}
				break;
			}
			
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
		m_HealthComp->AddObserver(this);
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
