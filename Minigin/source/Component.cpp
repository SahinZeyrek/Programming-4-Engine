#pragma once 
#include "Component.h"
#include "GameObject.h"
#include <cassert>
namespace dae
{
	Component::GameObjectPtr Component::GetOwner() const
	{
		if (m_pOwner)
		{
			return m_pOwner;
		}
		return nullptr;
	}
	void Component::SetOwner(GameObjectPtr pOwner)
	{
		assert(pOwner);
		if (!pOwner) return;
		else
		{
			m_pOwner->RemoveComponent(this);
		}
	}
	Vector3f Component::GetOwnerPosition() const
	{
		return GetOwner()->GetWorldPosition();
	}
	Component::Component(GameObjectPtr owner)
	{
		m_pOwner = owner;
		
	}
}

