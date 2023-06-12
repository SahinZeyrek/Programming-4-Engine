#pragma once
#include "Component.h"
#include "Grid.h"
namespace dae
{
	class EnemyMover final : public Component
	{
	public:


		virtual void Update() override;
		virtual void Render() override;
		void SetGrid(Grid* grid) { m_Grid = grid; }
		EnemyMover(GameObject* owner,Grid* grid);
		EnemyMover(const EnemyMover& other) = delete;
		EnemyMover(EnemyMover&& other) = delete;
		EnemyMover& operator=(const EnemyMover& other) = delete;
		EnemyMover& operator=(EnemyMover&& other) = delete;
	private:
		Grid* m_Grid;
		glm::vec3 m_Direction{-1,0,0};
		float m_Timer{ 0.f };
		const float m_MaxTimer{ 2.f };
		glm::vec3 m_Pos;
	};
	
}


