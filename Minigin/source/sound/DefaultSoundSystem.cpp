#include "sound/DefaultSoundSystem.h"
#include "sound/AudioClip.h"

#include <SDL_mixer.h>

#include <memory>
#include <queue>
#include <vector>
#include <unordered_map>
#include <thread>
#include <atomic>
#include <condition_variable>

namespace dae
{
	// ---------------------------------------------------------------------------
	// DefaultSoundSystem | Impl
	// ---------------------------------------------------------------------------

	class DefaultSoundSystem::Impl final
	{
	public:
		Impl();

		sound_id AddSound(std::string_view filepath);
		void Play(sound_id id, float volume);
		void Pause();
		void Resume();
		void Mute();
		void Unmute();
		void SetVolume(float volume);

		Impl(const Impl&)				= delete;
		Impl(Impl&&)					= delete;
		Impl& operator=(const Impl&)	= delete;
		Impl& operator=(Impl&&)			= delete;

		~Impl();

	private:
		struct SoundEvent
		{
			sound_id id;
			float volume;
		};

		std::unordered_map<std::string, sound_id> m_SoundIdMap;
		std::vector<std::unique_ptr<AudioClip>> m_AudioClips;

		std::queue<SoundEvent> m_SoundQueue;

		std::jthread m_Thread;
		std::mutex m_Mutex;
		std::condition_variable m_Conditional;
		std::atomic_bool m_JoinThread = false;

		int m_PrevVolume = -1;

	private:
		void ThreadFunction();
	};

	DefaultSoundSystem::Impl::Impl()
		: m_Thread{ &Impl::ThreadFunction, this }
	{

	}

	DefaultSoundSystem::Impl::~Impl()
	{
		m_JoinThread = true;
		m_Conditional.notify_all();
		m_Thread.join();
	}

	sound_id DefaultSoundSystem::Impl::AddSound(std::string_view filepath)
	{
		std::string strFilepath{ filepath };

		auto it = m_SoundIdMap.find(strFilepath);
		if (it != m_SoundIdMap.end())
		{
			return it->second;
		}

		auto id = static_cast<sound_id>(m_AudioClips.size());
		m_SoundIdMap.emplace(strFilepath, id);

		{
			std::lock_guard lock{ m_Mutex };
			m_AudioClips.emplace_back(std::make_unique<AudioClip>(filepath));
		}

		return id;
	}

	void DefaultSoundSystem::Impl::Play(sound_id id, float volume)
	{
		{
			std::lock_guard lock{ m_Mutex };
			m_SoundQueue.emplace(id, volume);
		}

		m_Conditional.notify_one();
	}

	void DefaultSoundSystem::Impl::Pause()
	{
		Mix_Pause(-1);
	}

	void DefaultSoundSystem::Impl::Resume()
	{
		Mix_Resume(-1);
	}

	void DefaultSoundSystem::Impl::Mute()
	{
		m_PrevVolume = Mix_Volume(-1, 0);
	}

	void DefaultSoundSystem::Impl::Unmute()
	{
		if (m_PrevVolume >= 0)
		{
			Mix_Volume(-1, m_PrevVolume);
			m_PrevVolume = -1;
		}
	}

	void DefaultSoundSystem::Impl::SetVolume(float volume)
	{
		Mix_Volume(-1, static_cast<int>(MIX_MAX_VOLUME * volume));
	}

	void DefaultSoundSystem::Impl::ThreadFunction()
	{
		while (true)
		{
			std::unique_lock lock{ m_Mutex };
			m_Conditional.wait(lock, [this]() { return !m_SoundQueue.empty() || m_JoinThread; });

			if (m_JoinThread)
			{
				break;
			}

			auto [id, volume] = m_SoundQueue.front();
			m_SoundQueue.pop();

			auto pAudioClip = m_AudioClips[id].get();

			lock.unlock();

			if (!pAudioClip->IsLoaded())
			{
				pAudioClip->Load();
			}

			pAudioClip->Play(volume);
		}
	}

	// ---------------------------------------------------------------------------
	// DefaultSoundSystem
	// ---------------------------------------------------------------------------

	DefaultSoundSystem::DefaultSoundSystem()
	{
		m_pImpl = new Impl();
	}

	DefaultSoundSystem::~DefaultSoundSystem()
	{
		delete m_pImpl;
	}

	sound_id DefaultSoundSystem::AddSound(std::string_view filepath)
	{
		return m_pImpl->AddSound(filepath);
	}

	void DefaultSoundSystem::Play(sound_id id, float volume)
	{
		m_pImpl->Play(id, volume);
	}

	void DefaultSoundSystem::Pause()
	{
		m_pImpl->Pause();
	}

	void DefaultSoundSystem::Resume()
	{
		m_pImpl->Resume();
	}

	void DefaultSoundSystem::Mute()
	{
		m_pImpl->Mute();
	}

	void DefaultSoundSystem::Unmute()
	{
		m_pImpl->Unmute();
	}

	void DefaultSoundSystem::SetVolume(float volume)
	{
		m_pImpl->SetVolume(volume);
	}
}
