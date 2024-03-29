#pragma once
#include "Component.h"
#include "GameObject.h"
namespace dae
{
	class ColliderComponent final : public Component
	{

	public:
		struct Rectangle
		{
			float x, y, width, height, right, bottom;
		};

		virtual void Update() override;
		virtual void Render() override;

		bool IsOverlapping();
		void SetTarget(GameObject* target);
		ColliderComponent(GameObject* owner, GameObject* target, const float width, const float height);
		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) = delete;
	private:
		GameObject* m_Target;
		Rectangle m_Rectangle;
		Rectangle m_TargetRectangle;
		float m_Timer;
		const float m_MaxTime;
		bool m_IsActive;
	};
}


