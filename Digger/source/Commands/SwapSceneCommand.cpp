#include "SwapSceneCommand.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "FiniteStateMachine.h"
namespace dae
{
	void SwapSceneCommand::Execute()
	{
		FiniteStateMachine::GetInstance().highscoreState->GetHighScoreObjs().clear();
		InputManager::GetInstance().SetCanProcess(false);
		auto& sm = SceneManager::GetInstance();
		std::string capture = m_SceneName;
		sm.LoadScene(capture);
	}
	SwapSceneCommand::SwapSceneCommand(const std::string& scene) : m_SceneName(scene)
	{

	}
}
