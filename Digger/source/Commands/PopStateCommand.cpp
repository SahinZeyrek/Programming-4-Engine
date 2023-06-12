#include "PopStateCommand.h"
#include "FiniteStateMachine.h"
void dae::PopStateCommand::Execute()
{
	FiniteStateMachine::GetInstance().Pop();
}
