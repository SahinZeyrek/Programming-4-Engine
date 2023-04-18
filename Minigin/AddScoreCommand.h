#pragma once
#include "Command.h"
#include "GameObject.h"
namespace dae
{
	class AddScoreCommand : public Command
	{
	public:
		AddScoreCommand(GameObject* target)
		{
			m_Target = target;
		};
		virtual void Execute() override;
	private:
		GameObject* m_Target;
	};
}