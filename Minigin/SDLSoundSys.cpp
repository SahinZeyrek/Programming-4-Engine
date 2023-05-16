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
