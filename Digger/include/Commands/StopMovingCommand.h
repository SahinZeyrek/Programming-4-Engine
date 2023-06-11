#pragma once
#include "Command.h"
#include "GameObject.h"
#include "MovementDirectionComponent.h"

namespace dae
{
	class StopMovingCommand final : public Command,public Observer
	{
	public:
		using MoveDir = MovementDirectionComponent::MovementDirection;
		StopMovingCommand(GameObject* target);
		virtual void Execute() override;
		virtual void OnEvent(Event e) override;

		virtual ~StopMovingCommand() override;
		StopMovingCommand(const StopMovingCommand& other) = delete;
		StopMovingCommand(StopMovingCommand&& other) = delete;
		StopMovingCommand& operator=(const StopMovingCommand& other) = delete;
		StopMovingCommand& operator=(StopMovingCommand&& other) = delete;
	private:
		bool m_IsActive{ true };
		GameObject* m_Target{};
		MoveDir m_MovementDirection;
		MoveDir m_LastMoveDir;
	};

}

