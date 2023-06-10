#pragma once
#include "Component.h"
#include "GameObject.h"
namespace dae
{
	class ColliderComponent final : public Component
	{

	public:
		virtual void Update() override;
		virtual void Render() override;

		ColliderComponent(GameObject* owner, GameObject* target);
		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) = delete;
	};
}


