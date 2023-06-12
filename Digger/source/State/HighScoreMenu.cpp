#include <fstream>
#include "State/HighScoreMenu.h"
#include "RenderTextComponent.h"
#include <algorithm>
namespace dae
{
	void HighScoreMenu::SetTitle(GameObject* title)
	{
		m_Title = title;
	}

	void HighScoreMenu::AddHighScoreObj(GameObject* obj)
	{
		m_Highscores.push_back(obj);
	}
	void HighScoreMenu::OnEnter()
	{
		for (const auto el : m_Highscores)
		{
			el->SetIsActive(true);
		}
		std::ifstream iStream("../Data/HighScores.txt");
		if (iStream.is_open())
		{
			m_Players.clear();
			std::string line;
			while (std::getline(iStream,line))
			{
				Player player;
				const size_t index =line.find_first_of('|');
				player.name = line.substr(0, index);
				auto score = line.substr(index + 1);
				player.score = std::stoi(score);
				m_Players.push_back(player);
			}
			std::sort(m_Players.begin(), m_Players.end(), [](const Player& a,const Player& b)
				{
					return a.score > b.score;
				});
		}
		for (size_t i{0};i < m_AmountHighScores;++i)
		{
			m_Highscores[i]->GetComponent<RenderTextComponent>()->SetText(m_Players[i].name + " - " + std::to_string(m_Players[i].score));
		}
		m_Title->SetIsActive(true);
		
	}

	void HighScoreMenu::OnExit()
	{
		m_Title->SetIsActive(false);
		for (size_t i = 0; i < m_Highscores.size(); ++i)
		{
			m_Highscores[i]->SetIsActive(false);
		}
	}

}

