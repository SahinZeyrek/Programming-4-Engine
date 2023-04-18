#include "MoveCommand.h"
#include "Time.h"
void dae::MoveCommand::Execute()
{
	auto pos = m_ObjectPtr->GetLocalPosition();
	pos -= m_ObjectPtr->GetSpeed() * m_Direction * Time::deltaTime;
	m_ObjectPtr->SetPosition(pos.x, pos.y);
}
