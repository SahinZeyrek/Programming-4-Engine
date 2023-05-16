#pragma once
#include "AddScoreCommand.h"
#include "ScoreComponent.h"
#include "SoundComponent.h"

// sound component added in the add score command just for quick testing.
namespace dae
{
	void AddScoreCommand::Execute()
	{
		m_Target->GetComponent<ScoreComponent>()->AddScore(25);
		m_Target->GetComponent<SoundComponent>()->PlaySound();
	}

}

