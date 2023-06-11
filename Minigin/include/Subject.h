#pragma once
#include "Observer.h"
#include <unordered_set>
namespace dae
{
	class Subject final
	{
	public:
		void Bind(Observer* observer);
		void Unbind(Observer* observer);
		void Invoke(Observer::Event event);
		std::unordered_set<Observer*> GetObservers();
		~Subject() = default;
		Subject() = default;
		Subject(const Subject& other) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) = delete;

	private:
		std::unordered_set<Observer*> m_Observers{};
	};
}


