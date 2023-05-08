#include "SpeedComponent.h"
namespace dae
{
	void dae::SpeedComponent::Update()
	{
	}

	void dae::SpeedComponent::Render()
	{
	}

	dae::SpeedComponent::SpeedComponent(GameObjectPtr owner, float speed) : Component(owner)
	{
		m_Speed = speed;
	}

}

