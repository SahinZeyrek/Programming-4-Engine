#include "EnemyMover.h"

#include <random>

#include "SpeedComponent.h"
#include "TimeUtil.h"
namespace dae
{
	EnemyMover::EnemyMover(GameObject* owner, Grid* grid) :Component(owner)
	{
		m_Grid = grid;
		m_Pos = GetOwner()->GetLocalPosition();
	}

	void EnemyMover::Update()
	{
		if ((m_Timer += TimeUtil::deltaTime) > m_MaxTimer)
		{
			int index = m_Grid->GetIndexFromPos(GetOwner()->GetLocalPosition().x, GetOwner()->GetLocalPosition().y);
			if (static_cast<size_t>(index) > m_Grid->GetCells().size())
			{
				return;
			}
			auto cell = m_Grid->GetCellFromIndex(index);
			std::random_device rd;
			std::mt19937 generator(rd());
			std::uniform_int_distribution<int> distribution(0, 3);
			auto pos = m_Grid->GetCellTopLeft(cell->location.x, cell->location.y, MovementDirectionComponent::MovementDirection::None);
			switch (distribution(generator))
			{
			case 0:
				{
					GetOwner()->SetPosition(pos.x + static_cast<float>(m_Grid->GetCellSize()), pos.y);
					break;
				}
				case 1:
				{
					GetOwner()->SetPosition(pos.x - static_cast<float>(m_Grid->GetCellSize()),
						pos.y + static_cast<float>(m_Grid->GetCellSize()));
					break;
				}
				case 2:
				{
					GetOwner()->SetPosition(pos.x + static_cast<float>(m_Grid->GetCellSize()),
						pos.y - static_cast<float>(m_Grid->GetCellSize()));
					break;
				}
				
				case 3:
				{
					GetOwner()->SetPosition(pos.x - static_cast<float>(m_Grid->GetCellSize()),
						pos.y - static_cast<float>(m_Grid->GetCellSize()));
					break;
				}

			}
			m_Timer = 0.f;
		}
		
	}


	void EnemyMover::Render()
	{
	}
}
