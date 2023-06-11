#pragma once
#include "Component.h"
#include "Grid.h"
namespace dae
{
	class GridComponent final : public Component
	{
	public:
		virtual void Update() override;
		virtual void Render() override;
		Grid* GetGrid();
		void SetGrid(Grid* grid);

		GridComponent(GameObject* owner,Grid* grid);
		GridComponent(const GridComponent& other) = delete;
		GridComponent(GridComponent&& other) = delete;
		GridComponent& operator=(const GridComponent& other) = delete;
		GridComponent& operator=(GridComponent&& other) = delete;
	private:
		Grid* m_Grid;
	};
}


