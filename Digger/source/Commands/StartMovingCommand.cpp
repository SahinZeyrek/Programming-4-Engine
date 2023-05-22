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
		while (true)
		{
			//SDL Coordinate is top left of texture.
			//float fakeX{ pos.x + static_cast<float>(m_Grid->GetCellSize()) / 2.f };
			//float fakeY{ pos.y + static_cast<float>(m_Grid->GetCellSize()) / 2.f };
			const auto cellCenter = m_Grid->GetCellCenter(pos.x, pos.y);
			if (m_Grid->IsNearCellCenter(0.05f, pos.x, pos.y)) // snap to center if near it 
			{
				m_Target->SetPosition(cellCenter.x - static_cast<float>(m_Grid->GetCellSize())/2.f,
									  cellCenter.y - static_cast<float>(m_Grid->GetCellSize())/2.f);
				
				std::cout << "pos is x: " << pos.x << " y: " << pos.y << std::endl;
				break;
			}
			else
			{
				
			}
		}
	}

	StartMovingCommand::StartMovingCommand(GameObject* target, const std::shared_ptr<Grid> grid) : m_Target{ target }, m_Grid{ grid }
	{
		m_Offset = glm::vec2{ target->GetComponent<RenderTextureComponent>()->GetTexture()->GetSize().x,
							 target->GetComponent<RenderTextureComponent>()->GetTexture()->GetSize().y };
	}

	StartMovingCommand::~StartMovingCommand()
	{
	}
}

