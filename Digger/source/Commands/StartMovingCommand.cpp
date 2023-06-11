#include "StartMovingCommand.h"
#include "SpeedComponent.h"
#include "TimeUtil.h"
#include <iostream>

#include "RenderTextureComponent.h"

namespace dae
{
	void StartMovingCommand::Execute()
	{
		if (m_Target != nullptr && m_IsActive)
		{
			glm::vec2 pos{ m_Target->GetLocalPosition().x,
							 m_Target->GetLocalPosition().y };
			std::cout << "Local X is " << pos.x << '\n';
			std::cout << "Local Y is " << pos.y << '\n';
			//const int cellSize = m_Grid->GetCellSize();
			if (m_Target->GetComponent<MovementDirectionComponent>()->GetOwner() == nullptr)
			{
				m_IsActive = false;
			}
			else
			{
				if (m_Target->GetComponent<MovementDirectionComponent>()->GetMovementDirection()
					== MovementDirectionComponent::MovementDirection::None)
				{
					if (m_Grid->IsNearCellTopLeft(40.f, pos.x, pos.y))
					{
						int index = m_Grid->GetIndexFromPos(pos.x, pos.y);
						auto cell = m_Grid->GetCellFromIndex(index);
						if (cell)
						{
							cell->isActive = false;
						}
						m_Target->SetPosition(m_Grid->GetCellTopLeft(pos.x, pos.y, m_Target->GetComponent<MovementDirectionComponent>()->GetMovementDirection()).x,
							m_Grid->GetCellTopLeft(pos.x, pos.y, m_Target->GetComponent<MovementDirectionComponent>()->GetMovementDirection()).y);
						m_Target->GetComponent<MovementDirectionComponent>()->SetMovementDirection(m_MovementDirection);
					}
					else
					{
						m_Target->GetComponent<MovementDirectionComponent>()->SetMovementDirection(
							m_Target->GetComponent<MovementDirectionComponent>()->GetLastMovementDirection());
						m_Target->SetPosition(m_Grid->GetCellTopLeft(pos.x, pos.y, m_Target->GetComponent<MovementDirectionComponent>()->GetMovementDirection()).x
							, m_Grid->GetCellTopLeft(pos.x, pos.y, m_Target->GetComponent<MovementDirectionComponent>()->GetMovementDirection()).y);
					}
					//m_Target->GetComponent<MovementDirectionComponent>()->SetMovementDirection(m_Target->GetComponent<MovementDirectionComponent>()->GetLastMovementDirection());
					std::cout << "test\n";
				}
			}
			
		}

		
	}

	void StartMovingCommand::OnEvent(Event e)
	{
		switch (e)
		{
		case Event::PlayerDied:
			m_IsActive = false;
			break;
		}
	}

	StartMovingCommand::StartMovingCommand(GameObject* target, const std::shared_ptr<Grid> grid,MoveDir moveDir) :
										   m_Target{ target }, m_Grid{ grid }, m_MovementDirection{moveDir},
										   m_LastMoveDir{MovementDirectionComponent::MovementDirection::None}
	{
		m_Offset = glm::vec2{ target->GetComponent<RenderTextureComponent>()->GetTexture()->GetSize().x,
							 target->GetComponent<RenderTextureComponent>()->GetTexture()->GetSize().y };
	}

	StartMovingCommand::~StartMovingCommand()
	{
	}

}

