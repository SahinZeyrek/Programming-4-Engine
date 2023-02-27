#pragma once
#include <memory>
#include "Common.h"
namespace dae
{
	class GameObject;
	class Component
	{
	public:
		using GameObjectPtr = GameObject*;
		//------------------------------------------------
		// METHODS
		//------------------------------------------------
		virtual void Update() = 0;
		virtual void Render() = 0;
		
		GameObjectPtr GetOwner() const;
		Vector3f GetOwnerPosition() const;

		//------------------------------------------------
		// RULE OF FIVE 
		//------------------------------------------------
		Component(GameObjectPtr owner);
		virtual ~Component() = default;
		Component(const Component&) = delete;
		Component(Component&&) = delete;
		Component& operator=(const Component&) = delete;
		Component& operator=(const Component&&) = delete;
	private:
		GameObjectPtr m_pOwner;
	};
}