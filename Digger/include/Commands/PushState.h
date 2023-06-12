#pragma once
#include "Command.h"
#include "State/MenuState.h"
namespace dae
{
	class PushState final : public Command
	{
	public:
		virtual void Execute() override;
		void SetStateToPush(MenuState* state);
		PushState(MenuState* state);
		PushState(const PushState& other) = delete;
		PushState(PushState&& other) = delete;
		PushState& operator=(const PushState& other) = delete;
		PushState& operator=(PushState&& other) = delete;
	private:
		MenuState* m_State;
	};
	
}


