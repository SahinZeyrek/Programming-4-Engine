#include "ServiceLocator.h"

namespace dae
{
	std::unique_ptr <ISoundSystem> ServiceLocator::m_SS_Instance{ std::make_unique<NullSoundSys>() };
}