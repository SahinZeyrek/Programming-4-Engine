#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <algorithm>

namespace dae
{
	GameObject::~GameObject()
	{
		for (auto elem : m_pComponents)
		{
			delete elem;
			elem = nullptr;
		}
	};

	void GameObject::RemoveComponent(Component* component)
	{
		m_pMarkedForRemoval.push_back(component);
	}

	void GameObject::SetParent(GameObjectPtr newParent, bool keepWorldPos)
	{
		if (m_Parent == newParent)
		{
			throw ParentException();
		}
		if (newParent == nullptr) { this->SetPosition(m_worldPos.x, m_worldPos.y); }
		else
		{
			if (keepWorldPos)
			{
				this->SetPosition(m_Transform.GetPosition().x - newParent->GetWorldPosition().x,
					m_Transform.GetPosition().y - newParent->GetWorldPosition().y);
			}
		}
		if (m_Parent != nullptr) { m_Parent = nullptr; }
		m_Parent = newParent;

	}

	void GameObject::Update()
	{
		for (size_t i = 0; i < m_pMarkedForRemoval.size(); ++i)
		{
			delete m_pMarkedForRemoval[i];
			m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), m_pMarkedForRemoval[i]));
		}
		if (m_IsActive)
		{
			for (auto comp : m_pComponents)
			{
				comp->Update();
			}
		}
		
	}

	void GameObject::Render() const
	{
		if (m_IsActive)
		{
			for (auto comp : m_pComponents)
			{
				comp->Render();
			}
		}
		
	}



	void GameObject::SetPosition(float x, float y)
	{
		m_Transform.SetPosition(x, y, 0.0f);
		m_isDirty = true;
	}

	void GameObject::SetParentScene(Scene* scene)
	{
		m_ParentScene = scene;
	}

	const glm::vec3& dae::GameObject::GetWorldPosition()
	{
		if (m_isDirty)
		{
			UpdateWorldPos();
		}
		return m_worldPos;
	}

	void GameObject::UpdateWorldPos()
	{
		if (m_isDirty)
		{
			if (m_Parent == nullptr)
			{
				m_worldPos = m_Transform.GetPosition();
			}
			else
			{
				m_worldPos = m_Parent->GetWorldPosition() + m_Transform.GetPosition();
			}
		}
		m_isDirty = false;
	}

	void GameObject::OnEvent(Event event)
	{
		switch (event)
		{
		case Observer::Event::PlayerDied:

			break;
		default:
			break;
		}
	}
}

