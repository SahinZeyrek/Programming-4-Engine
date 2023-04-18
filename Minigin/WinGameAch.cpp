#include "WinGameAch.h"
#pragma warning(disable:6340)
#include <steam_api.h>
#pragma warning(default:6340)
namespace dae
{
	

	void WinGameAch::UnlockAchievement()
	{
		if (SteamUserStats()->RequestCurrentStats())
		{
			if (SteamUserStats()->SetAchievement("ACH_WIN_ONE_GAME"))
			{
				SteamUserStats()->StoreStats();
			}
		}

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
