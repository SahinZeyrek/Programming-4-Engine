#include "AudioManager.h"

namespace dae
{
	void AudioManager::AddAudioClip(const std::string& path, bool preLoad)
	{
		if (!m_AudioClips.contains(path))
		{
			m_AudioClips[path] = std::make_unique<AudioClip>(path, preLoad);
		}
	}

	AudioClip* AudioManager::GetAudioClip(const std::string& path)
	{
		const auto it = m_AudioClips.find(path);
		if (it == m_AudioClips.end())
		{
			return nullptr;
		}
		return it->second.get();
	}
}

