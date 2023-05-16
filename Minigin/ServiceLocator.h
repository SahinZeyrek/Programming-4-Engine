#pragma once
#include <memory>
#include "SDLSoundSys.h"
#include  "NullSoundSys.h"
#include "ISoundSystem.h"
namespace dae
{
	class ServiceLocator final
	{
		static std::unique_ptr<ISoundSystem> m_SS_Instance;
	public:
		static ISoundSystem& GetSoundSystem() { return *m_SS_Instance; }
		static void RegisterSoundSystem(std::unique_ptr<ISoundSystem>&& sys)
		{
			m_SS_Instance = sys == nullptr ? std::make_unique<NullSoundSys>(): std::move(sys) ;
		}
	};
	
}


