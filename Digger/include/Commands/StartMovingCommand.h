#pragma once
#include "Command.h"
#include "GameObject.h"
#include "Grid.h"
#include <memory>
namespace dae
{
	class StartMovingCommand final : public Command
	{
	public:
		virtual void Execute() override;

		StartMovingCommand(GameObject* target,std::shared_ptr<Grid> grid);
		virtual ~StartMovingCommand() override;
		StartMovingCommand(const StartMovingCommand& other) = delete;
		StartMovingCommand(StartMovingCommand&& other) = delete;
		StartMovingCommand& operator=(const StartMovingCommand& other) = delete;
		StartMovingCommand& operator=(StartMovingCommand&& other) = delete;

	private:
		GameObject* m_Target;
		std::shared_ptr<Grid> m_Grid;
		glm::vec2 m_Offset{};
	};

	
}

