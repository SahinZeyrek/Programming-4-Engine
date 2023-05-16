#include "SoundComponent.h"
#include "../ServiceLocator.h"
namespace dae
{
	void SoundComponent::PlaySound()
	{
		auto& sys =ServiceLocator::GetSoundSystem();
		sys.Play("aughh.wav");
	}

	void SoundComponent::Update()
	{
	}

	void SoundComponent::Render()
	{
	}
}

