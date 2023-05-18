#include "sound/AudioClip.h"

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

namespace dae
{
	// ---------------------------------------------------------------------------
	// AudioClip | Impl
	// ---------------------------------------------------------------------------

	class AudioClip::Impl final
	{
	public:
		Impl(std::string_view filepath);

		void Load();
		void Unload();
		void Play(float volume);
		bool IsLoaded() const;

		Impl(const Impl&)				= delete;
		Impl(Impl&&)					= delete;
		Impl& operator=(const Impl&)	= delete;
		Impl& operator=(Impl&&)			= delete;

		~Impl();

	private:
		std::string m_Filepath;
		Mix_Chunk* m_pChunk = nullptr;
	};

	AudioClip::Impl::Impl(std::string_view filepath)
		: m_Filepath{ filepath }
	{

	}

	AudioClip::Impl::~Impl()
	{
		Unload();
	}

	void AudioClip::Impl::Load()
	{
		if (m_pChunk == nullptr)
		{
			m_pChunk = Mix_LoadWAV(m_Filepath.c_str());
			if (m_pChunk == nullptr)
			{
				std::cout << "Failed to load audio clip '" << m_Filepath << "'\n";
			}
		}
	}

	void AudioClip::Impl::Unload()
	{
		if (m_pChunk != nullptr)
		{
			Mix_FreeChunk(m_pChunk);
			m_pChunk = nullptr;
		}
	}

	void AudioClip::Impl::Play(float volume)
	{
		if (m_pChunk != nullptr)
		{
			Mix_VolumeChunk(m_pChunk, static_cast<int>(MIX_MAX_VOLUME * volume));
			int channel = Mix_PlayChannel(-1, m_pChunk, 0);

			if (channel == -1)
			{
				std::cout << "Could not play '" << m_Filepath << "' No free channel was available\n";
			}
		}
	}

	bool AudioClip::Impl::IsLoaded() const
	{
		return m_pChunk != nullptr;
	}

	// ---------------------------------------------------------------------------
	// AudioClip
	// ---------------------------------------------------------------------------

	void AudioClip::Load()
	{
		m_Pimpl->Load();
	}

	void AudioClip::Unload()
	{
		m_Pimpl->Unload();
	}

	void AudioClip::Play(float volume)
	{
		m_Pimpl->Play(volume);
	}

	bool AudioClip::IsLoaded() const
	{
		return m_Pimpl->IsLoaded();
	}

	AudioClip::AudioClip(std::string_view filepath)
	{
		m_Pimpl = new Impl(filepath);
	}
	AudioClip::~AudioClip()
	{
		delete m_Pimpl;
	}
}

