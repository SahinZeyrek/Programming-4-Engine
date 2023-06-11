#include "StopMovingCommand.h"

namespace dae
{
	StopMovingCommand::StopMovingCommand(GameObject* target) : m_Target(target)
	{
		m_Target = target;
	}

	void StopMovingCommand::Execute()
	{
		if (m_Target!= nullptr && m_IsActive)
		{
			if (m_Target->GetComponent<MovementDirectionComponent>()->GetOwner() == nullptr)
			{
				m_IsActive = false;
			}
			else
			{
				m_LastMoveDir = m_Target->GetComponent<MovementDirectionComponent>()->GetMovementDirection();
				m_Target->GetComponent<MovementDirectionComponent>()->SetLastMoveDirection(m_LastMoveDir);
				m_Target->GetComponent<MovementDirectionComponent>()->SetMovementDirection(MovementDirectionComponent::MovementDirection::None);
			}
			
		}
		else
		{
			m_IsActive = false;
		}
		
	}

	void StopMovingCommand::OnEvent(Event e)
	{
		switch (e) { case Event::PlayerDied: m_IsActive = false; }
	}

	StopMovingCommand::~StopMovingCommand()
	{

	}

	
}
