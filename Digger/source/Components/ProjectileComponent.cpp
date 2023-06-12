#include "ProjectileComponent.h"
#include "MovementDirectionComponent.h"
#include "SpeedComponent.h"
#include "ScoreComponent.h"
#include "TimeUtil.h"

namespace dae
{
	ProjectileComponent::ProjectileComponent(GameObject* owner, GameObject* bullet, const float Cooldown) : Component(owner),
		m_Bullet(bullet), m_Cooldown(Cooldown),m_Timer(0.f),m_Direction({0,0,0})
	{
		m_ColliderComp = m_Bullet->GetComponent<ColliderComponent>();
		m_MoveDir = m_Bullet->GetComponent<MovementDirectionComponent>();
		m_GridComp = owner->GetComponent<GridComponent>();
	}

	ProjectileComponent::~ProjectileComponent()
	{
		for (auto el : m_Subject.GetObservers())
		{
			m_Subject.Unbind(el);
		}
	}
	void ProjectileComponent::Update()
	{
		if (m_ColliderComp->IsOverlapping())
		{
			m_Subject.Invoke(Observer::Event::EnemyHit);
			GetOwner()->GetComponent<ScoreComponent>()->AddScore(250);
			m_Bullet->SetPosition(-1000.f, -1000.f);
			m_Direction = { 0,0,0 };
		}
		else
		{
			switch (m_MoveDir->GetMovementDirection())
			{
			case MovementDirectionComponent::MovementDirection::North:
				m_Direction = glm::vec3{ 0,1,0 };
				break;
			case MovementDirectionComponent::MovementDirection::South:
				m_Direction = glm::vec3{ 0,-1,0 };
				break;
			case MovementDirectionComponent::MovementDirection::West:
				m_Direction = glm::vec3{ 1,0,0 };
				break;
			case MovementDirectionComponent::MovementDirection::East:
				m_Direction = glm::vec3{ -1,0,0 };
				break;
			case MovementDirectionComponent::MovementDirection::None:
					m_Direction = glm::vec3{ -1,0,0 };
				break;
			default:
				break;
			}
			auto pos = m_Bullet->GetLocalPosition();
			pos -= m_Bullet->GetComponent<SpeedComponent>()->GetSpeed() * m_Direction * TimeUtil::deltaTime;
			m_Bullet->SetPosition(pos.x, pos.y);
		}
		if ((m_Timer += TimeUtil::deltaTime) >= m_Cooldown)
		{
			m_CanFire = true;
		}
		if (auto grid = m_GridComp->GetGrid())
		{
			const size_t index = grid->GetIndexFromPos(m_Bullet->GetLocalPosition().x, m_Bullet->GetLocalPosition().y);
			if ( index < grid->GetCells().size() - 1)
			{
				auto cell = grid->GetCellFromIndex(index);
				if (cell->isActive && cell)
				{
					m_Bullet->SetPosition(-1000.f, -1000.f);
					m_Direction = { 0,0,0 };
				}
			}
		}
	}

	void ProjectileComponent::Render()
	{

	}

	void ProjectileComponent::Shoot()
	{
		if (m_CanFire)
		{
			m_Bullet->SetPosition(GetOwner()->GetLocalPosition().x, GetOwner()->GetLocalPosition().y);
			m_MoveDir->SetMovementDirection(
			GetOwner()->GetComponent<MovementDirectionComponent>()->GetLastMovementDirection());
			m_CanFire = false;
		}
		
	}

	void ProjectileComponent::AddObserver(Observer* observer)
	{
		m_Subject.Bind(observer);
	}
}
