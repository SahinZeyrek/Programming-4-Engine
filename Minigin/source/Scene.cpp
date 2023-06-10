#include "Scene.h"
#include "GameObject.h"
#include <algorithm>
using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() {
	for (size_t i = 0; i < m_pObjects.size(); ++i)
	{
		delete m_pObjects[i];
		m_pObjects[i] = nullptr;
	}
};

void Scene::Add(GameObject* object)
{
	object->SetParentScene(this);
	m_pObjects.push_back(object);
}

void Scene::Remove(GameObject* object)
{
	m_pMarkedForRemoval.push_back(object);
}

void Scene::RemoveAll()
{
	for (auto elem : m_pObjects)
	{
		m_pMarkedForRemoval.push_back(elem);
	}
}

void Scene::Update()
{
	while (!m_pMarkedForRemoval.empty())
	{
		for (size_t i = 0; i < m_pMarkedForRemoval.size(); ++i)
		{
			delete m_pMarkedForRemoval[i];
			m_pObjects.erase(std::remove(m_pObjects.begin(), m_pObjects.end(), m_pMarkedForRemoval[i]));
		}
		m_pMarkedForRemoval.clear();
	}
	for(auto object : m_pObjects)
	{
		object->Update();
	}
}

void Scene::Render() const
{
	for (const auto object : m_pObjects)
	{
		object->Render();
	}
}

