#include "MoveCommand.h"
#include "TimeUtil.h"
void dae::MoveCommand::Execute()
{
	auto pos = m_ObjectPtr->GetLocalPosition();
	if (m_MoveComp->GetMovementDirection() != m_currentDirection)
	{
		return;
	}
	switch (m_MoveComp->GetMovementDirection())
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
	default:
		break;
	}

	const int index = m_Grid->GetIndexFromPos(pos.x, pos.y);
	auto cell = m_Grid->GetCellFromIndex(index);
	if (cell != nullptr)
	{
		cell->isActive = false;
	}
	pos -= m_ObjectPtr->GetComponent<SpeedComponent>()->GetSpeed() * m_Direction * TimeUtil::deltaTime;
	m_ObjectPtr->SetPosition(pos.x, pos.y);
	
	/*if (!m_IsMoving)
	{
		auto pos = m_ObjectPtr->GetLocalPosition();
		m_IsMoving = true;
		while (m_IsMoving)
		{
			switch (m_currentDirection)
			{
			case dae::HeldDirection::Up:
				m_Direction = glm::vec3{ 0,1,0 };

				break;
			case dae::HeldDirection::Down:
				m_Direction = glm::vec3{ 0,-1,0 };

				break;
			case dae::HeldDirection::Left:
				m_Direction = glm::vec3{ 1,0,0 };

				break;
			case dae::HeldDirection::Right:
				m_Direction = glm::vec3{ -1,0,0 };

				break;
			default:
				break;

			}
			pos -= m_ObjectPtr->GetComponent<SpeedComponent>()->GetSpeed() * m_Direction * TimeUtil::deltaTime;
			m_ObjectPtr->SetPosition(pos.x, pos.y);
			m_IsMoving = false;
		}
	}*/
	

	

	

}
