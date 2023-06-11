#include "Scene.h"
#include "GameObject.h"
#include <algorithm>
#include "InputManager.h"
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

void Scene::AddCommand(std::unique_ptr<Command> command)
{
	m_Commands.push_back(std::move(command));
}

void Scene::Remove(GameObject* object)
{
	m_pMarkedForRemoval.push_back(object);
}

void Scene::FlushMarked()
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
}

void Scene::RemoveAll()
{
	for (auto elem : m_pObjects)
	{
		m_pMarkedForRemoval.push_back(elem);
	}
	for (auto& elem : m_Commands)
	{
		m_CommandsRemoval.push_back(std::move(elem));
	}
}

void Scene::ForceDestroy()
{
	while (!m_pObjects.empty())
	{
		for (size_t i = 0; i < m_pObjects.size(); ++i)
		{
			delete m_pObjects[i];
			m_pObjects.erase(std::remove(m_pObjects.begin(), m_pObjects.end(), m_pObjects[i]));
		}
		m_pObjects.clear();
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
	while (!m_CommandsRemoval.empty())
	{
		for (size_t i = 0; i<m_CommandsRemoval.size(); ++i)
		{
			m_CommandsRemoval[i].reset();
			m_CommandsRemoval.erase(std::remove(m_Commands.begin(), m_Commands.end(), m_CommandsRemoval[i]));
		}
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

void Scene::BindOnLoad(const std::function<void()>& onLoadFunction)
{
	m_Callback = onLoadFunction;
}

void Scene::Load()
{
	m_Callback();
}

