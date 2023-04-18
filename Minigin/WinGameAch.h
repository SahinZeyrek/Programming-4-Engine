#pragma once
#include "Achievement.h"
#include "ScoreComponent.h"
namespace dae
{
	class WinGameAch final : public Achievement
	{public:
		WinGameAch() = default;
		virtual void UnlockAchievement() override;
		virtual void OnEvent(Observer::Event e) override;
		virtual ~WinGameAch() = default;
		WinGameAch(const WinGameAch&) = delete;
		WinGameAch(WinGameAch&&) = delete;
		WinGameAch& operator=(const WinGameAch&) = delete;
		WinGameAch& operator=(const WinGameAch&&) = delete;
	private:
	};

}


