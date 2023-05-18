#include "SoundComponent.h"
#include "../ServiceLocator.h"
namespace dae
{
	SoundComponent::SoundComponent(GameObjectPtr owner, std::string_view soundPath, float volume)
		: Component(owner)
		, m_Volume{ volume }
	{
		auto& sys = ServiceLocator::GetSoundSystem();
		m_SoundId = sys.AddSound(soundPath);
	}

	void SoundComponent::PlaySound()
	{
		auto& sys = ServiceLocator::GetSoundSystem();
		sys.Play(m_SoundId, m_Volume);
	}

	void SoundComponent::Update()
	{
	}

	void SoundComponent::Render()
	{
	}
}

