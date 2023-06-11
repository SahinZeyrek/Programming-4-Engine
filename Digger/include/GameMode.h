#pragma once
#include "Scene.h"

namespace dae
{
	class GameMode
	{
	public:
		virtual void Init(Scene* m_Scene,const std::string& gridStructure) = 0;
		GameMode() = default;
		virtual ~GameMode() = default;
		GameMode(const GameMode& other) = delete;
		GameMode(GameMode&& other) = delete;
		GameMode& operator=(const GameMode& other) = delete;
		GameMode& operator=(GameMode&& other) = delete;
	};

}

