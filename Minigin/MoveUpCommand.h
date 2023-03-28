#pragma once
#include "Command.h"
#include "GameObject.h"
namespace dae
{
	class MoveUpCommand final: public Command
	{
	public:
		MoveUpCommand(GameObject* go)
		{
			m_ObjectPtr = go;
		}
		virtual void Execute() override;
	private:
		GameObject* m_ObjectPtr{};
	};
}