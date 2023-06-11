#include "MoveCommand.h"
#include "TimeUtil.h"

void dae::MoveCommand::OnEvent(Event e)
{
	switch (e)
	{
	case Event::PlayerDied:
		m_IsActive = false;
		break;
	}
}

void dae::MoveCommand::Execute()
{
	if (m_ObjectPtr != nullptr && m_IsActive)
	{
		auto pos = m_ObjectPtr->GetLocalPosition();
		if (m_MoveComp->GetMovementDirection() != m_currentDirection)
		{
			return;
		}
		if (m_MoveComp->GetOwner() == nullptr)
		{
			m_IsActive = false;
		}
		else
		{
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

		}
		}
		
	else
	{
		m_IsActive = false;
	}
	

}
