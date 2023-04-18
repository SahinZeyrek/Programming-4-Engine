#pragma once
#include "AddScoreCommand.h"
#include "ScoreComponent.h"
namespace dae
{
	void AddScoreCommand::Execute()
	{
		m_Target->GetComponent<ScoreComponent>()->AddScore(25);
	}

}

