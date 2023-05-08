#pragma once
#include "Command.h"
#include "GameObject.h"
#include "SpeedComponent.h"
namespace dae
{
	enum class HeldDirection
	{
		Up, Down, Left, Right
	};
	class MoveCommand final : public Command
	{
	public:
		MoveCommand(GameObject* go, HeldDirection dir)
		{
			m_ObjectPtr = go;
			m_currentDirection = dir;
		}
		virtual void Execute() override;
	private:
		GameObject* m_ObjectPtr{};
		glm::vec3 m_Direction;
		HeldDirection m_currentDirection;
		static bool isMoving;
	};

}


