#pragma once
#include "Command.h"
#include "GameObject.h"
namespace dae
{
	class MoveDownCommand final : public Command
	{
	public:
		MoveDownCommand(GameObject* go)
		{
			m_ObjectPtr = go;
		}
		virtual void Execute() override;
	private:
		GameObject* m_ObjectPtr{};
	};
}