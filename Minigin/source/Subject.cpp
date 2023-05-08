#include "Subject.h"
namespace dae
{
	void Subject::Bind(Observer* observer)
	{
		if (observer != nullptr)
		{
			m_Observers.insert(observer);
		}
	}
	void Subject::Unbind(Observer* observer)
	{
		if (observer != nullptr)
		{
			m_Observers.erase(observer);
		}
	}

	void Subject::Invoke(Observer::Event event)
	{
		for (const auto& observer : m_Observers)
		{
			observer->OnEvent(event);
		}
	}

}

