#pragma once
namespace dae
{
	class Observer
	{
	public:
		enum class Event
		{
			PlayerDied,
			ScoreChanged,
			ScoreGoalReached,
			ItemPickedUp
		};
		virtual void OnEvent(Event e) = 0;
		virtual ~Observer() = default;
	private:

	};

}


