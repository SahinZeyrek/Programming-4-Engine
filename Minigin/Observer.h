#pragma once
namespace dae
{
	class Observer
	{
	public:
		enum class Event
		{
			PlayerDied = 0
		};
		virtual void OnEvent(Event e) = 0;
		virtual ~Observer() = default;
	private:

	};

}


