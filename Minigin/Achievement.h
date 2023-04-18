#pragma once
#include "Observer.h"
namespace dae
{
	class Achievement : public Observer
	{
	public:
		virtual void UnlockAchievement() = 0;
		virtual void OnEvent(Observer::Event e) override;
		explicit Achievement() = default;
		virtual ~Achievement() = default;
		Achievement(const Achievement&) = delete;
		Achievement(Achievement&&) = delete;
		Achievement& operator=(const Achievement&) = delete;
		Achievement& operator=(const Achievement&&) = delete;
	private:
	};

}


