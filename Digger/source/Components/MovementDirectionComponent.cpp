#include "MovementDirectionComponent.h"

namespace dae
{
	MovementDirectionComponent::MovementDirectionComponent(GameObjectPtr owner) : Component(owner),
															m_MovDir(MovementDirection::None),
														    m_LastMoveDir(MovementDirection::None)
	{

	}

	MovementDirectionComponent::MovementDirection MovementDirectionComponent::GetMovementDirection() const
	{
		if (GetOwner() != nullptr)
		{
			return m_MovDir;
		}
		return MovementDirection::None;
	}

	MovementDirectionComponent::MovementDirection MovementDirectionComponent::GetLastMovementDirection() const
	{
		return m_LastMoveDir;
	}

	void MovementDirectionComponent::SetMovementDirection(MovementDirection movement)
	{
		m_MovDir = movement;
	}

	void MovementDirectionComponent::SetLastMoveDirection(MovementDirection movement)
	{
		m_LastMoveDir = movement;
	}
}

