#pragma once
#include <string>
namespace dae
{
	class AudioClip final
	{
	public:
		AudioClip(std::string_view filepath);

		void Play(float volume);
		void Load();
		void Unload();
		bool IsLoaded() const;
		~AudioClip();

	private:
		class Impl;
		Impl* m_Pimpl;
	};
}

