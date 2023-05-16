#pragma once
#include "Singleton.h"
#include <unordered_map>
#include "../AudioClip.h"
#include <memory>
#include <string>
namespace dae
{
	class AudioManager final : public Singleton<AudioManager>
	{
	public:
		void AddAudioClip(const std::string& path,bool preLoad);
		AudioClip* GetAudioClip(const std::string& path);

	private:
		AudioManager() = default;
		~AudioManager() = default;
		std::unordered_map<std::string, std::unique_ptr<AudioClip>> m_AudioClips;
		friend Singleton<AudioManager>;
	};
	
}


