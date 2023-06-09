#include "StopMovingCommand.h"

namespace dae
{
	StopMovingCommand::StopMovingCommand(GameObject* target) : m_Target(target)
	{
		m_Target = target;
	}

	void StopMovingCommand::Execute()
	{
		m_LastMoveDir = m_Target->GetComponent<MovementDirectionComponent>()->GetMovementDirection();
		m_Target->GetComponent<MovementDirectionComponent>()->SetLastMoveDirection(m_LastMoveDir);
		m_Target->GetComponent<MovementDirectionComponent>()->SetMovementDirection(MovementDirectionComponent::MovementDirection::None);
	}

	StopMovingCommand::~StopMovingCommand()
	{

	}

	
}
