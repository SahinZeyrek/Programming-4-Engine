#include "SceneManager.h"
#include "Scene.h"
#include <cassert>
#include "InputManager.h"

void dae::SceneManager::Update()
{
	m_CurrentScene->Update();
	for (auto scene : m_scenes)
	{
		scene->FlushMarked();
	}
}

void dae::SceneManager::Render()
{
	m_CurrentScene->Render();
}

dae::SceneManager::~SceneManager()
{

}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}

void dae::SceneManager::SetCurrentScene(Scene* scene)
{
	m_CurrentScene = scene;
}

void dae::SceneManager::LoadScene(const std::string& name)
{
	auto it = std::find_if(m_scenes.begin(),m_scenes.end(), [name](const std::shared_ptr<Scene>& scene)
		{
			return (scene->GetName() == name);
		});
	assert(it != m_scenes.end() && "Scene doesn't exist");
	if (m_CurrentScene)
	{
		m_CurrentScene->RemoveAll();
	}
	(*it)->Load();
	InputManager::GetInstance().Clear();
	InputManager::GetInstance().SetCanProcess(true);
	SetCurrentScene(it->get());
}

