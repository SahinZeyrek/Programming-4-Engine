#pragma once
#include "HealthComponent.h"
namespace dae
{
	void HealthComponent::TakeDamage(int damage)
	{
		m_Health -= damage;
		if (m_Health <= 0)
		{
			--m_Lives;
			if (m_Lives < 0)
			{
				m_IsDead = true;
			}
			else
			{
				m_Health = m_MaxHealth;
			}

			m_Subject.Invoke(Observer::Event::PlayerDied);
		}
	}
	void HealthComponent::BindOnHealthChanged(Observer* observer)
	{
		m_Subject.Bind(observer);
	}

	void HealthComponent::Update()
	{
	}

	void HealthComponent::Render()
	{
	}

	HealthComponent::HealthComponent(GameObjectPtr owner, int lives, int health) : Component(owner),
		m_MaxHealth{ health }
	{
		m_pOwner = owner;
		m_Lives = lives;
		m_Health = health;
	}

}

