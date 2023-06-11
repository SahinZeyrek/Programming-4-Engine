#include "PlayerComponent.h"
#include "HealthComponent.h"
#include "GameObject.h"
#include "ScoreComponent.h"

namespace dae
{
	PlayerComponent::PlayerComponent(GameObject* owner, glm::vec2 spawn) : Component(owner),m_SpawnPoint(spawn)
	{

	}

	void PlayerComponent::Update()
	{

	}

	void PlayerComponent::Render()
	{

	}

	void PlayerComponent::OnEvent(Event e)
	{
		switch (e)
		{
		case Observer::Event::PlayerDied:
			if (auto scoreComp = GetOwner()->GetComponent<ScoreComponent>())
			{
				scoreComp->ResetCounter();
			}
			
			if (GetOwner()->GetComponent<HealthComponent>()->GetIsDead())
			{
				GetOwner()->SetPosition(-500, -500);
			}
			else
			{
				Respawn(m_SpawnPoint);
			}
		}
	}

	void PlayerComponent::Respawn(glm::vec2 spawnPoint)
	{
		GetOwner()->SetPosition(spawnPoint.x, spawnPoint.y);
	}
}
