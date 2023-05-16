#pragma once
#include  <string>
namespace dae
{
	// INTERFACE
	using sound_id = unsigned short;
	class ISoundSystem
	{
	public:
		virtual ~ISoundSystem() = default;
		virtual void Play(const std::string& string) = 0;
	};


}

