#include "WinGameAch.h"
namespace dae
{
	

	void WinGameAch::UnlockAchievement()
	{

	}

	void WinGameAch::OnEvent(Observer::Event e)
	{
		switch (e)
		{
		case dae::Observer::Event::ScoreGoalReached:
			UnlockAchievement();
			break;
		case dae::Observer::Event::ScoreChanged:
			break;
		default:
			break;
		}
	}

}
