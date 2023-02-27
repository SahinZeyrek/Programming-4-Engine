#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() {
	RemoveAll();
};

void Scene::Add(GameObject* object)
{
	m_pObjects.push_back(object);
}

void Scene::Remove([[maybe_unused]]GameObject* object)
{
	delete object;
	m_pObjects.erase(std::remove(m_pObjects.begin(), m_pObjects.end(), object), m_pObjects.end());
	
}

void Scene::RemoveAll()
{
	for (auto elem : m_pObjects)
	{
		delete elem;
	}
	m_pObjects.clear();
}

void Scene::Update()
{
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

