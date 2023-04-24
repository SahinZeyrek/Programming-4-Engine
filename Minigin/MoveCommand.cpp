#include "MoveCommand.h"
#include "TimeUtil.h"
void dae::MoveCommand::Execute()
{
	auto pos = m_ObjectPtr->GetLocalPosition();
	pos -= m_ObjectPtr->GetSpeed() * m_Direction * TimeUtil::deltaTime;
	m_ObjectPtr->SetPosition(pos.x, pos.y);
}
