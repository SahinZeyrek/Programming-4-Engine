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
	private:
		std::unordered_set<Observer*> m_Observers{};
	};
}


