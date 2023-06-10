#include "ColliderComponent.h"


namespace dae
{
	void ColliderComponent::Update()
	{
		m_Rectangle.x = GetOwner()->GetLocalPosition().x;
		m_Rectangle.y = GetOwner()->GetLocalPosition().y;
		m_TargetRectangle.x = m_Target->GetLocalPosition().x;
		m_TargetRectangle.y = m_Target->GetLocalPosition().y;
	}

	void ColliderComponent::Render()
	{

	}

	bool ColliderComponent::IsOverlapping()
	{
		// NEED TO APPLY OFFSET BECAUSE POS IS TOP LEFT CORNER OF TEXTURE
		const float offset{ 20.f };
		auto targetPos = m_Target->GetLocalPosition();
		if (m_Rectangle.x<= targetPos.x + offset && targetPos.x + offset <= m_Rectangle.x + m_Rectangle.width
			&&
			m_Rectangle.y<= targetPos.y + offset && targetPos.y + offset <= m_Rectangle.y + m_Rectangle.height)
		{

			//GetOwner()->GetParentScene()->Remove(GetOwner());
			return true;
		}
		return false;
	}

	void ColliderComponent::SetTarget(GameObject* target)
	{
		m_Target = target;
	}

	ColliderComponent::ColliderComponent(GameObject* owner, GameObject* target, 
	                                     const float width,const float height) : Component(owner),
	                                                                             m_Target(target)
	{
		m_Rectangle.x = owner->GetLocalPosition().x;
		m_Rectangle.y = owner->GetLocalPosition().y;
		m_Rectangle.width = width;
		m_Rectangle.height = height;
		m_Rectangle.right = m_Rectangle.x + width;
		m_Rectangle.bottom = m_Rectangle.y + height;
		m_TargetRectangle.width = width;
		m_TargetRectangle.height = height;
		m_TargetRectangle.right = m_TargetRectangle.x + width;
		m_TargetRectangle.bottom = m_TargetRectangle.y + height;
	}
}

;