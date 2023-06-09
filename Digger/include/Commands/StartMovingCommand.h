#pragma once
#include "Command.h"
#include "GameObject.h"
#include "Grid.h"
#include "MovementDirectionComponent.h"
#include <memory>
namespace dae
{
	class StartMovingCommand final : public Command
	{
	public:
		using MoveDir = MovementDirectionComponent::MovementDirection;
		virtual void Execute() override;

		StartMovingCommand(GameObject* target,std::shared_ptr<Grid> grid, MoveDir moveDir);
		virtual ~StartMovingCommand() override;
		StartMovingCommand(const StartMovingCommand& other) = delete;
		StartMovingCommand(StartMovingCommand&& other) = delete;
		StartMovingCommand& operator=(const StartMovingCommand& other) = delete;
		StartMovingCommand& operator=(StartMovingCommand&& other) = delete;

	private:
		//void HandleStart(const float xOffset, const float yOffset);
		GameObject* m_Target;
		std::shared_ptr<Grid> m_Grid;
		glm::vec2 m_Offset{};
		MoveDir m_MovementDirection;
		MoveDir m_LastMoveDir;
	};

	
}

