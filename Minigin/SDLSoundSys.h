#pragma once
#include "ISoundSystem.h"
#include <queue>
#include <thread>
#include <condition_variable>
namespace dae
{
	class SDLSoundSys final : public ISoundSystem
	{
	public:
		virtual void Play(const std::string& path) override;
		virtual void SetPause(bool setPause) override;
		virtual void SetMute(bool setMute) override;
		virtual void SetVolume(const float volume) override;
		virtual ~SDLSoundSys() override;
		SDLSoundSys()
		{
			m_Thread = std::jthread(&SDLSoundSys::FlushQueue, this);
		}
		SDLSoundSys(const SDLSoundSys& other) = delete;
		SDLSoundSys(SDLSoundSys&& other) = delete;
		SDLSoundSys& operator=(const SDLSoundSys& other) = delete;
		SDLSoundSys& operator=(SDLSoundSys&& other) = delete;
	private:
		void FlushQueue();
		std::jthread m_Thread;
		std::mutex m_Mutex;
		std::queue<std::string> m_AudioQueue;
		std::condition_variable m_Condition;
		std::atomic_bool m_CanJoin{ false };
		
	};
	
}


