#pragma once
#include "Command.h"
#include "GameObject.h"
namespace dae
{
	class MoveLeftCommand final : public Command
	{
	public:
		MoveLeftCommand(GameObject* go)
		{
			m_ObjectPtr = go;
		}
		virtual void Execute() override;
	private:
		GameObject* m_ObjectPtr{};
	};
}