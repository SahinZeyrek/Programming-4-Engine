#pragma once 
#include "Component.h"
#include "GameObject.h"
namespace dae
{
	Component::GameObjectPtr Component::GetOwner() const
	{
		return m_pOwner;
	}
	Vector3f Component::GetOwnerPosition() const
	{
		return GetOwner()->GetTransform().GetPosition();
	}
	Component::Component(GameObjectPtr owner)
	{
		m_pOwner = owner;
		
	}
}

