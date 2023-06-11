#include "GridComponent.h"
namespace dae
{
	GridComponent::GridComponent(GameObject* owner,Grid* grid) : Component(owner),m_Grid(grid)
	{
	}

	void GridComponent::Update()
	{
	}

	void GridComponent::Render()
	{
	}

	Grid* GridComponent::GetGrid()
	{
		return m_Grid;
	}

	void GridComponent::SetGrid(Grid* grid)
	{
		m_Grid = grid;
	}
}

