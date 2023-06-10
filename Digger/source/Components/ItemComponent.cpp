#include "ItemComponent.h"
#include "SoundComponent.h"
namespace dae
{

	void ItemComponent::Update()
	{
		if (m_ColliderComp->IsOverlapping() && m_ColliderComp)
		{
			m_Subject.Invoke(m_ItemPickUpEvent);
			if (auto comp =GetOwner()->GetComponent<SoundComponent>())
			{
				comp->PlaySound();
			}
			GetOwner()->GetParentScene()->Remove(GetOwner());
		}
	}

	void ItemComponent::Render()
	{
	}

	void ItemComponent::AddObserver(Observer* observer)
	{
		m_Subject.Bind(observer);
	}

	ItemComponent::ItemComponent(GameObject* owner) : Component(owner)
	{
		m_ColliderComp = owner->GetComponent<ColliderComponent>();
	}
}

