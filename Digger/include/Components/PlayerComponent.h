#pragma once
#include "Component.h"
#include "Observer.h"
namespace dae
{
	class PlayerComponent final : public Component,public Observer
	{
	public:
		virtual void Update() override;
		virtual void Render() override;
		virtual void OnEvent(Event e) override;
		void Respawn(glm::vec2 spawnPoint);

		PlayerComponent(GameObject* owner, glm::vec2 spawnPoint);
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;
	private:
		glm::vec2 m_SpawnPoint;
	};

}

