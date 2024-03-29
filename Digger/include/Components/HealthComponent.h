#pragma once
#include "Component.h"
#include "Subject.h"
namespace dae
{
	class HealthComponent final : public Component
	{
	public:
		void TakeDamage(int damage);
		void AddObserver(Observer* observer);
		int GetLives() const { return m_Lives; }
		void IncrementLives() { ++m_Lives; }
		void ReduceLives() { --m_Lives; }
		bool GetIsDead()const { return m_IsDead; }
		virtual void Update() override;
		virtual void Render() override;
		//------------------------------------------------
		// RULE OF FIVE 
		//------------------------------------------------
		HealthComponent(GameObjectPtr owner, int health,int lives);
		virtual ~HealthComponent();
		HealthComponent(const HealthComponent&) = delete;
		HealthComponent(HealthComponent&&) = delete;
		HealthComponent& operator=(const HealthComponent&) = delete;
		HealthComponent& operator=(const HealthComponent&&) = delete;
	private:
		GameObjectPtr m_pOwner{};
		int m_Health{};
		const int m_MaxHealth{};
		int m_Lives{};
		Subject m_Subject{};
		bool m_IsDead{};
	};
}


