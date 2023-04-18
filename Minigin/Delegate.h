#pragma once
#include <vector>
#include <functional>
template<typename ... Args>

class Delegate final
{
public:
	// universal reference, compiler tries to pass best option
	using Callback = std::function<void(Args& ...)>;
	void Bind(const Callback& function)
	{
		m_Callbacks.push_back(function);
	}

	void Bind(Callback&& function)
	{
		m_Callbacks.push_back(std::move(function));
	}

	void Invoke(Args&... args) const
	{
		for (const auto& callback : m_Callbacks)
		{
			callback(std::forward<Args&>(args)...);
		}
	}
private:
	std::vector<Callback> m_Callbacks;
};

