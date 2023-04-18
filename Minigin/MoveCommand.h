#pragma once
#include "Command.h"
#include "GameObject.h"
namespace dae
{
	class MoveCommand final : public Command
	{
	public:
		MoveCommand(GameObject* go,glm::vec3 dir)
		{
			m_ObjectPtr = go;
			m_Direction = dir;
		}
		virtual void Execute() override;
	private:
		GameObject* m_ObjectPtr{};
		glm::vec3 m_Direction;
	};

}


