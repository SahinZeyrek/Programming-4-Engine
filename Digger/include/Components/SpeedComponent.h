#pragma once
#include "Component.h"
namespace dae
{
	class SpeedComponent : public Component
	{
	public:
		float GetSpeed() const { return m_Speed; }
		float SetSpeed(float value) { m_Speed = value; }
		virtual void Update() override;
		virtual void Render() override;
		//------------------------------------------------
		// RULE OF FIVE 
		//------------------------------------------------
		SpeedComponent(GameObjectPtr owner, float speed = 100);
		virtual ~SpeedComponent() = default;
		SpeedComponent(const SpeedComponent&) = delete;
		SpeedComponent(SpeedComponent&&) = delete;
		SpeedComponent& operator=(const SpeedComponent&) = delete;
		SpeedComponent& operator=(const SpeedComponent&&) = delete;
	private:
		float m_Speed{};
	};

}


