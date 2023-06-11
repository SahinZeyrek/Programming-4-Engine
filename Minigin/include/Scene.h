#pragma once
#include "SceneManager.h"
#include "Command.h"
namespace dae
{
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(GameObject* object);
		void AddCommand(std::unique_ptr<Command> command);
		void Remove(GameObject* object);
		void FlushMarked();
		void RemoveAll();
		void ForceDestroy();
		void Update();
		void Render() const;
		void BindOnLoad(const std::function<void()>& onLoadFunction);
		void Load();
		const std::string& GetName() const { return m_name; }

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);
		std::string m_name;
		std::function<void()> m_Callback;
		std::vector<std::unique_ptr<Command>> m_Commands;
		std::vector<std::unique_ptr<Command>> m_CommandsRemoval;
		std::vector <GameObject*> m_pObjects{};
		std::vector <GameObject*> m_pMarkedForRemoval{};
		static unsigned int m_idCounter; 
	};

}
