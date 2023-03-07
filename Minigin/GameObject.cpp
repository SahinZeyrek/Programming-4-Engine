#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <algorithm>

dae::GameObject::~GameObject()
{
	for (auto elem : m_pComponents)
	{
		delete elem;
		elem = nullptr;
	}
};

void dae::GameObject::RemoveComponent(Component* component)
{
	m_pMarkedForRemoval.push_back(component);
}

void dae::GameObject::SetParent(GameObjectPtr newParent, bool keepWorldPos)
{
	if (m_Parent == newParent) 
	{ throw dae::ParentException(); }
	if (newParent == nullptr) { this->SetPosition(m_worldPos.x,m_worldPos.y); }
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

void dae::GameObject::Update()
{
	for (size_t i = 0; i < m_pMarkedForRemoval.size(); ++i)
	{
		delete m_pMarkedForRemoval[i];
		m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), m_pMarkedForRemoval[i]));
	}
	for (auto comp : m_pComponents)
	{
		comp->Update();
	}
}

void dae::GameObject::Render() const
{
	for (auto comp : m_pComponents)
	{
		comp->Render();
	}
}



void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
	m_isDirty = true;
}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
	if (m_isDirty)
	{
		UpdateWorldPos();
	}
	return m_worldPos;
}

void dae::GameObject::UpdateWorldPos()
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
