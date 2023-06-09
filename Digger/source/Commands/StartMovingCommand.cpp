#include "StartMovingCommand.h"
#include "SpeedComponent.h"
#include "TimeUtil.h"
#include <iostream>

#include "RenderTextureComponent.h"

namespace dae
{
	void StartMovingCommand::Execute()
	{
		glm::vec2 pos{   m_Target->GetLocalPosition().x,
						 m_Target->GetLocalPosition().y };
		std::cout << "Local X is " << pos.x << '\n';
		std::cout << "Local Y is " << pos.y << '\n';
		//const int cellSize = m_Grid->GetCellSize();
		if (m_Target->GetComponent<MovementDirectionComponent>()->GetMovementDirection()
			== MovementDirectionComponent::MovementDirection::None)
		{
			//switch (m_Target->GetComponent<MovementDirectionComponent>()->GetMovementDirection())
			//{
			//case MovementDirectionComponent::MovementDirection::East:
			//	{
			//	if (m_Grid->IsNearCellTopLeft(40.f, pos.x + cellSize, pos.y))
			//	{
			//		m_Target->SetPosition(m_Grid->GetCellTopLeft(pos.x, pos.y).x, m_Grid->GetCellTopLeft(pos.x, pos.y).y);
			//		m_Target->GetComponent<MovementDirectionComponent>()->SetMovementDirection(m_MovementDirection);
			//	}
			//	else
			//	{
			//		m_Target->GetComponent<MovementDirectionComponent>()->SetMovementDirection(
			//			m_Target->GetComponent<MovementDirectionComponent>()->GetLastMovementDirection());
			//		m_Target->SetPosition(m_Grid->GetCellTopLeft(pos.x, pos.y).x, m_Grid->GetCellTopLeft(pos.x, pos.y).y);
			//	}
			//	}
			//case MovementDirectionComponent::MovementDirection::West:
			//	{
			//	if (m_Grid->IsNearCellTopLeft(40.f, pos.x, pos.y))
			//	{
			//		m_Target->SetPosition(m_Grid->GetCellTopLeft(pos.x, pos.y).x, m_Grid->GetCellTopLeft(pos.x, pos.y).y);
			//		m_Target->GetComponent<MovementDirectionComponent>()->SetMovementDirection(m_MovementDirection);
			//	}
			//	else
			//	{
			//		m_Target->GetComponent<MovementDirectionComponent>()->SetMovementDirection(
			//			m_Target->GetComponent<MovementDirectionComponent>()->GetLastMovementDirection());
			//		m_Target->SetPosition(m_Grid->GetCellTopLeft(pos.x, pos.y).x, m_Grid->GetCellTopLeft(pos.x, pos.y).y);
			//	}
			//	}
			//}
			if (m_Grid->IsNearCellTopLeft(40.f,pos.x,pos.y))
			{
				m_Target->SetPosition(m_Grid->GetCellTopLeft(pos.x, pos.y).x, m_Grid->GetCellTopLeft(pos.x, pos.y).y);
				m_Target->GetComponent<MovementDirectionComponent>()->SetMovementDirection(m_MovementDirection);
			}
			else
			{
				m_Target->GetComponent<MovementDirectionComponent>()->SetMovementDirection(
				m_Target->GetComponent<MovementDirectionComponent>()->GetLastMovementDirection());
				m_Target->SetPosition(m_Grid->GetCellTopLeft(pos.x, pos.y).x, m_Grid->GetCellTopLeft(pos.x, pos.y).y);
			}

			//m_Target->GetComponent<MovementDirectionComponent>()->SetMovementDirection(m_MovementDirection);
			std::cout << "test\n";
		}

		//glm::vec2 pos{   m_Target->GetLocalPosition().x,
		//				 m_Target->GetLocalPosition().y };
		//while (true)
		//{
		//	//SDL Coordinate is top left of texture.
		//	//float fakeX{ pos.x + static_cast<float>(m_Grid->GetCellSize()) / 2.f };
		//	//float fakeY{ pos.y + static_cast<float>(m_Grid->GetCellSize()) / 2.f };
		//	const auto cellCenter = m_Grid->GetCellTopLeft(pos.x, pos.y);
		//	if (m_Grid->IsNearCellTopLeft(0.05f, pos.x, pos.y)) // snap to center if near it 
		//	{
		//		m_Target->SetPosition(cellCenter.x - static_cast<float>(m_Grid->GetCellSize())/2.f,
		//							  cellCenter.y - static_cast<float>(m_Grid->GetCellSize())/2.f);
		//		
		//		std::cout << "pos is x: " << pos.x << " y: " << pos.y << std::endl;
		//		break;
		//	}
		//	else
		//	{
		//		
		//	}
		//}
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

