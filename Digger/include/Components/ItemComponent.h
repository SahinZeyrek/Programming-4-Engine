#pragma once
#include "Component.h"
#include "ColliderComponent.h"
#include "Observer.h"
#include "Subject.h"
namespace dae
{
	class ItemComponent final : public Component
	{
	public:

		virtual void Update() override;
		virtual void Render() override;
		void AddObserver(Observer* observer);
		ItemComponent(GameObject* owner);
		~ItemComponent();
		ItemComponent(const ItemComponent& other) = delete;
		ItemComponent(ItemComponent&& other) = delete;
		ItemComponent& operator=(const ItemComponent& other) = delete;
		ItemComponent& operator=(ItemComponent&& other) = delete;
	private:
		ColliderComponent* m_ColliderComp;
		Subject m_Subject;
		Observer::Event m_ItemPickUpEvent = Observer::Event::ItemPickedUp;
	};

}

