#pragma once
#include "State/MenuState.h"
#include "GameObject.h"
namespace dae
{
	class HighScoreMenu final : public MenuState
	{
		struct Player
		{
			std::string name;
			int score;
		};
	public:
		HighScoreMenu() = default;
		void SetTitle(GameObject* title);
		void AddHighScoreObj(GameObject* obj);
		std::vector<GameObject*> GetHighScoreObjs() { return m_Highscores; }
		size_t GetAmountHighScores() const{ return m_AmountHighScores; }
		virtual void OnEnter() override;
		virtual void OnExit() override;
	private:
		GameObject* m_Title;
		std::vector<GameObject*> m_Highscores;
		std::vector<Player> m_Players;
		size_t m_AmountHighScores{ 5 };
	};
}


