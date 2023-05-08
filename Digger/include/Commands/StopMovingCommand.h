#pragma once
#include "Command.h"
#include "GameObject.h"
namespace dae
{
	class StopMovingCommand : public Command
	{
	public:
		StopMovingCommand(GameObject* target)
		{
			m_Target = target;
		};
		virtual void Execute() override;
	private:
		GameObject* m_Target{};
	};

}

