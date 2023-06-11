#pragma once
#include <functional>
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		void SetCurrentScene(Scene* scene);
		void LoadScene(const std::string& name);
		void Update();
		void Render();
	private:
		Scene* m_CurrentScene;
		friend class Singleton<SceneManager>;
		~SceneManager();
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
	};
}