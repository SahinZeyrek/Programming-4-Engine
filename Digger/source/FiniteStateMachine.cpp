#include "FiniteStateMachine.h"

namespace dae
{
	void FiniteStateMachine::Push(MenuState* state)
	{
		if (!m_Stack.empty())
		{
			m_Stack.top()->OnExit();
		}
		m_Stack.push(state);
		state->OnEnter();
	}

	void FiniteStateMachine::Pop()
	{
		if (m_Stack.empty())
		{
			m_Stack.top()->OnExit();
			m_Stack.pop();
			if (!m_Stack.empty()) // call on e previous state
			{
				m_Stack.top()->OnEnter();
			}
		}
	}

	MenuState* FiniteStateMachine::GetState()
	{
		return m_Stack.top();
	}
}

