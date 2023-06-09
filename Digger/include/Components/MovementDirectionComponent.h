#pragma once
#include "Component.h"

namespace dae
{

	class MovementDirectionComponent final :public Component
	{
	public:
		enum class MovementDirection
		{
			North, East, South, West, None
		};

		virtual void Update() override {};
		virtual void Render() override{};

		MovementDirection GetMovementDirection() const;
		MovementDirection GetLastMovementDirection() const;
		void SetMovementDirection(MovementDirection movement);
		void SetLastMoveDirection(MovementDirection movement);
		explicit MovementDirectionComponent(GameObjectPtr owner);

		MovementDirectionComponent(const MovementDirectionComponent& other) = delete;
		MovementDirectionComponent(MovementDirectionComponent&& other) = delete;
		MovementDirectionComponent& operator=(const MovementDirectionComponent& other) = delete;
		MovementDirectionComponent& operator=(MovementDirectionComponent&& other) = delete;
	private:
		MovementDirection m_MovDir;
		MovementDirection m_LastMoveDir;
	};
	
}


