#include "PushState.h"
#include "FiniteStateMachine.h"
namespace dae
{
	void PushState::Execute()
	{
		FiniteStateMachine::GetInstance().Push(m_State);
	}
	void PushState::SetStateToPush(MenuState* state)
	{
		m_State = state;
	}
	PushState::PushState(MenuState* state)
	{
		m_State = state;
	}
}
