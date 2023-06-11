#pragma once
#include "Command.h"
#include "GameObject.h"
namespace dae
{
	class ShootCommand final : public Command
	{
	public:
		virtual void Execute() override;
		ShootCommand(GameObject* target);
		ShootCommand(const ShootCommand& other) = delete;
		ShootCommand(ShootCommand&& other) = delete;
		ShootCommand& operator=(const ShootCommand& other) = delete;
		ShootCommand& operator=(ShootCommand&& other) = delete;
	private:
		GameObject* m_Target;
	};

}

