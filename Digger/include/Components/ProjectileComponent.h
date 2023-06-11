#pragma once
#include "Component.h"
#include "Subject.h"
#include "ColliderComponent.h"
#include "MovementDirectionComponent.h"
#include "GridComponent.h"
namespace dae
{
	class ProjectileComponent final : public Component
	{
	public:

		virtual void Update() override;
		virtual void Render() override;
		void Shoot();

		void AddObserver(Observer* observer);
		ProjectileComponent(GameObject* owner, GameObject* bullet,const float m_Cooldown);
		~ProjectileComponent();
		ProjectileComponent(const ProjectileComponent& other) = delete;
		ProjectileComponent(ProjectileComponent&& other) = delete;
		ProjectileComponent& operator=(const ProjectileComponent& other) = delete;
		ProjectileComponent& operator=(ProjectileComponent&& other) = delete;
	private:
		GameObject* m_Bullet;
		Subject m_Subject;
		ColliderComponent* m_ColliderComp;
		GridComponent* m_GridComp;
		MovementDirectionComponent* m_MoveDir;
		const float m_Cooldown;
		float m_Timer;
		glm::vec3 m_Direction;
		bool m_CanFire{ true };
	};
}


