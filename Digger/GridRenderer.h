#pragma once
#include "Grid.h"
#include "Component.h"
#include "GameObject.h"
#include <memory>
namespace dae
{
	class GridRenderer final : public Component
	{
	public:
		GridRenderer(GameObject* pOwner,std::shared_ptr<Grid> grid) : Component(pOwner)
		{
			m_Grid = grid;
		}
		;
		//------------------------------------------------
		// METHODS
		//------------------------------------------------
		virtual void Update() override;
		virtual void Render() override;
		//------------------------------------------------
		// RULE OF FIVE 
		//------------------------------------------------
		virtual ~GridRenderer() = default;
		GridRenderer(const GridRenderer&) = delete;
		GridRenderer(GridRenderer&&) = delete;
		GridRenderer& operator=(const GridRenderer&) = delete;
		GridRenderer& operator=(const GridRenderer&&) = delete;
	private:
		std::shared_ptr<Grid> m_Grid;
	};

}


