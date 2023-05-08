#include "MoveCommand.h"
#include "TimeUtil.h"
bool dae::MoveCommand::isMoving = false;
void dae::MoveCommand::Execute()
{
	auto pos = m_ObjectPtr->GetLocalPosition();

	switch (m_currentDirection)
	{
	case dae::HeldDirection::Up:
		m_Direction = glm::vec3{ 0,1,0 };
		isMoving = true;
		break;
	case dae::HeldDirection::Down:
		m_Direction = glm::vec3{ 0,-1,0 };
		isMoving = true;

		break;
	case dae::HeldDirection::Left:
		m_Direction = glm::vec3{ 1,0,0 };
		isMoving = true;
		break;
	case dae::HeldDirection::Right:
		m_Direction = glm::vec3{ -1,0,0 };
		isMoving = true;
		break;
	default:
		break;

	}

	pos -= m_ObjectPtr->GetComponent<SpeedComponent>()->GetSpeed() * m_Direction * TimeUtil::deltaTime;
	m_ObjectPtr->SetPosition(pos.x, pos.y);

}
