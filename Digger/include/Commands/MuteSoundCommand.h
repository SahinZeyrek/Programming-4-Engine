#pragma once
#include "Command.h"

namespace dae
{
	class MuteSoundCommand final : public Command
	{
	public:
		virtual void Execute() override;
		MuteSoundCommand() = default;
		~MuteSoundCommand() = default;
		MuteSoundCommand(const MuteSoundCommand& other) = delete;
		MuteSoundCommand(MuteSoundCommand&& other) = delete;
		MuteSoundCommand& operator=(const MuteSoundCommand& other) = delete;
		MuteSoundCommand& operator=(MuteSoundCommand&& other) = delete;
	private:
		bool m_IsMuted{false};
	};
}


