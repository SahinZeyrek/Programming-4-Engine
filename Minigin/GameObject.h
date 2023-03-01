#pragma once
#include <memory>
#include "Transform.h"
#include "Component.h"
#include <vector>
namespace dae
{
	class Texture2D;

	class GameObject final
	{
		
	public:
		virtual void Update();

		template <typename T>
		T* AddComponent(T* component)
		{
			if (component == nullptr)
			{
				return nullptr;
			}
			m_pComponents.emplace_back(component);
			return nullptr;
		};
		template <typename T> T* GetComponent() const
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
		template <typename T> T* RemoveComponent()
		{
			for (size_t i = 0; i < m_pComponents.size(); i++)
			{
				auto pComponent = dynamic_cast<T*>(m_pComponents[i]);
				if (pComponent != nullptr)
				{
					delete pComponent;
					m_pComponents.erase(pComponent);
				}
			}
		};
		virtual void Render() const;
		void SetPosition(float x, float y);
		Transform GetTransform() const { return m_Transform; }
		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:

		Transform m_Transform{};
		std::vector<Component*> m_pComponents;

	};
}
