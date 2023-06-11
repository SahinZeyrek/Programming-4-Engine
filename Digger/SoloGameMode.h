#pragma once
#include "GameMode.h"

namespace dae
{
	class SoloGameMode final : public GameMode
	{
	public:
		virtual void Init(Scene* m_Scene,const std::string& GridStructure) override;
		SoloGameMode() = default;
	private:
	};
}


