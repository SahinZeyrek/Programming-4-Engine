#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject()
{
	for (auto elem : m_pComponents)
	{
		delete elem;
		elem = nullptr;
	}
};

void dae::GameObject::Update()
{
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
}
