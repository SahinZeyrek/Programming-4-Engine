#include "EnemyComponent.h"

#include <iostream>

namespace dae
{
	EnemyComponent::EnemyComponent(GameObject* owner) : Component(owner),
		m_ColliderComponent(nullptr)
	{
		m_ColliderComponent = GetOwner()->GetComponent<ColliderComponent>();
	}

	EnemyComponent::~EnemyComponent()
	{
		for (auto el : m_Subject.GetObservers())
		{
			m_Subject.Unbind(el);
		}
	}

	void EnemyComponent::Update()
	{
		if (m_ColliderComponent && m_ColliderComponent->IsOverlapping())
		{
			m_Subject.Invoke(Observer::Event::PlayerDamaged);
		}
	}

	void EnemyComponent::Render()
	{

	}

	void EnemyComponent::OnEvent(Event e)
	{
		switch (e)
		{
		case Event::EnemyHit:
			GetOwner()->SetPosition(-100.f, -100.f);
			// TO DO: disable ai mover;
			break;

		}
	}

	void EnemyComponent::AddObserver(Observer* observer)
	{
		m_Subject.Bind(observer);
	}

	
}
