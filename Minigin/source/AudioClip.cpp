#include "AudioClip.h"

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
namespace dae
{
	class AudioClip::MixerPimpl
	{
	public:
		MixerPimpl(const std::string& path, bool preLoad) : m_Path{path}  
		{
			if (preLoad)
			{
				Load();
				m_IsLoaded = true;
			}

		}
		~MixerPimpl()
		{
			Mix_FreeChunk(m_SoundEffect);
		}
		void Load()
		{
			m_SoundEffect = Mix_LoadWAV(m_Path.c_str());
			if (!m_SoundEffect)
			{
				std::cout << "Sound effect was nullptr, SDl Error :" << Mix_GetError() << '\n';
				m_IsLoaded = false;
			}
			else
			{
				m_IsLoaded = true;
			}
		}
		bool IsLoaded()
		{
			return m_IsLoaded;
		};
		void Play()
		{
			if (!m_IsLoaded)
			{
				std::cout << "Sound effect was not loaded.\n";
			}
			Mix_PlayChannel(-1, m_SoundEffect, 0);
		}
		void SetPause(bool setPause)
		{
			if (setPause)
			{
				Mix_Pause(-1);
			}
			Mix_Resume(-1);
		}
		void SetMute(bool setMute)
		{
			if (setMute)
			{
				Mix_Volume(-1, 0);
			}
			Mix_Volume(-1, static_cast<int>(m_Volume));
		}
		void SetVolume(const float volume)
		{
			m_Volume = volume;
			Mix_Volume(-1, static_cast<int>(m_Volume));
		}
	private:
		float m_Volume{ 50.f };
		const std::string m_Path;
		Mix_Chunk* m_SoundEffect{};
		bool m_IsLoaded{ false };
	};
	void AudioClip::Load()
	{
		m_Pimpl->Load();
	}
	void AudioClip::Play()
	{
		m_Pimpl->Play();
	}

	bool AudioClip::IsLoaded() const
	{
		m_Pimpl->IsLoaded();
	}

	void AudioClip::SetPause(bool setPause)
	{
		m_Pimpl->SetPause(setPause);
	}

	void AudioClip::SetMute(bool setMute)
	{
		m_Pimpl->SetMute(setMute);
	}

	AudioClip::AudioClip(const std::string& path, bool preLoad)
	{
		m_Pimpl = new MixerPimpl(path, preLoad);
	}
	AudioClip::~AudioClip()
	{
		delete m_Pimpl;
	}
}

