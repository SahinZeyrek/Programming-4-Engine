#pragma once
#include "Command.h"
#include "GameObject.h"
namespace dae
{
	class KillCommand final : public Command
	{
	public:
		KillCommand(GameObject* target)
		{
			m_Target = target;
		};
		virtual void Execute() override;
	private:
		GameObject* m_Target{};
	};

}


