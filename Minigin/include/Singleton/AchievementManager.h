#pragma once
#include "Singleton.h"
#include <vector>
#include "Achievement/Achievement.h"
#include <memory>
namespace dae
{
	class AchievementManager final : public dae::Singleton<AchievementManager>
	{
	public:
		Achievement* AddAchievement(std::unique_ptr<Achievement> ach) 
		{ 
		  m_Achievements.emplace_back(std::move(ach));
		  return m_Achievements.back().get();
		}

	private:
		std::vector<std::unique_ptr<Achievement>> m_Achievements;
		friend class Singleton<AchievementManager>;
		AchievementManager() = default;
	};

}


