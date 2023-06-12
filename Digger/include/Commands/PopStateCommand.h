#pragma once
#include "State/MenuState.h"
#include "Command.h"

namespace dae
{
	class PopStateCommand final : public Command
	{
	public:
		virtual void Execute() override;
		PopStateCommand() = default;
		PopStateCommand(const PopStateCommand& other) = delete;
		PopStateCommand(PopStateCommand&& other) = delete;
		PopStateCommand& operator=(const PopStateCommand& other) = delete;
		PopStateCommand& operator=(PopStateCommand&& other) = delete;
	private:

	};
}

