#pragma once
#include "Component.h"
#include "ColliderComponent.h"
#include "Subject.h"
namespace dae
{
	class EnemyComponent final : public Component,public Observer
	{
	public:
		virtual void Update() override;
		virtual void Render() override;
		virtual void OnEvent(Event e) override;

		void AddObserver(Observer* observer);

		EnemyComponent(GameObject* owner);
		~EnemyComponent();
;		EnemyComponent(const EnemyComponent& other) = delete;
		EnemyComponent(EnemyComponent&& other) = delete;
		EnemyComponent& operator=(const EnemyComponent& other) = delete;
		EnemyComponent& operator=(EnemyComponent&& other) = delete;
	private:
		Subject m_Subject;
		ColliderComponent* m_ColliderComponent;
	};
	
}


