#pragma once
#include <memory>
#include "Transform.h"
#include "Component.h"
#include <vector>
#include "Observer.h"
#include <exception>
#include "Scene.h"
namespace dae
{
	class Texture2D;
	class ParentException : public std::exception
	{
	public:
		ParentException() = default;

		const char* what() const noexcept override {
			return "Invalid Parent";
		}
	};
	class GameObject final : public Observer
	{
		using GameObjectPtr = GameObject*;
	public:

		template <typename T>
		void AddComponent(T* component)
		{
			if (component == nullptr)
			{
				return;
			}
			m_pComponents.emplace_back(component);
			return;
		};
		template <typename T>
		T* GetComponent() const
		{
			for (auto& comp : m_pComponents)
			{
				auto pComponent = dynamic_cast<T*>(comp);

				if (pComponent != nullptr)
				{
					return pComponent;
				}
			}
			return nullptr;
		};
		template <typename T>
		void RemoveComponent()
		{
			for (size_t i = 0; i < m_pComponents.size(); ++i)
			{
				auto pComponent = dynamic_cast<T*>(m_pComponents[i]);
				if (pComponent != nullptr)
				{
					m_pMarkedForRemoval.push_back(pComponent);
				}
			}
		};
		void RemoveComponent(Component* component);

		Transform GetTransform() const{ return m_Transform;}
		glm::vec3 GetLocalPosition() const { return m_Transform.GetPosition(); }
		Scene* GetParentScene() const { return m_ParentScene; }
		void SetParent(GameObjectPtr go, bool keepWorldPos);
		void SetIsActive(bool isActive) { m_IsActive = isActive; }
		void Update();
		void Render() const;
		void SetPosition(float x, float y);
		void SetParentScene(Scene* scene);
		const glm::vec3& GetWorldPosition();
		void UpdateWorldPos();
		virtual void OnEvent(Event event) override;

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:

		Transform m_Transform{};
		glm::vec3 m_worldPos{};

		std::vector<Component*> m_pComponents{};
		std::vector<Component*> m_pMarkedForRemoval{};
		GameObject* m_Parent{};
		bool m_isDirty{ false };
		bool m_IsActive{ true };
		Scene* m_ParentScene;

	};
}
