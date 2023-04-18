#include "ScoreComponent.h"
#include "GameObject.h"
namespace dae
{
	ScoreComponent::ScoreComponent(GameObject* owner,int startScore) : Component(owner)
	{
		m_Score = startScore;
	}

	void ScoreComponent::AddScore(int amount)
	{
		m_Score += amount;
		m_Subject.Invoke(Observer::Event::ScoreChanged);
		if (m_Score >= 500)
		{
			m_Subject.Invoke(Observer::Event::ScoreGoalReached);
		}
	}

	void ScoreComponent::BindOnScoreChanged(Observer* observer)
	{
		m_Subject.Bind(observer);
	}

	void ScoreComponent::Update()
	{
	}

	void ScoreComponent::Render()
	{
	}

}

