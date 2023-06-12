#include "ScoreComponent.h"
#include "GameObject.h"
#include "ServiceLocator.h"
#include "SoundComponent.h"
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
		if (m_Score % 20000)
		{
			m_Subject.Invoke(Observer::Event::ExtraLive);
		}
	}

	void ScoreComponent::BindOnScoreChanged(Observer* observer)
	{
		m_Subject.Bind(observer);
	}

	void ScoreComponent::IncrementCounter()
	{
		++m_ItemPickUpCounter;
		if (m_ItemPickUpCounter % m_CounterThreshold == 0)
		{
			auto& sys = ServiceLocator::GetSoundSystem();
			auto id  = sys.AddSound("../Data/Streak.mp3");
			sys.Play(id, 5.f);
			AddScore(250);
		}
	}

	void ScoreComponent::ResetCounter()
	{
		m_ItemPickUpCounter = 0;
	}

	void ScoreComponent::Update()
	{
	}

	void ScoreComponent::Render()
	{
	}

	ScoreComponent::~ScoreComponent()
	{
		for (auto el : m_Subject.GetObservers())
		{
			m_Subject.Unbind(el);
		}
	}
}

