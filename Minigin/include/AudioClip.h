#pragma once
#include <string>
namespace dae
{
	class AudioClip final
	{
		class MixerPimpl;
		MixerPimpl* m_Pimpl;
	public:
		AudioClip(const std::string& path, bool preLoad);

		void Play();
		void Load();
		bool IsLoaded() const;
		void SetPause(bool setPause);
		void SetMute(bool setMute);
		void SetVolume(const float volume);
		float GetVolume() const;
		~AudioClip();
	private:
	};
}

