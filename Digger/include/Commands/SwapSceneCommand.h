#pragma once
#include "Command.h"
#include "Scene.h"
namespace dae
{
	class SwapSceneCommand final : public Command
	{
	public:
		virtual void Execute() override;
		SwapSceneCommand(const std::string& scene);
		SwapSceneCommand(const SwapSceneCommand& other) = delete;
		SwapSceneCommand(SwapSceneCommand&& other) = delete;
		SwapSceneCommand& operator=(const SwapSceneCommand& other) = delete;
		SwapSceneCommand& operator=(SwapSceneCommand&& other) = delete;
	private:
		std::string m_SceneName;
	};

}

