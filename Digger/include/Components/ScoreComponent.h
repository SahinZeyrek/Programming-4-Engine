#pragma once
#include "Component.h"
#include "Subject.h"
namespace dae
{
	class ScoreComponent : public Component
	{
	public:
		ScoreComponent(GameObject* owner,int startScore = 0);
		void AddScore(int amount);
		int GetScore() const { return m_Score; }
		void BindOnScoreChanged(Observer* observer);
		void IncrementCounter();
		void ResetCounter();
		virtual void Update() override;
		virtual void Render() override;
		//------------------------------------------------
		// RULE OF FIVE 
		//------------------------------------------------
		virtual ~ScoreComponent();
		ScoreComponent(const ScoreComponent&) = delete;
		ScoreComponent(ScoreComponent&&) = delete;
		ScoreComponent& operator=(const ScoreComponent&) = delete;
		ScoreComponent& operator=(const ScoreComponent&&) = delete;
	private:
		size_t m_ItemPickUpCounter{};
		const size_t m_CounterThreshold{8};
		int m_Score{};
		Subject m_Subject{};
	};


}

