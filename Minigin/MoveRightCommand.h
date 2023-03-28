#pragma once
#include "Command.h"
#include "GameObject.h"
namespace dae
{
	class MoveRightCommand final : public Command
	{
	public:
		MoveRightCommand(GameObject* go)
		{
			m_ObjectPtr = go;
		}
		virtual void Execute() override;
	private:
		GameObject* m_ObjectPtr{};
	};
}