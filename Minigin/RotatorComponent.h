#pragma once
#include "Component.h"
namespace dae
{

	class RotatorComponent final : public Component
	{
	public:
		using GameObjectPtr = GameObject*;
		//------------------------------------------------
		// METHODS
		//------------------------------------------------
		virtual void Update() override;
		virtual void Render() override;
		//------------------------------------------------
		// RULE OF FIVE 
		//------------------------------------------------
		RotatorComponent(GameObjectPtr owner,float radius, float angleSpeed);
		virtual ~RotatorComponent();
		RotatorComponent(const RotatorComponent&) = delete;
		RotatorComponent(RotatorComponent&&) = delete;
		RotatorComponent& operator=(const RotatorComponent&) = delete;
		RotatorComponent& operator=(const RotatorComponent&&) = delete;
	private:
		float m_Radius{};
		float m_AngleSpeed{};
		float m_Angle{};
		glm::vec3 m_Offset{};
		GameObjectPtr m_pOwner{};

	};

}

