#pragma once
#include "Command.h"
#include "GameObject.h"
#include "SpeedComponent.h"
#include "MovementDirectionComponent.h"
#include "Grid.h"
namespace dae
{
	enum class HeldDirection
	{
		Up, Down, Left, Right
	};
	class MoveCommand final : public Command,public Observer
	{
	public:
		using MoveDir = MovementDirectionComponent::MovementDirection;
		MoveCommand(GameObject* go, std::shared_ptr<Grid> grid, MoveDir dir)
		{
			m_ObjectPtr = go;
			m_currentDirection = dir;
			m_MoveComp = m_ObjectPtr->GetComponent<MovementDirectionComponent>();
			m_Grid = grid;	
		}

		virtual void OnEvent(Event e) override;
		virtual void Execute() override;
	private:
		 GameObject* m_ObjectPtr;
		 glm::vec3 m_Direction;
		 bool m_IsActive{true};
		MoveDir m_currentDirection;
		MovementDirectionComponent* m_MoveComp;
		std::shared_ptr<Grid> m_Grid;
	};

}


