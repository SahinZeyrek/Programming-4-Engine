#include "SDLSoundSys.h"
#include "AudioManager.h"
namespace dae
{
	void SDLSoundSys::Play(const std::string& path)
	{
		{
			std::lock_guard lockGuard(m_Mutex);
			m_AudioQueue.emplace(path);
		}
		m_Condition.notify_one();
	}

	void SDLSoundSys::SetPause(bool setPause)
	{
		// i know its really strange code but im on my last legs right now,
		// hello to the people in the class if i make it on the slides :)
		for (int i{0 } ; i < m_AudioQueue.size(); ++i)
		{
			auto path = std::move(m_AudioQueue.front());
			m_AudioQueue.pop();
			AudioManager::GetInstance().GetAudioClip(path)->SetPause(setPause);
			m_AudioQueue.emplace(std::move(path));
		}
	}

	void SDLSoundSys::SetMute(bool setMute)
	{
		for (int i{ 0 }; i < m_AudioQueue.size(); ++i)
		{
			auto path = std::move(m_AudioQueue.front());
			m_AudioQueue.pop();
			AudioManager::GetInstance().GetAudioClip(path)->SetMute(setMute);
			m_AudioQueue.emplace(std::move(path));
		}
	}

	void SDLSoundSys::SetVolume(const float volume)
	{
		for (int i{ 0 }; i < m_AudioQueue.size(); ++i)
		{
			auto path = std::move(m_AudioQueue.front());
			m_AudioQueue.pop();
			AudioManager::GetInstance().GetAudioClip(path)->SetVolume(volume);
			m_AudioQueue.emplace(std::move(path));
		}
	}

	SDLSoundSys::~SDLSoundSys()
	{
		m_CanJoin = true;
		m_Condition.notify_all();
		m_Thread.join();
	}

	void SDLSoundSys::FlushQueue()
	{
		while (true)
		{
			std::unique_lock uLock{ m_Mutex };
			m_Condition.wait(uLock, [this]()
				{
					return !m_AudioQueue.empty() || m_CanJoin ; 
				});
			if (m_AudioQueue.empty() && m_CanJoin)
			{
				break;
			}
			const std::string path = std::move(m_AudioQueue.front());
			m_AudioQueue.pop();

			auto audioClip = AudioManager::GetInstance().GetAudioClip(path);
			if (audioClip == nullptr)
			{
				AudioManager::GetInstance().AddAudioClip(path, true);
				audioClip = AudioManager::GetInstance().GetAudioClip(path);

			}
			if (audioClip->IsLoaded() == false)
			{
				audioClip->Load();
			}
			audioClip->Play();
		}

	}
}
