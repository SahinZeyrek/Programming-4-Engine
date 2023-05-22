#include "RotatorComponent.h"
#include <glm/glm.hpp>
#include "TimeUtil.h"
#include "GameObject.h"
#include "RenderTextureComponent.h"
#include "Texture2D.h"
namespace dae
{
	void RotatorComponent::Update()
	{
		m_Angle += (m_AngleSpeed * TimeUtil::deltaTime);
		auto deg = glm::degrees(m_Angle);
		float x = glm::cos(deg) * m_Radius + m_Offset.x/2.f;
		float y = glm::sin(deg) * m_Radius + m_Offset.y/2.f;
		m_pOwner->SetPosition(x, y);
	}

	void RotatorComponent::Render()
	{
	}

	RotatorComponent::RotatorComponent(GameObjectPtr owner,float radius,float angleSpeed) : Component(owner)
	{
		m_Radius = radius;
		m_AngleSpeed = angleSpeed;
		m_pOwner = owner;
		m_Offset = glm::vec3{ owner->GetComponent<RenderTextureComponent>()->GetTexture()->GetSize().x,
							 owner->GetComponent<RenderTextureComponent>()->GetTexture()->GetSize().y ,
							 0};
	}

	RotatorComponent::~RotatorComponent()
	{
	}
}

